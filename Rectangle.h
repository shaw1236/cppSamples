/** C++ OO: class, encapsulation, inheritance, polymorphism, etc  
**
** Purpose: Sample to create classes and use them
**
** Author : Simon Li  Jan 2019
**
* 1. Create two virtual classes: Display_Area, Display_Size
*    define two apis: get_area() and get_size() respectively
* 2. Integrate the two virtual classes into a new virtual class Display
* 3. Create a class Rectanlge to implement the virtual class methods,
*    track any new creation on the class and instance level
* 4. Create a sub class Square to overwrite the two methods
* 5. A friend class is created for testing
**/
#ifndef _RECTANGLE_
#define _RECTANGLE_

#include <iostream>     
#include <cassert>  
using namespace std;

class Display_Area {
    public: 
        virtual int get_area() = 0; 
};

class Display_Size {
   public:
        virtual int get_size() = 0;
}; 

class Display : public virtual Display_Area, public virtual Display_Size {
};

class Rectangle : public virtual Display {
    friend class Test_Rectangle; // friend class

    private: // access to the same class only
        static int number_of_instance;
    
    protected:
        int length, width;

    public:
        Rectangle(int length, int width) {
            this->length = length;
            this->width = width;
            Rectangle::number_of_instance++;
        }

        ~Rectangle() {
            Rectangle::number_of_instance--;
        }

        int get_length() { return length; }
        
        int get_width() { return width; }
        
        void set_length(int length) {
            this->length = length;
        }
        
        // Implicitly assign this way
        // Rectangle &operator=(Rectangle &other) { return other; }

        Rectangle &operator+(Rectangle &other) {
            length += other.length;
            width += other.width;
            return *this;
        }

        Rectangle &operator+(int num) {
            length += num;
            width += num;
            return *this;
        }

        Rectangle &operator+=(Rectangle &other) {
            return *this + other;
        }

        Rectangle &operator++(int) {
            this->length++;
            this->width++;
            return *this;
        }

        Rectangle &operator--(int) {
            if (length > 0) length--;
            if (width > 0) width--;
            return *this;
        }

        void set_width(int width) {
            this->width = width;
        }

        int get_area() { 
            return length * width;
        } 
    
        int get_size() {
            return (length + width) * 2;
        }

        static int get_number_of_instance() {
            return number_of_instance;
        }
};

int Rectangle::number_of_instance = 0;

// CLASS zcl_square DEFINITION inheriting from zcl_rectangle PUBLIC FINAL CREATE PUBLIC .
class Square : public Rectangle {
  public: 
    Square(int side);
    int get_side();
    void set_side(int);
    int get_area();
    int get_size();
};

Square::Square(int side) : Rectangle(side, side) { }

int Square::get_side() {
    return get_length();
} 
  
void Square::set_side(int side) { 
    length = width = side;
}
    
int Square::get_area() {
    //return Rectangle::get_area();
    return length * length;
}

int Square::get_size() {
    return length * 4;
}

class Test_Rectangle {
    public:
        void checking();
};

void Test_Rectangle::checking() {
    try {
        cout << "\nCheck Class Rectangle - Begin" << endl; 
        
        // Instance
        Rectangle rect(10, 20); // new an instance
        assert(rect.length == 10);
        assert(rect.width == 20);
        assert(rect.get_area() == 200);
        assert(rect.get_size() == 60);
        assert(Rectangle::number_of_instance == 1);
    
        // reference to the instance
        Rectangle refRect = rect;  // reference to "rect"
        assert(refRect.get_size() == 60);
        assert(Rectangle::get_number_of_instance() == 1);

        // point to the instance
        Rectangle *pRect = &refRect;   // point to the reference, i.e. point to the original "rect"
        assert(pRect->get_size() == 60);
        assert(Rectangle::get_number_of_instance() == 1);

        Rectangle *pRect2 = NULL; 
        pRect2 = new Square(5);
   
        assert(pRect2);
        Square *square1 = (Square *)pRect2; 
        assert(square1);
        assert(square1->get_side() == 5);
        assert(Rectangle::number_of_instance == 2);
        
        Rectangle *pRect3 = square1;
        assert(pRect3);
        assert(Rectangle::number_of_instance == 2);
        
        delete square1; // destruct an object
        pRect2 = pRect3 = square1 = NULL;
        assert(Rectangle::number_of_instance == 1);

        Rectangle *p2 = new Rectangle(2, 3);
        assert(Rectangle::number_of_instance == 2);
        //cout << "Number of Instances: " << Rectangle::get_number_of_instance() << endl;

        rect += *p2;
        //rect = rect + *p2;
        rect++;
        rect--;
        assert(Rectangle::number_of_instance == 2);
        
        // cout << "Number of Instances: " << Rectangle::get_number_of_instance() << endl;
        // cout << "Rect: " << rect.get_length() << endl;
        // cout << "p2: " << p2->get_length() << endl;
        
        cout << "Check Class Rectangle - End" << endl; 
        
    }
    catch(const char *ex) {
        cerr << ex << endl;
    }
};

#endif