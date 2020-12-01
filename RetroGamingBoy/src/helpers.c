#include <gb/gb.h>
#include "./helpers.h"
#include "./text.h"

void clearScreen(void) {
    UINT8 line[32] = {_TEXT_CHAR_SPACE};
    UINT8 y = 32;
    while (y) {
        y -= 1;
        set_bkg_tiles(0, y, 32, 1, line);
    }
}

UINT8 waitFramesOrKeys(INT8 count) {
    UINT8 keys = 0;
    while (count) {
        keys = joypad();
        if (keys) return keys;
        count -= 1;
        wait_vbl_done();
    }
    return 0;
}
