
#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <iostream>
using namespace std;

template <class T>
class Calculator {
    friend class Test_Calculator;
    private:
        T num1, num2;

    public:
        Calculator(T n1, T n2) : num1(n1), num2(n2) {}
        ~Calculator() {}

        void displayResult() {
            cout << "Numbers: " << num1 << " and " << num2 << "." << endl;
            cout << num1 << " + " << num2 << " = " << add() << endl;
            cout << num1 << " - " << num2 << " = " << subtract() << endl;
            cout << num1 << " * " << num2 << " = " << multiply() << endl;
            cout << num1 << " / " << num2 << " = " << divide() << endl;
        }

        T add() { return num1 + num2; }
        T subtract() { return num1 - num2; }
        T multiply() { return num1 * num2; }
        T divide() { return num1 / num2; }
};

class Test_Calculator {
    public:
        static void run();
};

void Test_Calculator::run() {
    cout << "\nCheck Class Calculator - Begin" << endl; 
        
    Calculator<int> intCalc(2, 1);
    Calculator<float> floatCalc(2.4, 1.2);
    cout << "private member: " << intCalc.num1 << endl; // friend class assessing a private memeber is okay

    cout << "Int results:" << endl;
    intCalc.displayResult();

    cout << endl << "Float results:" << endl;
    floatCalc.displayResult();
    cout << "Check Class Calculator - End" << endl; 
   
};

#endif