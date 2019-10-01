#include "draw.h"


// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    drawFullScreenImageDMA(gameScreen);
    drawString(170, 50, "SCORE:", WHITE);
    UNUSED(state);
}

void unDrawBlock(int loc, Block b) {
    if (loc < 0 || loc > 199) {
        return;
    }
    drawRectDMA(89 + (loc % 10) * 6, 20 + (loc / 10) * 6, 6, 6, BLACK);

    int secLoc = loc;
    if (b.top) {
        secLoc = loc - 10;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.down) {
        secLoc = loc + 10;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.left) {
        secLoc = loc - 1;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.right) {
        secLoc = loc + 1;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.tl) {
        secLoc = loc - 11;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.tr) {
        secLoc = loc - 9;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.dl) {
        secLoc = loc + 9;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.dr) {
        secLoc = loc + 11;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.tt) {
        secLoc = loc - 20;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.dd) {
        secLoc = loc + 20;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.rr) {
        secLoc = loc + 2;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }
    if (b.ll) {
        secLoc = loc - 2;
        drawRectDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, BLACK);
    }

    //UNUSED(b);
}

void drawBlock(int loc, Block b) {
    if (loc < 0 || loc > 199) {
        return;
    }

    drawImageDMA(89 + (loc % 10) * 6, 20 + (loc / 10) * 6, 6, 6, b.image);

    int secLoc = loc;
    if (b.top) {
        secLoc = loc - 10;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.down) {
        secLoc = loc + 10;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.left) {
        secLoc = loc - 1;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.right) {
        secLoc = loc + 1;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.tl) {
        secLoc = loc - 11;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.tr) {
        secLoc = loc - 9;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.dl) {
        secLoc = loc + 9;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.dr) {
        secLoc = loc + 11;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.tt) {
        secLoc = loc - 20;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.dd) {
        secLoc = loc + 20;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.rr) {
        secLoc = loc + 2;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }
    if (b.ll) {
        secLoc = loc - 2;
        drawImageDMA(89 + (secLoc % 10) * 6, 20 + (secLoc / 10) * 6, 6, 6, b.image);
    }

    //UNUSED(b);
}

void drawNextSave(Block b, int loc) {

    drawRectDMA(65 - 6, 32 + loc - 6, 24, 24, BLACK);

    int secLoc = loc;
    drawImageDMA(65, 32 + loc, 6, 6, b.image);
    if (b.top) {
        secLoc = loc - 6;
        drawImageDMA(65, 32 + secLoc, 6, 6, b.image);
    }
    if (b.down) {
        secLoc = loc + 6;
        drawImageDMA(65, 32 + secLoc, 6, 6, b.image);
    }
    if (b.left) {
        secLoc = loc;
        drawImageDMA(65 - 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.right) {
        secLoc = loc;
        drawImageDMA(65 + 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.tl) {
        secLoc = loc - 6;
        drawImageDMA(65 - 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.tr) {
        secLoc = loc - 6;
        drawImageDMA(65 + 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.dl) {
        secLoc = loc + 6;
        drawImageDMA(65 - 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.dr) {
        secLoc = loc + 6;
        drawImageDMA(65 + 6, 32 + secLoc, 6, 6, b.image);
    }
    if (b.tt) {
        secLoc = loc - 12;
        drawImageDMA(65, 32 + secLoc, 6, 6, b.image);
    }
    if (b.dd) {
        secLoc = loc + 12;
        drawImageDMA(65, 32 + secLoc, 6, 6, b.image);
    }
    if (b.rr) {
        secLoc = loc;
        drawImageDMA(65 + 12, 32 + secLoc, 6, 6, b.image);
    }
    if (b.ll) {
        secLoc = loc;
        drawImageDMA(65 - 12, 32 + secLoc, 6, 6, b.image);
    }


}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame.
void undrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    // int controlLoc = state->controlLoc;
    unDrawBlock(state->controlLoc, state->control);

    char str[4];
    sprintf(str, "%d", state->score);
    drawString(210, 50, str, 0x411f);

    // UNUSED(loc);
}

// This function will be used to draw things that might have moved in a frame.
void drawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    static int preArray[200];;

    for (int loc = 0; loc < 200; loc++) {
        if (state->array[loc] != 0 && preArray[loc] == 0) {
            // UNUSED(loc);
            drawImageDMA(89 + (loc % 10) * 6, 20 + (loc / 10) * 6, 6, 6, block);
        } else if (state->array[loc] == 0 && preArray[loc] != 0) {
            drawRectDMA(89 + (loc % 10) * 6, 20 + (loc / 10) * 6, 6, 6, BLACK);
        }
        preArray[loc] = state->array[loc];
    }

    drawBlock(state->controlLoc, state->control);
    drawNextSave(state->next, 0);
    drawNextSave(state->save, 35);

    char str[4];
    sprintf(str, "%d", state->score);
    drawString(210, 50, str, WHITE);
}

