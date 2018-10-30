#include "interface.h"

using namespace cv;

extern Mat image;
extern Mat new_image;

const int CROSS_X = 1098;
const int CROOS_Y = 1239;

Mat pictureOfCross;
int mask[4][8];
void findFocus(char*argv);
void createMask();

int main(int argc, char** argv)
{    
    validator(argc, argv[1]);
    
    findFocus(argv[1]);

    return 0;
}

void findFocus(char*argv){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            mask[i][j] = i*j;
        }
    }

    pictureOfCross = imread(argv);

    if(!pictureOfCross.data){
        std::cerr << "нет информации по фотке";
    }else{
        namedWindow("Display", WINDOW_AUTOSIZE);
        imshow("Display", pictureOfCross);
        waitKey(0);
        destroyWindow("Display");
    }
    
    createMask();

    
}

void createMask(){
    for(int i = CROOS_Y - 3; i < CROOS_Y + 4; i++){
        for(int j = CROSS_X - 3; j < CROSS_X + 4; j++){
            mask[i-CROOS_Y + 3][j-CROSS_X + 3] = image.at<uchar>(j,i);
        }
    }
    namedWindow("test",WINDOW_AUTOSIZE);
    Mat pic;
    pic.create(8,8, CV_8UC(1));
    imshow("test",pic);
    waitKey(0);
    destroyWindow("test");
    std::cout << "M = " << std::endl << " " << pic << std::endl << std::endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pic.at<uchar>(j,i) = mask[i][j];
            std::cout <<"works";
        }
    }
    namedWindow("Cross", WINDOW_AUTOSIZE);
    imshow("Cross", pic);
    waitKey(0);
    destroyAllWindows();
}