#include <gb/gb.h>
#include "./splashscreen.tileset.h"
#include "./splashscreen.tilemap.h"

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3

#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

void wait_frames(INT8 count) {
    while (count) {
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
    wait_frames(60);  // ~ 1s

    // Fade-in
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, WHITE);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, SILVER);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, SILVER, GRAY);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);

    wait_frames(120);  // ~ 2s

    // Fade-out (inverted color)
    BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, SILVER, GRAY);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, SILVER);
    wait_frames(5);   // ~ 0.08s
    BGP_REG = PALETTE(WHITE, WHITE, WHITE, WHITE);
    wait_frames(5);   // ~ 0.08s
}

void main(void) {
    // Display the splash screen
    splashScreen();
}
