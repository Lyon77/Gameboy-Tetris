#include <stddef.h>
#include "gba.h"
#include "images/orangeBlk.h"
#include "images/yellowBlk.h"
#include "images/blueBlk.h"
#include "images/greenBlk.h"
#include "images/redBlk.h"
#include "images/pinkBlk.h"
#include "images/purpleBlk.h"

typedef struct single {
    // Store whether or not the game is over in this member:
    int top;
    int down;
    int left;
    int right;
    int tl;
    int tr;
    int dl;
    int dr;
    int tt;
    int rr;
    int ll;
    int dd;
    u16 *image;



} Block;

Block randomBlock(void);
Block TBlock(void);
Block LongBlock(void);
Block LBlock(void);
Block JBlock(void);
Block ZBlock(void);
Block SBlock(void);
Block SquareBlock(void);