#include <gb/gb.h>
#include "./start.h"
#include "./studio.h"

void main(void) {
    // Display the splash screen
    splashScreen();

    // Display the home screen
    homeScreen();

    rpgInit();
    
    rpgMain();
}
