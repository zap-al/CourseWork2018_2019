#include "CrossFindingInterface.h"
#include "ImgManipInterface.h"
#include "BasisDecompositionInterface.h"
#include <fstream>

using namespace cv;

int main(int argc, char** argv)
{    
    if (argc != 2) { 
        cout << "Error: Wrong count of arguments" << endl;
        return 1;
    }
        
    const enum ImreadModes SCALE = IMREAD_REDUCED_GRAYSCALE_4;
    Mat image;
    image = imread(argv[1], SCALE);

    if (!image.data) {
        cout << "Error: Wrong picture addres" << endl;
        return 1;
    }

    std::cout << "Image: [ " <<  image.rows << " x " << image.cols << " ] px" << std::endl;

    pointXY pFrom;
    pointXY pTo(image.cols / 2., image.rows / 2.);

    pFrom = findCross(image);
    
    ofstream a;
    a.open("/home/meow/CourseWork2018_2019/file.txt");
    for (int i = pFrom.y - 30; i < pFrom.y + 30; i++)
        a << static_cast<int>(image.at<uchar>(Point(400,i))) << " ";        
    a.close();

    improseCrossOnInputImage(image, pFrom);
    printToScreen(image);

    BasisDecomposition(pFrom, pTo);
    
    return 0;
}
