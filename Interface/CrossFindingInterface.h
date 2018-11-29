#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <chrono>
#include <string>
#include "StructuresInterface.h"

using namespace cv;

pointXY findCross(Mat &image);
void     filtrate();
void     improseCrossOnInputImage(Mat _img, pointXY pCross);
void     imageClear();
int      findPos(Mat &image,Mat &new_image, int (*f)(Mat&,int,int));
int      rowPos(Mat &new_image, const int k, const int j);
int      colPos(Mat &new_image, const int k, const int j);