#include "CrossFindingInterface.h"
#include "FocusFindingInterface.h"
#include "ImgManipInterface.h"

using namespace cv;

int main(int argc, char** argv)
{    
    const int SIZE = 2048;
    pointXY crossPoint;
    pointXY centerPoint(SIZE/2, SIZE/2);
    baseMove a,b;
    baseMove vectToCenter;

    validator(argc, argv[1]);

    a = tryMoveA();
    b = tryMoveB();
    
    crossPoint = findCross();
    
    vectToCenter = crossPoint - centerPoint;

    findFocus(argv[1]);

    imageClear();

    return 0;
}
