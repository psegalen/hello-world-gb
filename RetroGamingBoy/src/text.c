#include <gb/gb.h>
#include "./font.tileset.h"
#include "text.h"

void textLoadFont() {
    set_bkg_data(TEXT_OFFSET, FONT_TS_TILE_COUNT, FONT_TS);
}

void textPrintCharBkg(UINT8 x, UINT8 y, unsigned char chr) {
    UINT8 tile = _TEXT_CHAR_TOFU;

    if (chr >= 'A' && chr <= 'Z') {
        tile = _TEXT_CHAR_A + chr - 'A';
    } else if (chr >= 'a' && chr <= 'z') {
        tile = _TEXT_CHAR_A + chr - 'a';
    } else if (chr >= '0' && chr <= '9') {
        tile = _TEXT_CHAR_0 + chr - '0';
    } else {
        switch (chr) {
            case ' ':
                tile = _TEXT_CHAR_SPACE;
                break;
        }
    }

    set_bkg_tiles(x, y, 1, 1, &tile);
}