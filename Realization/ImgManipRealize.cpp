#include "ImgManipInterface.h"


extern Mat image;
extern Mat new_image;

void printToPictureFile(const std::string outWay){

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

void validator(const int _argc, const char* arg){
    if ( _argc < 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        exit(0);
    }
    image = imread(arg, IMREAD_REDUCED_GRAYSCALE_2);
    new_image = imread(arg, IMREAD_REDUCED_GRAYSCALE_2);

    if (!image.data)
    {
        printf("No image data \n");
        exit(0);
    }
    
    std::cout << "Image: [ " <<  image.rows << " x " << image.cols << " ] px" << std::endl;
}
