#include <gb/gb.h>
#include "./splashscreen.tileset.h"
#include "./splashscreen.tilemap.h"
#include "./logo_rgb.tileset.h"
#include "./logo_rgb.tilemap.h"
#include "./text.h"
#include "./helpers.h"

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
