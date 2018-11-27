#include "CrossFindingInterface.h"
#include "ImgManipInterface.h"
#include "BasisDecompositionInterface.h"
//#include "FocusFindingInterface.h"

using namespace cv;
extern Mat image;
extern Mat new_image;

int main(int argc, char** argv)
{    
    const int SIZE = 2048;
    pointXY dagPoint;
    pointXY centerPoint(SIZE/2, SIZE/2);

    validator(argc, argv[1]);
    
    dagPoint = findCross();

    BasisDecomposition(dagPoint, centerPoint);
    
    imageClear();

    return 0;
}
