#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <chrono>
#include <string>
#include "StructuresInterface.h"

using namespace cv;

pointXY findCross();
void     filtrate();
void     improseCrossOnInputImage(Mat _img, const int _rowOfLine, const int _colOfLine);
void     imageClear();
int      findPos(const int _i, const int _g, int (*f)(int,int));
int      rowPos(const int k, const int j);
int      colPos(const int k, const int j);