#include <gb/gb.h>
#include "./splashscreen.tileset.h"
#include "./splashscreen.tilemap.h"
#include "./logo_rgb.tileset.h"
#include "./logo_rgb.tilemap.h"
#include "./studio.tileset.h"
#include "./studio.tilemap.h"
#include "./text.h"
#include "./sprites/player.sprite.h"

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3

#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

UINT8 waitFramesOrKeys(INT8 count) {
    UINT8 keys = 0;
    while (count) {
        keys = joypad();
        if (keys) return keys;
        count -= 1;
        wait_vbl_done();
    }
}

void splashScreen(void) {
    set_bkg_data(0, SPLASH_TS_TILE_COUNT, SPLASH_TS);
    set_bkg_tiles(0, 0, SPLASH_TM_WIDTH, SPLASH_TM_HEIGHT, SPLASH_TM);
    SHOW_BKG;
    
    // Black screen (initial state)
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, WHITE);
    waitFramesOrKeys(60);  // ~ 1s

    // Fade-in
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, WHITE);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, SILVER);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, SILVER, GRAY);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);

    waitFramesOrKeys(120);  // ~ 2s

    // Fade-out (inverted color)
    BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, SILVER, GRAY);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, SILVER);
    waitFramesOrKeys(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, WHITE);
    waitFramesOrKeys(5);   // ~ 0.08s
}

void homeScreen(void) {
    SHOW_BKG;
    SHOW_WIN;
    BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);

    // Logo RGB
    set_bkg_data(0, LOGO_RGB_TS_TILE_COUNT, LOGO_RGB_TS);
    set_bkg_tiles(0, 0, LOGO_RGB_TM_WIDTH, LOGO_RGB_TM_HEIGHT, LOGO_RGB_TM);

    // TEXT
    textLoadFont();
    move_win(0, 16*8);
    textPrintStringWin(5, 0, "Press Start!");

    UINT8 key = 0;
    
    while (1) {
        if (waitFramesOrKeys(50)) {
            break;
        }
        HIDE_WIN;
        if (waitFramesOrKeys(20)) {
            break;
        }
        SHOW_WIN;
    }
}

void clearScreen(void) {
    UINT8 line[32] = {_TEXT_CHAR_SPACE};
    UINT8 y = 32;
    while (y) {
        y -= 1;
        set_bkg_tiles(0, y, 32, 1, line);
    }
}

void displayMap(void) {
    HIDE_BKG;
    HIDE_WIN;
    
    set_bkg_data(0, STUDIO_TS_TILE_COUNT, STUDIO_TS);
    set_bkg_tiles(0, 0, STUDIO_TM_WIDTH, STUDIO_TM_HEIGHT, STUDIO_TM);
    SHOW_BKG;
}

void showSprite(void) {
    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    SPRITES_8x16;
    SHOW_SPRITES;
    move_sprite(0, 32, 128);
    move_sprite(1, 40, 128);
}

void main(void) {
    // Display the splash screen
    splashScreen();

    // Display the home screen
    homeScreen();

    displayMap();

    showSprite();
}
