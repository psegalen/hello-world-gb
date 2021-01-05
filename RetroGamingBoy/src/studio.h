#ifndef _STUDIO_H
#define _STUDIO_H

#define MESSAGE_BOX_INITIAL_Y   (18 * 8) + 16
#define MESSAGE_BOX_FINAL_Y     ((18 * 8) + 16) - (5 * 8)

void displayMap(void);

void movePlayer(INT8 dX, INT8 dY);

void rpgInit(void);

void rpgMain(void);

void showMessagBox(void);

void showMessage(unsigned char* message);

void hideMessageBox(void);

#endif
