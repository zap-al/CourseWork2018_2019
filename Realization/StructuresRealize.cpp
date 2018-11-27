#include "StructuresInterface.h"

void pointXY::operator = (pointXY a){
    pointXY res;
    x = a.x;
    y = a.y;
}

void pointXY::operator += (pointXY a) {
    x += a.x;
    y += a.y;
}

pointXY operator - (pointXY a, pointXY b) {
    pointXY res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}
