#ifndef _TEXT_H
#define _TEXT_H

#define TEXT_OFFSET 0xD0
#define _TEXT_CHAR_A TEXT_OFFSET
#define _TEXT_CHAR_0 TEXT_OFFSET + 26
#define _TEXT_CHAR_TOFU TEXT_OFFSET + 26 + 10 + 9
#define _TEXT_CHAR_SPACE TEXT_OFFSET + 26 + 10 + 11

void textLoadFont();
void textPrintCharBkg(UINT8 x, UINT8 y, unsigned char chr);

#endif