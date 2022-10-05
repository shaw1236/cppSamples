#ifndef _ASMCALCULATOR_
#define _ASMCALCULATOR_

#include <cstdio>
#include <iostream>
using namespace std;

class AsmCalculator {
    friend class Test_AsmCalculator;
    private:
        int num1, num2;

    public:
        AsmCalculator(int n1, int n2) : num1(n1), num2(n2) {}
        ~AsmCalculator() {}

        void displayResult() {
            int divides[2];
            divide(&divides[0]); // divide(divides);

            cout << "Numbers: " << num1 << " and " << num2 << "." << endl;
            cout << num1 << " + " << num2 << " = " << add() << endl;
            cout << num1 << " - " << num2 << " = " << subtract() << endl;
            cout << num1 << " * " << num2 << " = " << multiply() << endl;
            cout << num1 << " / " << num2 << " = " << (int)divides[0] << endl;
            cout << num1 << " % " << num2 << " = " << (int)divides[1] << endl;
            cout << "gcd(" << num1 << "," << num2 << ") = " << gcd() << endl;
        
        }

        int add() {
            int res;
            // "a"(num1): num1 -> %eax, "b"(num2): num2 -> %ebx, "=a"(res): %eax -> res
            asm("addl %%ebx, %%eax;" : "=a"(res) : "a"(num1), "b"(num2)); 
            return res; 
        }

        int subtract() { 
            int res;
            // "a"(num1): num1 -> %eax, "b"(num2): num2 -> %ebx, "=a"(res): %eax -> res
            asm("subl %%ebx, %%eax;" : "=a"(res) : "a"(num1), "b"(num2)); 
            return res; 
        }

        int multiply() { 
            int res;
            // "a"(num1): num1 -> %eax, "b"(num2): num2 -> %ebx, "=a"(res): %eax -> res
            asm("imul %%ebx, %%eax;" : "=a"(res) : "a"(num1), "b"(num2)); 
            return res;
        }

        void divide(int *res) { // (int res[])
            // "a"(num1): num1 -> %eax, "b"(num2): num2 -> %ebx, "=a"(res[0]): %eax -> res[0], "=d"(res[1]): %edx -> res[1] 
            asm("movl $0x0, %%edx;" /* clean %edx for idivl %edx:%eax */ 
                "idivl %%ebx;" : "=a"(res[0]), "=d"(res[1]) : "a"(num1), "b"(num2)); 
        }

        int gcd() {
            int res;
            /* Compute Greatest Common Divisor using Euclid's Algorithm */
            /*"DONE: movl %%eax, %0;" : "=g"(result) : "a"(a), "b"(b) */
            asm("CONTD: cmpl $0, %%ebx;" // %ebx vs 0
                "je DONE;"
                "xorl %%edx, %%edx;" // eq "movl 0x0, %%edx;" 
                "idivl %%ebx;"       // %eax / %ebx
                "movl %%ebx, %%eax;" // %ebx -> %eax
                "movl %%edx, %%ebx;" // %edx -> %ebx
                "jmp CONTD;"
                "DONE: movl %%eax, %0;" : "=g"(res) : "a"(num1), "b"(num2)
            );

            return res;
        }
};

class Test_AsmCalculator {
    public:
        static void run();
};

void Test_AsmCalculator::run() {
    cout << "\nCheck Class AsmCalculator" << endl; 
        
    AsmCalculator intCalc(25, 10);

    cout << "Int results:" << endl;
    intCalc.displayResult();
};

#endif