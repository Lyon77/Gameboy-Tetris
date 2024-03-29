#ifndef DRAW_H
#define DRAW_H

#include "logic.h"
#include <stdio.h>
#include "images/block.h"
#include "gba.h"
#include "images/gameScreen.h"

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state);

void unDrawBlock(int loc, Block b);
void drawBlock(int loc, Block b);
void drawNextSave(Block b, int loc);


// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state);



#endif
