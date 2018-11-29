#include "BasisDecompositionInterface.h"

int stepCout(pointXY pStart, pointXY pEnd, pointXY pMove) { 
    int countOfSteps;
    int direct;
    double checkDist;
    double distanceToendPoint;
    double moveLenght;

    distanceToendPoint = abs(sqrt(pow(pEnd.x - pStart.x, 2) + pow(pEnd.y - pStart.y, 2)));
    moveLenght = abs(sqrt(pow(pMove.x, 2) + pow(pMove.y, 2)));
    
    countOfSteps = 0;
    
    checkDist = distanceToendPoint;
    while (distanceToendPoint > moveLenght / 2.) { 
        countOfSteps++;
        distanceToendPoint -= moveLenght;
    }

    pStart += pMove;

    distanceToendPoint = abs(sqrt(pow(pEnd.x - pStart.x, 2) + pow(pEnd.x - pStart.x, 2)));

    direct = distanceToendPoint > checkDist ? -1 : 1;

    countOfSteps *= direct;
    return countOfSteps;
}

void BasisDecomposition(pointXY pNow,  pointXY pCenter)
{
    pointXY pCross;
    pointXY pMove1(30,2);
    pointXY pMove2(2,30);

    cout << "Move1: " << pMove1.to_string();
    cout << "Move2: " << pMove2.to_string();

    double k1, k2, k3, b1, b2, b3;
    int countOfSteps{0};

    //find equation for (1) mooving
    k1 = pMove1.y / pMove1.x;
    b1 = pNow.y - k1 * pNow.x;
    //find equation for (2) mooving
    k2 = pMove2.y / pMove2.x;
    b2 = pNow.y - k2 * pNow.x;

    //draw a line throw 1 equation, then cross we want find relatively 2 equation 
    k3 = k1;
    b3 = pCenter.y - k3 * pCenter.x;

    //find pointXY of both (2) and (3) equation
    pCross.x = (b3-b2) / (k2-k3);
    pCross.y = k3 * pCross.x + b3;


    //to finding direction ov moves we try to move in the same direction as at begin
    //and if distance became bigger, we start movint in opposite direction    
    
    countOfSteps = stepCout(pNow, pCross, pMove2);
    cout << "We want make " << countOfSteps  << " steps by (2) engine " << endl;

    countOfSteps = stepCout(pCross, pCenter, pMove1);
    cout << "We want make " << countOfSteps << " steps by (1) engine " << endl << endl;
}
