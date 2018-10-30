#include "interface.h"

using namespace cv;

Mat image;
Mat new_image;

const double verticalMask  [3][3]={{-1, 2,-1},{-1, 2,-1},{-1, 2,-1}};
const double horisontalMask[3][3]={{-1,-1,-1},{ 2, 2, 2},{-1,-1,-1}};
const double artifactMask  [3][3]={{-1, -1, -1},{ -1, 8, -1},{-1, -1, -1}};


void validator(int _argc, char* arg){
    if ( _argc < 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        exit(0);
    }
    image = imread(arg, IMREAD_GRAYSCALE);
    new_image = imread(arg, IMREAD_GRAYSCALE);

    if (!image.data)
    {
        printf("No image data \n");
        exit(0);
    }
    
    std::cout << "Rows: " << image.rows << std::endl;
    std::cout << "Cols: " << image.cols << std::endl;

}

double checkByMask(int _j, int _i, const double (*_mask)[3]){
    double sum{0};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sum += (image.at<uchar>(_j + j,_i + i) * _mask[i][j]);
    return abs(sum);
}

double checkForArtefacts(int _i, int _j, const double (*_mask)[3], Mat img){
    double sum{0};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sum += (img.at<uchar>(_j + j,_i + i) * _mask[i][j]);
    sum -= img.at<uchar>(_j + 1,_i + 1);
    sum /= 8;
    return abs(sum);
}

void printToPictureFile(Mat img, std::string *way){

    std::cout << "mew" << std::endl;
    imwrite(*way, img);
}

void printToTextFile(Mat img){
    std::ofstream out("out.txt");
    out << new_image;
    out.close();
}

void improseCross(Mat _img, int _rowOfLine, int _colOfLine){
    for(int i = _rowOfLine - 1; i < _rowOfLine + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(j,i) = 255;

    for(int i = _colOfLine - 1; i < _colOfLine + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(i,j) = 255;
}

void filtrate(){
    for(int i = 0; i < image.rows - 1; i++)
        for(int j = 0; j < image.cols - 1; j++)   
        {
            if(checkByMask(i, j, horisontalMask) < 30 && checkByMask(i, j,verticalMask) < 30)
                new_image.at<uchar>(i+1,j+1) = 255;
        } 
 
    new_image =  cv::Scalar::all(255) - new_image;
}

void imageClear(){
    for(int i = 0; i < image.rows; i++)
        for(int j = 0; j < image.cols; j++)
            if(new_image.at<uchar>(j,i) < 255)
                new_image.at<uchar>(j,i) = 0;
}

void printToScreen(Mat _image){
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", _image);
    waitKey(0);
}

int findPos(int _i, int _j, int (*f)(int,int)){
    int maxSum{0};
    int sum{0};
    int res{0};
    for(int i = 1; i < _i - 4; i++){

        sum = 0;

        for(int j = 1; j < _j - 4; j++)
            for(int k = i; k < i + 2; k++)
                sum += f(k,j);

        if (sum > maxSum)
        {
            maxSum = sum;
            res = i + 1;
        }
    }
    return res;
}

void findCross(){

    filtrate();
   
    int rowOfLine{0};
    rowOfLine = findPos(image.cols, image.rows, rowPos);
    std:: cout << "Row of line is: " << rowOfLine << std::endl;

    int colOfLine{0};
    colOfLine = findPos(image.rows, image.cols, colPos);
    std:: cout << "Col of line is: " << colOfLine << std::endl;
    
    improseCross(new_image, rowOfLine, colOfLine);

    imwrite("/home/meow/Pictures/out.png", new_image);
}

int colPos(int k, int j){return new_image.at<uchar>(k,j);}

int rowPos(int k, int j){return new_image.at<uchar>(j,k);}