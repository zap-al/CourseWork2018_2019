#include "ImgManipInterface.h"

void printToPictureFile(const std::string outWay, Mat &new_image){

    std::cout << "mew" << std::endl;
    imwrite(outWay, new_image);
}

void printToTextFile(const Mat img, const std::string outWay){
    std::ofstream out(outWay);
    out << img;
    out.close();
}

void printToScreen(const Mat _image){
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", _image);
    waitKey(0);
}


