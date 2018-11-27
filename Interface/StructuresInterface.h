#pragma once
#include <string>

using namespace std;

struct pointXY{
    double x;
    double y;
    pointXY():x(0),y(0){};
    pointXY(const int _x, const int _y):x(_x),y(_y){};
    void operator += (pointXY);
    void operator = (pointXY);   
    string to_string() {
        string res("[ " + std::to_string(x) + " , " + std::to_string(y) + " ]\n");
        return res;
    }
};


struct baseMove{
    int xDist;
    int yDist;
};

baseMove operator - (baseMove a, baseMove b);

pointXY operator - (pointXY a, pointXY b);