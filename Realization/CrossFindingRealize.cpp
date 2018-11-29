#include "CrossFindingInterface.h"

const double verticalMask  [3][3]={{-1, 2,-1},{-1, 2,-1},{-1, 2,-1}};
const double horisontalMask[3][3]={{-1,-1,-1},{ 2, 2, 2},{-1,-1,-1}};
const double artifactMask  [3][3]={{-1, -1, -1},{ -1, 8, -1},{-1, -1, -1}};

double checkForArtefacts(const int _i, const int _j, const double (*_mask)[3], Mat img){
    double sum{0};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            sum += (img.at<uchar>(_j + j,_i + i) * _mask[i][j]);
    sum -= img.at<uchar>(_j + 1,_i + 1);
    sum /= 8;
    return abs(sum);
}

void filtrate(Mat &image, Mat &new_image){
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
                    sumHorizontal += (image.at<uchar>(i + l,j + k) * verticalMask[k][l]);
            sumVertical = abs(sumVertical);

            if(sumVertical < 30 && sumHorizontal < 30)
                new_image.at<uchar>(i+1,j+1) = 255;
        } 
 
    new_image =  cv::Scalar::all(255) - new_image;
}

void improseCrossOnInputImage(Mat _img, pointXY pCross){
    for(int i = pCross.x - 1; i < pCross.x + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(j,i) = 255;

    for(int i = pCross.y - 1; i < pCross.y + 1; i++)
        for(int j = 0; j < _img.cols; j++)
            _img.at<uchar>(i,j) = 255;
}

pointXY findCross(Mat &image) {
    pointXY res;
    Mat new_image = image.clone();
    
    filtrate(image,new_image);
   
    int rowOfLine{0};
    rowOfLine = findPos(image,new_image, rowPos);

    int colOfLine{0};
    colOfLine = findPos(image, new_image, colPos);

    res.x = rowOfLine;
    res.y = colOfLine;

    improseCrossOnInputImage(new_image, res);

    cout << "Point of cross: " << res.to_string();
    
    return res;
}

int findPos(Mat &image,Mat &new_image, int (*f)(Mat&,int,int)){
    int _i = image.cols;
    int _j = image.rows;
    int maxSum{0};
    int sum{0};
    int res{0};
    for(int i = 1; i < _i - 4; i++){

        sum = 0;

        for(int j = 1; j < _j - 4; j++)
            for(int k = i; k < i + 2; k++)
                sum += f(new_image,k,j);

        if (sum > maxSum)
        {
            maxSum = sum;
            res = i + 1;
        }
    }
    return res;
}

int colPos(Mat &new_image, const int k, const int j){
    return new_image.at<uchar>(k,j);
}

int rowPos(Mat &new_image, const int k, const int j){
    return new_image.at<uchar>(j,k);
}
