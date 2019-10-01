#include "logic.h"

//initalizes start state of the gameboy
void initializeAppState(AppState* appState) {
    appState->gameOver = 0;
    appState->reset = 0;
    appState->control = randomBlock();
    appState->save = randomBlock();
    appState->next = randomBlock();
    appState->controlLoc = 14;
    for(int i = 0; i < 200; i++ ) {
        appState->array[i] = 0;
    }
    appState->score = 0;
    appState->counter = 0;
}


// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
     /* To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     */

    AppState nextAppState = *currentAppState;

    if(currentAppState->counter == 30) {
        //move block down one
        if (canMove(currentAppState, 'd')) {
            nextAppState.controlLoc = move(currentAppState, 'd');
        } else {
            nextAppState = reset(currentAppState);
        }
        nextAppState.counter = 0;
    } else {
        //Down, Left, Right, A, B
        //inefficient code
        if (KEY_JUST_PRESSED(BUTTON_DOWN, keysPressedNow, keysPressedBefore)) {
            while(canMove(&nextAppState, 'd')) {
                nextAppState.controlLoc = move(&nextAppState, 'd');
            }
            nextAppState = reset(&nextAppState);
            keysPressedBefore = keysPressedBefore | BUTTON_DOWN;
        } else if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore)) {
            if (canMove(currentAppState, 'l')) {
                nextAppState.controlLoc = move(currentAppState, 'l');
            }
            keysPressedBefore = keysPressedBefore | BUTTON_LEFT;
        } else if (KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore)) {
            if (canMove(currentAppState, 'r')) {
                nextAppState.controlLoc = move(currentAppState, 'r');
            }
            keysPressedBefore = keysPressedBefore | BUTTON_RIGHT;
        } else if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
            nextAppState.control = clockwise(currentAppState);
            keysPressedBefore = keysPressedBefore | BUTTON_A;
        } else if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
            nextAppState.control = counterClock(currentAppState);
            keysPressedBefore = keysPressedBefore | BUTTON_B;
        } else if (KEY_JUST_PRESSED(BUTTON_SELECT, keysPressedNow, keysPressedBefore)) {
            nextAppState.reset = 1;
            keysPressedBefore = keysPressedBefore | BUTTON_SELECT;
        } else if (KEY_JUST_PRESSED(BUTTON_L, keysPressedNow, keysPressedBefore)) {
            swap(&nextAppState);
            keysPressedBefore = keysPressedBefore | BUTTON_L;
        } else if (KEY_JUST_PRESSED(BUTTON_R, keysPressedNow, keysPressedBefore)) {
            keysPressedBefore = keysPressedBefore | BUTTON_R;
        }

        if (!KEY_DOWN(BUTTON_DOWN, keysPressedNow) && (~keysPressedBefore & BUTTON_DOWN)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_DOWN;
        }
        if (!KEY_DOWN(BUTTON_LEFT, keysPressedNow) && (~keysPressedBefore & BUTTON_LEFT)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_LEFT;
        }
        if (!KEY_DOWN(BUTTON_RIGHT, keysPressedNow) && (~keysPressedBefore & BUTTON_RIGHT)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_RIGHT;
        }
        if (!KEY_DOWN(BUTTON_A, keysPressedNow) && (~keysPressedBefore & BUTTON_A)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_A;
        }
        if (!KEY_DOWN(BUTTON_B, keysPressedNow) && (~keysPressedBefore & BUTTON_B)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_B;
        }
        if (!KEY_DOWN(BUTTON_L, keysPressedNow) && (~keysPressedBefore & BUTTON_L)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_L;
        }
        if (!KEY_DOWN(BUTTON_R, keysPressedNow) && (~keysPressedBefore & BUTTON_R)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_R;
        }
        if (!KEY_DOWN(BUTTON_SELECT, keysPressedNow) && (~keysPressedBefore & BUTTON_SELECT)) {
            keysPressedBefore = keysPressedBefore & ~BUTTON_SELECT;
        }

        nextAppState.counter++;
    }

    //check for complete row
    int amount = 0;
    for (int i = 0; i < 20; i++) {
        int check = 1;
        for (int j = 0; j < 10; j++) {
            if (nextAppState.array[(19 - i) * 10 + j] == 0) {
                check = 0;
                break;
            }
        }
        for (int j = 0; j < 10; j++) {
            nextAppState.array[((19 - i) * 10 + j) + 10 * amount] = nextAppState.array[(19 - i) * 10 + j];
        }
        if (check) {
            for (int j = 0; j < 10; j++) {
                nextAppState.array[(19 - i) * 10 + j] = 0;
            }
            amount++;
            nextAppState.score++;
        }
    }

    return nextAppState;
}

int canMove(AppState *currentAppState, char direction) {
    int *array = currentAppState->array;
    int loc = currentAppState->controlLoc;
    Block b = currentAppState->control;
    if(direction == 'l') {
        if(b.top) {
            int copy = loc;
            copy -= 10;
            if(copy % 10 == 0 || array[copy - 1] != 0) {
                return 0;
            }
        }
        if(b.down) {
            int copy = loc;
            copy += 10;
            if(copy % 10 == 0 || array[copy - 1] != 0) {
                return 0;
            }
        }
        if(b.left) {
            int copy = loc;
            copy -= 1;
            if(copy % 10 == 0 || array[copy - 1] != 0) {
                return 0;
            }
        }
        if(b.tl) {
            int copy = loc;
            copy -= 11;
            if(copy % 10 == 0 || array[copy - 1] != 0) {
                return 0;
            }
        }
        if(b.dl) {
            int copy = loc;
            copy += 9;
            if(copy % 10 == 0 || array[copy - 1] != 0) {
                return 0;
            }
        }
        if(b.tt) {
            int copy = loc;
            copy -= 20;
            if(copy % 10 == 0 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.dd) {
            int copy = loc;
            copy += 20;
            if(copy % 10 == 0 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.ll) {
            int copy = loc;
            copy -= 2;
            if(copy % 10 == 0 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(loc % 10 == 0 || array[loc - 1] != 0) {
            return 0;
        }
    } else if (direction == 'r') {
        if(b.top) {
            int copy = loc;
            copy -= 10;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.down) {
            int copy = loc;
            copy += 10;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.right) {
            int copy = loc;
            copy += 1;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(loc % 10 == 9 || array[loc + 1] != 0) {
            return 0;
        }
        if(b.tr) {
            int copy = loc;
            copy -= 9;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.dr) {
            int copy = loc;
            copy += 11;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.tt) {
            int copy = loc;
            copy -= 20;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.dd) {
            int copy = loc;
            copy += 20;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
        if(b.rr) {
            int copy = loc;
            copy += 2;
            if(copy % 10 == 9 || array[copy + 1] != 0) {
                return 0;
            }
        }
    } else if (direction == 'd') {
        if(b.down) {
            int copy = loc;
            copy += 10;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.left) {
            int copy = loc;
            copy -= 1;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.right) {
            int copy = loc;
            copy += 1;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.tl) {
            int copy = loc;
            copy -= 11;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.tr) {
            int copy = loc;
            copy -= 9;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.dl) {
            int copy = loc;
            copy += 9;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.dr) {
            int copy = loc;
            copy += 11;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(loc + 10 >= 200 || array[loc + 10] != 0) {
            return 0;
        }
        if(b.tt) {
            int copy = loc;
            copy -= 20;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.ll) {
            int copy = loc;
            copy -= 2;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.dd) {
            int copy = loc;
            copy += 20;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(b.rr) {
            int copy = loc;
            copy += 2;
            if(copy + 10 >= 200 || array[copy + 10] != 0) {
                return 0;
            }
        }
        if(loc + 10 >= 200 || array[loc + 10] != 0) {
            return 0;
        }
    }

    return 1;
}

int move(AppState *currentAppState, char direction) {
    int loc = currentAppState->controlLoc;
    int newLoc = loc;
    if(direction == 'l') {
        newLoc--;
    } else if (direction == 'r') {
        newLoc++;
    } else if (direction == 'd') {
        newLoc += 10;
    }

    return newLoc;
}

Block clockwise(AppState *currentAppState) {
    Block b_real = currentAppState->control;
    Block b = b_real;

    int copy = b.top;
    b.top = b.left;
    b.left = b.down;
    b.down = b.right;
    b.right = copy;
    int copy2 = b.tl;
    b.tl = b.dl;
    b.dl = b.dr;
    b.dr = b.tr;
    b.tr = copy2;
    int copy3 = b.tt;
    b.tt = b.ll;
    b.ll = b.dd;
    b.dd = b.rr;
    b.rr = copy3;

    if (canExist(currentAppState, b)) {
        return b;
    }

    return b_real;
}

Block counterClock(AppState *currentAppState) {
    Block b_real = currentAppState->control;
    Block b = b_real;

    int copy = b.top;
    b.top = b.right;
    b.right = b.down;
    b.down = b.left;
    b.left = copy;
    int copy2 = b.tl;
    b.tl = b.tr;
    b.tr = b.dr;
    b.dr = b.dl;
    b.dl = copy2;
    int copy3 = b.tt;
    b.tt = b.rr;
    b.rr = b.dd;
    b.dd = b.ll;
    b.ll = copy3;

    if (canExist(currentAppState, b)) {
        return b;
    }

    return b_real;
}

int canExist(AppState *currentAppState, Block b) {
    int loc = currentAppState->controlLoc;
    int *array = currentAppState->array;

    if(b.top) {
        int copy = loc;
        copy -= 10;
        if(array[copy] != 0) {
            return 0;
        }
    }
    if(b.down) {
        int copy = loc;
        copy += 10;
        if(copy >= 200 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.left) {
        int copy = loc;
        copy -= 1;
        if(copy % 10 == 9 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.right) {
        int copy = loc;
        copy += 1;
        if(copy % 10 == 0 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.tl) {
        int copy = loc;
        copy -= 11;
        if(copy % 10 == 9 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.tr) {
        int copy = loc;
        copy -= 9;
        if(copy % 10 == 0 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.dl) {
        int copy = loc;
        copy += 9;
        if(copy >= 200 || copy % 10 == 9 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.dr) {
        int copy = loc;
        copy += 11;
        if(copy >= 200 || copy % 10 == 0 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.tt) {
        int copy = loc;
        copy -= 20;
        if(array[copy] != 0) {
            return 0;
        }
    }
    if(b.dd) {
        int copy = loc;
        copy += 20;
        if(copy >= 200 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.rr) {
        int copy = loc;
        copy += 2;
        if(copy % 10 == 0 || array[copy] != 0) {
            return 0;
        }
    }
    if(b.ll) {
        int copy = loc;
        copy -= 2;
        if(copy % 10 == 9 || array[copy] != 0) {
            return 0;
        }
    }

    return 1;
}

AppState reset(AppState *currentAppState) {
    AppState nextAppState = *currentAppState;

    nextAppState.array[currentAppState->controlLoc] = 1;

    Block b = currentAppState->control;
    if(b.top) {
        nextAppState.array[currentAppState->controlLoc - 10] = 1;
    }
    if(b.down) {
        nextAppState.array[currentAppState->controlLoc + 10] = 1;
    }
    if(b.left) {
        nextAppState.array[currentAppState->controlLoc - 1] = 1;
    }
    if(b.right) {
        nextAppState.array[currentAppState->controlLoc + 1] = 1;
    }
    if(b.tl) {
        nextAppState.array[currentAppState->controlLoc - 11] = 1;
    }
    if(b.tr) {
        nextAppState.array[currentAppState->controlLoc - 9] = 1;
    }
    if(b.dl) {
        nextAppState.array[currentAppState->controlLoc + 9] = 1;
    }
    if(b.dr) {
        nextAppState.array[currentAppState->controlLoc + 11] = 1;
    }
    if(b.tt) {
        nextAppState.array[currentAppState->controlLoc - 20] = 1;
    }
    if(b.dd) {
        nextAppState.array[currentAppState->controlLoc + 20] = 1;
    }
    if(b.ll) {
        nextAppState.array[currentAppState->controlLoc - 2] = 1;
    }
    if(b.rr) {
        nextAppState.array[currentAppState->controlLoc + 2] = 1;
    }


    nextAppState.controlLoc = 14;

    if(!canExist(&nextAppState, nextAppState.next)) {
        nextAppState.gameOver = 1;
    }

    nextAppState.control = nextAppState.next;
    nextAppState.next = randomBlock();
    return nextAppState;
}

void swap(AppState* nextAppState) {
    if (canExist(nextAppState, nextAppState->save)) {
        Block copy = nextAppState->save;
        nextAppState->save = nextAppState->control;
        nextAppState->control = copy;
    }
}