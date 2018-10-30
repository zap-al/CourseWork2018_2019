#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <chrono>
#include <string>

using namespace cv;

void   printToPictureFile(Mat,std::string);
void   printToTextFile(Mat);
void   printToScreen(Mat);
void   checkByMasks(int,int);
void   improseCross(Mat,int,int);
void   validator(int, char*);
void   filtrate();
void   imageClear();
void   findCross();
int    findPos(int,int, int (*f)(int,int));
int    rowPos(int,int);
int    colPos(int,int);