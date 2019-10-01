#include "block.h"

Block randomBlock(void) {
    int num = randint(1, 8);
    Block control = LBlock();
    switch (num) {
        case 1:
            control = TBlock();
            break;
        case 2:
            control = LBlock();
            break;
        case 3:
            control = JBlock();
            break;
        case 4:
            control = SquareBlock();
            break;
        case 5:
            control = ZBlock();
            break;
        case 6:
            control = SBlock();
            break;
        case 7:
            control = LongBlock();
            break;
    }
    return control;
}

Block TBlock(void) {
    Block control;

    control.top = 1;
    control.left = 0;
    control.down = 1;
    control.right = 1;
    control.tl = 0;
    control.tr = 0;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = blueBlk;
    return control;
}
Block LongBlock(void) {
    Block control;

    control.top = 0;
    control.left = 1;
    control.down = 0;
    control.right = 1;
    control.tl = 0;
    control.tr = 0;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 1;
    control.ll = 0;
    control.image = orangeBlk;
    return control;
}
Block LBlock(void) {
    Block control;

    control.top = 0;
    control.left = 1;
    control.down = 0;
    control.right = 1;
    control.tl = 0;
    control.tr = 1;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = purpleBlk;
    return control;
}
Block JBlock(void) {
    Block control;

    control.top = 0;
    control.left = 1;
    control.down = 0;
    control.right = 1;
    control.tl = 1;
    control.tr = 0;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = greenBlk;
    return control;
}
Block ZBlock(void) {
    Block control;

    control.top = 1;
    control.left = 0;
    control.down = 0;
    control.right = 1;
    control.tl = 1;
    control.tr = 0;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = pinkBlk;
    return control;
}
Block SBlock(void) {
    Block control;

    control.top = 1;
    control.left = 1;
    control.down = 0;
    control.right = 0;
    control.tl = 0;
    control.tr = 1;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = redBlk;
    return control;
}
Block SquareBlock(void) {
    Block control;

    control.top = 1;
    control.left = 1;
    control.down = 0;
    control.right = 0;
    control.tl = 1;
    control.tr = 0;
    control.dl = 0;
    control.dr = 0;
    control.tt = 0;
    control.dd = 0;
    control.rr = 0;
    control.ll = 0;
    control.image = yellowBlk;
    return control;
}