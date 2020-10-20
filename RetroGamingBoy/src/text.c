#include <gb/gb.h>
#include "./font.tileset.h"
#include "text.h"

void textLoadFont() {
    set_bkg_data(TEXT_OFFSET, FONT_TS_TILE_COUNT, FONT_TS);
}

void textPrintCharWin(UINT8 x, UINT8 y, unsigned char chr) {
    UINT8 tile = _TEXT_CHAR_TOFU;

    if (chr >= 'A' && chr <= 'Z') {
        tile = _TEXT_CHAR_A + chr - 'A';
    } else if (chr >= 'a' && chr <= 'z') {
        tile = _TEXT_CHAR_A + chr - 'a';
    } else if (chr >= '0' && chr <= '9') {
        tile = _TEXT_CHAR_0 + chr - '0';
    } else {
        switch (chr) {
            case '\'':
                tile = _TEXT_CHAR_APOSTROPHE;
                break;
            case '-':
                tile = _TEXT_CHAR_DASH;
                break;
            case '.':
                tile = _TEXT_CHAR_DOT;
                break;
            case ',':
                tile = _TEXT_CHAR_COMMA;
                break;
            case ':':
                tile = _TEXT_CHAR_COLON;
                break;
            case '!':
                tile = _TEXT_CHAR_EXCLAMATION;
                break;
            case '?':
                tile = _TEXT_CHAR_INTERROGATION;
                break;
            case '(':
                tile = _TEXT_CHAR_LPARENTHESES;
                break;
            case ')':
                tile = _TEXT_CHAR_RPARENTHESES;
                break;
            case ' ':
                tile = _TEXT_CHAR_SPACE;
                break;
        }
    }

    set_win_tiles(x, y, 1, 1, &tile);
}

void textPrintStringWin(UINT8 x, UINT8 y, unsigned char *string) {
    UINT8 offsetX = 0;
    UINT8 offsetY = 0;

    while (string[0]) {
        if (string[0] == '\n') {
            offsetX = 0;
            offsetY += 1;
        } else {
            textPrintCharWin(x + offsetX, y + offsetY, string[0]);
            offsetX += 1;
        }
        string += 1;
    }
}