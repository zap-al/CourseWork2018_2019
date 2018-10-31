#include "CrossFindingInterface.h"
#include "FocusFindingInterface.h"
#include "ImgManipInterface.h"

using namespace cv;

int main(int argc, char** argv)
{    
    pointXY crossPoint;
    baseVector a,b;

    validator(argc, argv[1]);

    a = tryMoveA();
    b = tryMoveB();

    findFocus(argv[1]);

    imageClear();

    return 0;
}
