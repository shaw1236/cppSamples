#ifndef _CIRCLE_
#define _CIRCLE_

#include <iostream>     
#include <cassert>  
using namespace std;

class Display_Area_D {
    public: 
        virtual double get_area() = 0; 
};

class Display_Size_D {
   public:
        virtual double get_size() = 0;
}; 

class Display_D : public virtual Display_Area_D, public virtual Display_Size_D {
    public:
        static double math_pi; 
};
double Display_D::math_pi = 3.1415926;

class Circle : public virtual Display_D {
    friend class Test_Circle; // friend class

    protected:
        double radius;

    public:
        Circle(double r) : radius(r) { }
        Circle(Circle &c) : radius(c.radius) { }
        Circle(Circle *pc) : radius(pc->radius) { }
        ~Circle() { }

        double get_radius() { return radius; }
        
        double get_diameter() { return 2 * radius; }
        
        void set_radius(double radius) {
            this->radius = radius;
        }
        
        Circle &operator+(double r) {
            radius += r;
            return *this;
        }

        Circle &operator+=(double r) {
            return *this + r;
        }

        Circle &operator++(int) {
            radius += 1;
            return *this;
        }

        Circle &operator--(int) {
            if (radius > 1) 
                radius -= 1;
            return *this;
        }

        double get_area() { 
            return radius * radius * Display_D::math_pi;
        } 
    
        double get_size() {
            return 2 * radius * Display_D::math_pi;
        }

};

class Test_Circle {
    public:
        static void run();
};

void Test_Circle::run() {
    cout << "\nCheck Class Circle - Begin" << endl; 
        
    Circle circle(2.5);
    assert(circle.get_radius() >= 2.5);
    assert(circle.get_diameter() >= 5);
    assert(circle.get_size() >= 15);
    assert(circle.get_area() > 18);

    Display_Area_D *d1 = &circle;
    assert(d1->get_area() > 18);

    Display_D *d = &circle;
    assert(d->get_size() >= 15);
    assert(d->get_area() > 18);
    cout << "Check Class Circle - End" << endl; 
}

#endif

