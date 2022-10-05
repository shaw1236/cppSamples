//#include <iostream>
//using namespace std;
#include "Circle.h"
#include "Rectangle.h"
#include "RectangleT.h"
#include "Calculator.h"
#include "AsmCalculator.h"
#include "ClassTemplate.h"

/** Build:
 *  MinGW-W64 under Windows 10 
 *  [c++|g++] run.cpp -o run
**/
int main(int argc, char *argv[]) {
    Test_Rectangle *p = new Test_Rectangle();
    p->checking();

    Test_RectangleT::checking();
    Test_Circle::run();
    Test_Calculator::run();
    Test_ClassTemplate::run();
    Test_AsmCalculator::run();

    return 0;
}