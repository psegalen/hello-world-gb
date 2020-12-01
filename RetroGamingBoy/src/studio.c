#include <gb/gb.h>
#include "./studio.tileset.h"
#include "./studio.tilemap.h"
#include "./player.sprite.h"
#include "./helpers.h"

// Constantes sprites
UINT8 PLAYER_ANIMATION_RIGHT[] = {24, 28, 24, 32};
UINT8 PLAYER_ANIMATION_TOP[] = {12, 16, 12, 20};
UINT8 PLAYER_ANIMATION_BOTTOM[] = {0, 4, 0, 8};
#define PLAYER_DIRECTION_RIGHT   0
#define PLAYER_DIRECTION_LEFT    1
#define PLAYER_DIRECTION_TOP     2
#define PLAYER_DIRECTION_BOTTOM  3

// Variables d'état
UINT8 playerX;
UINT8 playerY;
UINT8 playerAnimationStep = 0;
UINT8 frameSkip = 8;
UINT8 playerIsWalking = 0;
UINT8 playerDirection = PLAYER_DIRECTION_RIGHT;
UINT8 bkgXPosition = 0;

void displayMap(void) {
    HIDE_BKG;
    HIDE_WIN;
    
    set_bkg_data(0, STUDIO_TS_TILE_COUNT, STUDIO_TS);
    set_bkg_tiles(0, 0, STUDIO_TM_WIDTH, STUDIO_TM_HEIGHT, STUDIO_TM);
    SHOW_BKG;
}

void movePlayer(UINT8 dX, UINT8 dY) {
    playerX += dX;
    playerY += dY;
    move_sprite(0, playerX, playerY);
    move_sprite(1, playerX +8, playerY);
}

void rpgInit(void) {
    displayMap();

    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    SPRITES_8x16;
    SHOW_SPRITES;
    playerX = 96;
    playerY = 48;
    movePlayer(0, 0);
    set_sprite_prop(0, get_sprite_prop(0) | S_PALETTE);
    set_sprite_prop(1, get_sprite_prop(1) | S_PALETTE);
}

void rpgMain(void) {
    UINT8 keys = 0;
    while(1) {
        keys = joypad();
        playerIsWalking = 0;
        if (keys & J_UP) {
            playerDirection = PLAYER_DIRECTION_TOP;
            movePlayer(0, -1);
            playerIsWalking = 1;
        } else if (keys & J_DOWN) {
            playerDirection = PLAYER_DIRECTION_BOTTOM;
            if (playerY <= (18 * 8) - 1) {
                movePlayer(0, +1);
            }
            playerIsWalking = 1;
        } else if (keys & J_LEFT) {
            playerDirection = PLAYER_DIRECTION_LEFT;
            playerIsWalking = 1;
            if (bkgXPosition && playerX < 32) {
                bkgXPosition -= 1;
            } else if (playerX >= 8) {
                movePlayer(-1, 0);
            }
        } else if (keys & J_RIGHT) {
            playerDirection = PLAYER_DIRECTION_RIGHT;
            playerIsWalking = 1;
            if (bkgXPosition < (12 * 8) && playerX > 128 + 8) {
                bkgXPosition += 1;
            } else if (playerX <= (20 * 8) - 8) {
                movePlayer(+1, 0);
            }
        }
        move_bkg(bkgXPosition, 0);

        if (playerIsWalking) {
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
        }

        wait_vbl_done();   
    }
}
