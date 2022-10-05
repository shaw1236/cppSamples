/** C++ OO: interface, class, event, encapsulation, inheritance, polymorphism, etc  
**
** Purpose: Sample to create class, interface and use them
**
** Author : Simon Li  Jan 2019
**
* 1. Create two interfaces: if_display_area, if_display_szie
*    define two apis: get_area() and get_size() respectively
* 2. Integrate the two interfaces into a new interface if_display
* 3. Create a class rectanlge to implement the interface methods,
*    track any new creation on the class and instance level
* 4. Create a sub class square to overwrite the two methods
* 5. Create a class to receive the events and collect the rectange instanaces
* 6. some Sample code for how to use the class and instances
* 7. A friend class is created for testing
**/
#ifndef _RECTANGLET_
#define _RECTANGLET_

#include <iostream>     
#include <cassert>  
#include <vector>

using namespace std;

template <class _T>
class Display_AreaT {
    public: 
        virtual _T get_area() = 0; 
};

template <class _T>
class Display_SizeT {
   public:
        virtual _T get_size() = 0;
}; 

template <class _T>
class DisplayT: public Display_SizeT<_T>, Display_AreaT<_T> {
    static double math_pi; 
};
template <class _T>
double DisplayT<_T>::math_pi = 3.1415926;

template <class _T = int>
class RectangleT : public DisplayT<_T> {
    friend class Test_RectangleT; // friend class

    private: // access to the same class only
        static int number_of_instance;
    
    protected:
        _T length, width;

    public:
        RectangleT(_T l, _T w) : length(l), width(w) {
            RectangleT::number_of_instance++;
        }

        ~RectangleT() {
            RectangleT::number_of_instance--;
        }

        _T get_length() { return length; }
        
        _T get_width() { return width; }
        
        void set_length(_T length) {
            this->length = length;
        }
        
        // Implicitly assign this way
        // Rectangle &operator=(Rectangle &other) { return other; }

        RectangleT &operator+(RectangleT &other) {
            length += other.length;
            width += other.width;
            return *this;
        }

        RectangleT &operator+=(RectangleT &other) {
            return *this + other;
        }

        RectangleT &operator++(int) {
            this->length++;
            this->width++;
            return *this;
        }

        RectangleT &operator--(int) {
            if (length > 0) length -= 1;
            if (width > 0) width -= 1;
            return *this;
        }

        void set_width(_T width) {
            this->width = width;
        }

        _T get_area() { 
            return length * width;
        } 
    
        _T get_size() {
            return (length + width) * 2;
        }

        static int get_number_of_instance() {
            return number_of_instance;
        }
};

template<class _T>
int RectangleT<_T>::number_of_instance = 0;

// CLASS zcl_square DEFINITION inheriting from zcl_rectangle PUBLIC FINAL CREATE PUBLIC .
template <class _T = int>
class SquareT : public RectangleT<_T> {
  public: 
    SquareT(_T side);
    _T get_side();
    void set_side(_T);
    _T get_area();
    _T get_size();
};

template <class _T>
SquareT<_T>::SquareT(_T side) : RectangleT<_T>(side, side) { }

template <class _T>
_T SquareT<_T>::get_side() { return RectangleT<_T>::get_length(); } 
  
template <class _T>
void SquareT<_T>::set_side(_T side) { this->length = this->width = side; }

template <class _T>
_T SquareT<_T>::get_area() { return this->length * this->length; }

template <class _T>
_T SquareT<_T>::get_size() { return this->length * 4; }

class Test_RectangleT {
    public:
        static void checking();
};

void Test_RectangleT::checking() {
    try {
        cout << "\nCheck Class RectangleT - Begin" << endl; 

        // Container for the points, the actual objects are still outside
        vector<RectangleT<int> *> vec;        
        // Instance
        RectangleT<int> rect(10, 20); // new an instance
        vec.push_back(&rect);

        assert(rect.length == 10);
        assert(rect.width == 20);
        assert(rect.get_area() == 200);
        assert(rect.get_size() == 60);
        assert(RectangleT<int>::number_of_instance == 1);
    
        // reference to the instance
        RectangleT<int> refRect = rect;  // reference to "rect"
        assert(refRect.get_size() == 60);
        assert(RectangleT<int>::get_number_of_instance() == 1);

        // point to the instance
        RectangleT<int> *pRect = &refRect;   // point to the reference, i.e. point to the original "rect"
        assert(pRect->get_size() == 60);
        assert(RectangleT<int>::get_number_of_instance() == 1);

        // Square
        RectangleT<int> *pRect2 = NULL; 
        pRect2 = new SquareT<int>(5.0);
        vec.push_back(pRect2);
        assert(pRect2);
        SquareT<int> *square1 = (SquareT<int> *)pRect2; 
        assert(square1);
        assert(square1->get_side() == 5);
        assert(RectangleT<int>::number_of_instance == 2);
        
        RectangleT<int> *pRect3 = square1;
        assert(pRect3);
        assert(RectangleT<int>::number_of_instance == 2);
        
        delete square1; // destruct an object
        vec.pop_back();
        pRect2 = pRect3 = square1 = NULL;
        assert(RectangleT<int>::number_of_instance == 1);

        RectangleT<int> *p2 = new RectangleT<int>(2, 3);
        assert(RectangleT<int>::number_of_instance == 2);
        vec.push_back(p2);
        //cout << "Number of Instances: " << Rectangle::get_number_of_instance() << endl;

        assert(vec.size() == 2);
        assert(vec[0]->width == 20);
        assert(vec[1]->get_area() == 6);
      
        // Check operators 
        rect += *p2;
        //rect = rect + *p2;
        rect++;
        rect--;
        assert(RectangleT<int>::number_of_instance == 2);
        // cout << "Number of Instances: " << Rectangle::get_number_of_instance() << endl;
        // cout << "Rect: " << rect.get_length() << endl;
        // cout << "p2: " << p2->get_length() << endl;
        
        cout << "Check Class RectangleT - End" << endl; 
    }
    catch(const char *ex) {
        cerr << ex << endl;
    }
};

#endif