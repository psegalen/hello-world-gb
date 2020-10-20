#ifndef _TEXT_H
#define _TEXT_H

#define TEXT_OFFSET 0xD0
#define _TEXT_CHAR_A              TEXT_OFFSET
#define _TEXT_CHAR_0              TEXT_OFFSET + 26
#define _TEXT_CHAR_APOSTROPHE     TEXT_OFFSET + 26 + 10 + 0
#define _TEXT_CHAR_DASH           TEXT_OFFSET + 26 + 10 + 1
#define _TEXT_CHAR_DOT            TEXT_OFFSET + 26 + 10 + 2
#define _TEXT_CHAR_COMMA          TEXT_OFFSET + 26 + 10 + 3
#define _TEXT_CHAR_COLON          TEXT_OFFSET + 26 + 10 + 4
#define _TEXT_CHAR_EXCLAMATION    TEXT_OFFSET + 26 + 10 + 5
#define _TEXT_CHAR_INTERROGATION  TEXT_OFFSET + 26 + 10 + 6
#define _TEXT_CHAR_LPARENTHESES   TEXT_OFFSET + 26 + 10 + 7
#define _TEXT_CHAR_RPARENTHESES   TEXT_OFFSET + 26 + 10 + 8
#define _TEXT_CHAR_TOFU           TEXT_OFFSET + 26 + 10 + 9
#define _TEXT_CHAR_BORDER         TEXT_OFFSET + 26 + 10 + 10
#define _TEXT_CHAR_SPACE          TEXT_OFFSET + 26 + 10 + 11


void textLoadFont();
void textPrintCharWin(UINT8 x, UINT8 y, unsigned char chr);
void textPrintStringWin(UINT8 x, UINT8 y, unsigned char *string);

#endif