#ifndef _HELPERS_H
#define _HELPERS_H

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3

#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

void clearScreen(void);

UINT8 waitFramesOrKeys(INT8 count);

#endif
