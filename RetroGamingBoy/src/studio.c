#include <gb/gb.h>
#include "./studio.tileset.h"
#include "./studio.tilemap.h"
#include "./player.sprite.h"
#include "./helpers.h"
#include "./studio.h"
#include "./text.h"

// Constantes sprites
UINT8 PLAYER_ANIMATION_RIGHT[] = {24, 28, 24, 32};
UINT8 PLAYER_ANIMATION_TOP[] = {12, 16, 12, 20};
UINT8 PLAYER_ANIMATION_BOTTOM[] = {0, 4, 0, 8};
#define PLAYER_DIRECTION_RIGHT   0
#define PLAYER_DIRECTION_LEFT    1
#define PLAYER_DIRECTION_TOP     2
#define PLAYER_DIRECTION_BOTTOM  3

// Variables d'état
UINT8 playerScreenX;
UINT8 playerScreenY;
UINT8 playerWorldX;
UINT8 playerWorldY;
UINT8 playerAnimationStep = 0;
UINT8 frameSkip = 8;
UINT8 playerDirection = PLAYER_DIRECTION_BOTTOM;
UINT8 bkgXPosition = 0;

const UINT8 DELIMITER_LINE[20] = {_TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER, _TEXT_CHAR_BORDER};
const UINT8 BLANK_LINE[20] = {_TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE, _TEXT_CHAR_SPACE};

void displayMap(void) {
    HIDE_BKG;
    HIDE_WIN;
    
    set_bkg_data(0, STUDIO_TS_TILE_COUNT, STUDIO_TS);
    set_bkg_tiles(0, 0, STUDIO_TM_WIDTH, STUDIO_TM_HEIGHT, STUDIO_TM);
    SHOW_BKG;
}

UINT8 playerCanGo(INT8 dX, INT8 dY) {
    if (playerWorldX + dX < 0) return 0;
    if (playerWorldY + dY == 9) return 0;
    if (playerWorldX + dX == 16) return 0;

    UINT8 cx = (playerWorldX + dX) * 2;
    UINT8 cy = (playerWorldY + dY) * 2;
    UINT8 tiles[4];
    get_bkg_tiles(cx, cy, 2, 2, tiles);

    return tiles[0] <= 0x1F && tiles[1] <= 0x1F
        && tiles[2] <= 0x1F && tiles[3] <= 0x1F;
}

void movePlayer(INT8 dX, INT8 dY) {
    if (!playerCanGo(dX, dY)) return;

    playerWorldX += dX;
    playerWorldY += dY;

    for (UINT8 delta = 16 ; delta ; delta -= 1) {

        // Move camera 
        if ((bkgXPosition && dX == -1 && playerScreenX == 2 * 16) ||
            (bkgXPosition < (16 - 10) * 16 && dX == 1 && playerScreenX == 8 * 16)) {
            bkgXPosition += dX;
            move_bkg(bkgXPosition, 0);
        // Move player
        } else {
            playerScreenX += dX;
            playerScreenY += dY;
            move_sprite(0, playerScreenX, playerScreenY);
            move_sprite(1, playerScreenX +8, playerScreenY);
        }

        // Animate
        frameSkip -= 1;
        if (!frameSkip) {
            switch (playerDirection) {
                case PLAYER_DIRECTION_LEFT:
                    set_sprite_prop(0, get_sprite_prop(0) | S_FLIPX);
                    set_sprite_prop(1, get_sprite_prop(1) | S_FLIPX);
                    set_sprite_tile(1, PLAYER_ANIMATION_RIGHT[playerAnimationStep]);
                    set_sprite_tile(0, PLAYER_ANIMATION_RIGHT[playerAnimationStep] + 2);
                    break;
                case PLAYER_DIRECTION_RIGHT:
                    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
                    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
                    set_sprite_tile(0, PLAYER_ANIMATION_RIGHT[playerAnimationStep]);
                    set_sprite_tile(1, PLAYER_ANIMATION_RIGHT[playerAnimationStep] + 2);
                    break;
                case PLAYER_DIRECTION_TOP:
                    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
                    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
                    set_sprite_tile(0, PLAYER_ANIMATION_TOP[playerAnimationStep]);
                    set_sprite_tile(1, PLAYER_ANIMATION_TOP[playerAnimationStep] + 2);
                    break;
                case PLAYER_DIRECTION_BOTTOM:
                    set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
                    set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
                    set_sprite_tile(0, PLAYER_ANIMATION_BOTTOM[playerAnimationStep]);
                    set_sprite_tile(1, PLAYER_ANIMATION_BOTTOM[playerAnimationStep] + 2);
                    break;
            }
            playerAnimationStep = (playerAnimationStep + 1) % 4;
            frameSkip = 8;
        }

        wait_vbl_done();
    }
}

void rpgInit(void) {
    displayMap();

    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    SPRITES_8x16;
    set_sprite_prop(0, get_sprite_prop(0) | S_PALETTE);
    set_sprite_prop(1, get_sprite_prop(1) | S_PALETTE);
    SHOW_SPRITES;
    playerWorldX = 0;
    playerWorldY = 3;
    playerScreenX = (playerWorldX * 16) + 8;
    playerScreenY = (playerWorldY * 16) + 16;
    move_sprite(0, playerScreenX, playerScreenY);
    move_sprite(1, playerScreenX +8, playerScreenY);

    textLoadFont();
}

void rpgMain(void) {
    UINT8 keys = 0;
    showMessage("Hello\nWorld!\nHow are you\neverybody?");
    while(1) {
        keys = joypad();
        if (keys & J_UP) {
            playerDirection = PLAYER_DIRECTION_TOP;
            movePlayer(0, -1);
        } else if (keys & J_DOWN) {
            playerDirection = PLAYER_DIRECTION_BOTTOM;
            movePlayer(0, +1);
        } else if (keys & J_LEFT) {
            playerDirection = PLAYER_DIRECTION_LEFT;
            movePlayer(-1, 0);
        } else if (keys & J_RIGHT) {
            playerDirection = PLAYER_DIRECTION_RIGHT;
            movePlayer(+1, 0);
        } else if (keys & J_B) {
            showMessage("Hello\nWorld!\nHow are you\neverybody?");
        }

        wait_vbl_done();
    }
}

void clearMessageBox(void) {
    set_win_tiles(0, 0, 20, 1, DELIMITER_LINE);
    set_win_tiles(0, 1, 20, 1, BLANK_LINE);
    set_win_tiles(0, 2, 20, 1, BLANK_LINE);
    set_win_tiles(0, 3, 20, 1, BLANK_LINE);
}

void showMessagBox(void) {
    move_win(7, MESSAGE_BOX_INITIAL_Y);
    SHOW_WIN;
    for(UINT8 y = MESSAGE_BOX_INITIAL_Y; y >= MESSAGE_BOX_FINAL_Y; y -= 1) {
        move_win(7, y);
        wait_vbl_done();
    }
}

void hideMessageBox(void) {
    move_win(7, MESSAGE_BOX_FINAL_Y);
    for(UINT8 y = MESSAGE_BOX_FINAL_Y; y <= MESSAGE_BOX_INITIAL_Y; y += 1) {
        move_win(7, y);
        wait_vbl_done();
    }
    HIDE_WIN;
}

void showMessage(unsigned char* message) {
    clearMessageBox();
    showMessagBox();

    UINT8 offsetX = 1;
    UINT8 offsetY = 1;
    UINT8 newline = 2;

    while (message[0]) {
        if (message[0] == '\n') {
            offsetX = 1;
            offsetY += 1;
            newline -= 1;
        } else {
            textPrintCharWin(offsetX, offsetY, message[0]);
            offsetX += 1;
        }

        if (!newline) {
            while(!(joypad() & J_A)) {
                wait_vbl_done();
            }
            clearMessageBox();
            offsetX = 1;
            offsetY = 1;
            newline = 2;
        }
        message += 1;
        wait_vbl_done();
    }

    while(!(joypad() & J_A)) {
        wait_vbl_done();
    }

    hideMessageBox();
}
