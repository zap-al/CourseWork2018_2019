#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <chrono>
#include <string>

using namespace cv;

void   validator(const int argc,const char*arg, enum cv::ImreadModes scale);
void   printToPictureFile(const std::string outWay);    
void   printToTextFile(const Mat img, const std::string outWay);      
void   printToScreen(const Mat img);             