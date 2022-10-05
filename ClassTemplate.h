#ifndef _CLASSTEMPLATE_
#define _CLASSTEMPLATE_

#include <iostream>
using namespace std;

// Class template with multiple and default parameters
template <class T, class U, class V = char>
class ClassTemplate {
    friend class Test_ClassTemplate;
    private:
        T var1;
        U var2;
        V var3;

    public:
        ClassTemplate(T v1, U v2, V v3) : var1(v1), var2(v2), var3(v3) {}  // constructor
        ~ClassTemplate() {}
        void printVar() {
            cout << "var1 = " << var1 << endl;
            cout << "var2 = " << var2 << endl;
            cout << "var3 = " << var3 << endl;
        }
};

class Test_ClassTemplate {
    public:
        static int run();
};

int Test_ClassTemplate::run() {
    cout << "\nCheck Class ClassTemplate - Begin" << endl; 
        
    // create object with int, double and char types
    ClassTemplate<int, double> obj1(7, 7.7, 'c');
    cout << "obj1 values: " << endl;
    obj1.printVar();
    cout << "private member: " << obj1.var2 << endl; // friend class assessing a private memeber is okay


    // create object with int, double and bool types
    ClassTemplate<double, char, bool> obj2(8.8, 'a', false);
    cout << "\nobj2 values: " << endl;
    obj2.printVar();
    cout << "Check Class ClassTemplate - End" << endl; 
    
    return 0;
};

#endif