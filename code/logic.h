#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"
#include "block.h"

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    int reset;
    int score;
    Block control;
    Block save;
    Block next;
    int controlLoc;
    int array[200];
    int counter;



} AppState;



// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

int canMove(AppState *currentAppState, char direction);

int move(AppState *currentAppState, char direction);

Block clockwise(AppState *currentAppState);

Block counterClock(AppState *currentAppState);

int canExist(AppState *currentAppState, Block b);

AppState reset(AppState *currentAppState);

void swap(AppState *nextAppState);

#endif
