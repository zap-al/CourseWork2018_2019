#include "CrossFindingInterface.h"
#include "ImgManipInterface.h"
#include "BasisDecompositionInterface.h"
#include <fstream>
//#include "FocusFindingInterface.h"

using namespace cv;
extern Mat image;
extern Mat new_image;

int main(int argc, char** argv)
{    
    const enum ImreadModes scale = IMREAD_REDUCED_GRAYSCALE_4;
    const int SIZE = (scale == IMREAD_GRAYSCALE) ? 2048 : (16384 / scale);
    pointXY pFrom;
    pointXY pTo(SIZE/2, SIZE/2);
    
    validator(argc, argv[1], scale);

    pFrom = findCross();
    
    ofstream a;
    a.open("/home/meow/CourseWork2018_2019/file.txt");
    for (int i = pFrom.y - 30; i < pFrom.y + 30; i++)
        a << static_cast<int>(image.at<uchar>(Point(400,i))) << " ";        
    a.close();

    improseCrossOnInputImage(image, pFrom);

    BasisDecomposition(pFrom, pTo);
    printToScreen(image);
    printToScreen(new_image);
    
    imageClear();

    return 0;
}
