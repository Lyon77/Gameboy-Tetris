#include "gba.h"
#include "logic.h"
#include "draw.h"

// #include "images/garbage.h"
#include "images/main.h"
#include "images/gameOver.h"

#include <stdio.h>
#include <stdlib.h>

// AppState enum definition
typedef enum {
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

int main(void) {
    // Manipulate REG_DISPCNT here to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // Manipulate the state machine below as needed.
        switch(state) {
            case START:
                // Wait for VBlank
                waitForVBlank();

                //  Draw the start state here.
                drawFullScreenImageDMA(tetrisMain);
                state = START_NODRAW;
                break;
            case START_NODRAW:
                // Check for a button press here to start the app.
                // Start the app by switching the state to APP_INIT.
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    state = APP_INIT;
                    previousButtons = previousButtons | BUTTON_START;
                } else if (!KEY_DOWN(BUTTON_START, currentButtons) && (~previousButtons & BUTTON_START)) {
                    previousButtons = previousButtons & ~BUTTON_START;
                }
                break;
            case APP_INIT:
                // Initialize the app. Switch to the APP state.
                initializeAppState(&currentAppState);

                // Draw the initial state of the app
                fullDrawAppState(&currentAppState);

                state = APP;
                break;
            case APP:

                // Process the app for one frame, store the next state
                nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                // Wait for VBlank before we do any drawing.
                waitForVBlank();

                // Undraw the previous state
                undrawAppState(&currentAppState);

                // Draw the current state
                drawAppState(&nextAppState);

                // Now set the current state as the next state for the next iter.
                currentAppState = nextAppState;

                // Check if the app is exiting. If it is, then go to the exit state.
                if (nextAppState.gameOver) {
                    state = APP_EXIT;
                } else if (nextAppState.reset) {
                    state = START;
                }

                break;
            case APP_EXIT:
                // Wait for VBlank
                waitForVBlank();

                //Draw the exit / gameover screen
                drawFullScreenImageDMA(gameOver);

                state = APP_EXIT_NODRAW;
                break;
            case APP_EXIT_NODRAW:
                if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
                    state = START;
                    previousButtons = previousButtons | BUTTON_SELECT;
                } else if (!KEY_DOWN(BUTTON_SELECT, currentButtons) && (~previousButtons & BUTTON_SELECT)) {
                    previousButtons = previousButtons & ~BUTTON_SELECT;
                }

                //Check for a button press here to go back to the start screen
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    state = START;
                    previousButtons = previousButtons | BUTTON_START;
                } else if (!KEY_DOWN(BUTTON_START, currentButtons) && (~previousButtons & BUTTON_START)) {
                    previousButtons = previousButtons & ~BUTTON_START;
                }

                break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
