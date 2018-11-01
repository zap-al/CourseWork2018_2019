#include "CrossFindingInterface.h"

const double verticalMask  [3][3]={{-1, 2,-1},{-1, 2,-1},{-1, 2,-1}};
const double horisontalMask[3][3]={{-1,-1,-1},{ 2, 2, 2},{-1,-1,-1}};
const double artifactMask  [3][3]={{-1, -1, -1},{ -1, 8, -1},{-1, -1, -1}};

Mat image;
Mat new_image;

baseMove operator - (pointXY a, pointXY b){
    baseMove res;
    res.xDist = a.x - b.x;
    res.yDist = a.y - b.y;
    return res;
}

baseMove tryMoveA(){
    baseMove res;
    pointXY from, to;
    from = findCross();
    //FP_SetAMoveTo(1); допустим сдвинули на 1 такт вверх
    to = findCross();
    //FP_SetAMoveTo(-1); потом вернули обратно
    res.xDist = to.x - from.x;
    res.yDist = to.y - from.y;
    return res;
}

baseMove tryMoveB(){
    baseMove res;
    pointXY from, to;
    from = findCross();
    //FP_SetBMoveTo(1); допустим сдвинули на 1 такт вверх
    to = findCross();
    //FP_SetBMoveTo(-1); потом вернули обратно
    res.xDist = to.x - from.x;
    res.yDist = to.y - from.y;
    return res;
}

baseMove tryMoveC(){
    baseMove res;
    pointXY from, to;
    from = findCross();
    //FP_SetCMoveTo(1); допустим сдвинули на 1 такт вверх
    to = findCross();
    //FP_SetCMoveTo(-1); потом вернули обратно
    res.xDist = to.x - from.x;
    res.yDist = to.y - from.y;
    return res;
}

pointXY pointXY::operator = (const pointXY& a){
    pointXY res;
    res.x = a.x;
    res.y = a.y;
    return res;
}

double checkForArtefacts(const int _i, const int _j, const double (*_mask)[3], Mat img){
    double sum{0};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sum += (img.at<uchar>(_j + j,_i + i) * _mask[i][j]);
    sum -= img.at<uchar>(_j + 1,_i + 1);
    sum /= 8;
    return abs(sum);
}

void filtrate(){

    double sumHorizontal{0};
    double sumVertical{0};
    for(int i = 0; i < image.rows - 1; i++)
        for(int j = 0; j < image.cols - 1; j++)   
        {    
            sumHorizontal = 0;
            for(int k = 0; k < 3; k++)
                for(int l = 0; l < 3; l++)
                    sumHorizontal += (image.at<uchar>(i + l,j + k) * horisontalMask[k][l]);
            sumHorizontal = abs(sumHorizontal);

            sumVertical = 0;
            for(int k = 0; k < 3; k++)
                for(int l = 0; l < 3; l++)
                    sumHorizontal += (image.at<uchar>(i + l,j + k) * horisontalMask[k][l]);
            sumVertical = abs(sumVertical);

            if(sumVertical < 30 && sumHorizontal < 30)
                new_image.at<uchar>(i+1,j+1) = 255;
        } 
 
    new_image =  cv::Scalar::all(255) - new_image;
}

void improseCrossOnInputImage(Mat _img, const int _rowOfLine, const int _colOfLine){
    for(int i = _rowOfLine - 1; i < _rowOfLine + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(j,i) = 255;

    for(int i = _colOfLine - 1; i < _colOfLine + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(i,j) = 255;
}

void imageClear(){
    for(int i = 0; i < new_image.rows; i++)
        for(int j = 0; j < new_image.cols; j++)
            if(new_image.at<uchar>(j,i) < 255)
                new_image.at<uchar>(j,i) = 0;
}

pointXY findCross(){
    pointXY res;
    
    filtrate();
   
    int rowOfLine{0};
    rowOfLine = findPos(image.cols, image.rows, rowPos);
    std:: cout << "Row of line is: " << rowOfLine << std::endl;

    int colOfLine{0};
    colOfLine = findPos(image.rows, image.cols, colPos);
    std:: cout << "Col of line is: " << colOfLine << std::endl;
    
    improseCrossOnInputImage(new_image, rowOfLine, colOfLine);

    res.x = colOfLine;
    res.y = rowOfLine;
    return res;
}

int findPos(const int _i, const int _j, int (*f)(int,int)){
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

int colPos(const int k, const int j){
    return new_image.at<uchar>(k,j);
}

int rowPos(const int k, const int j){
    return new_image.at<uchar>(j,k);
}
