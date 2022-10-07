/** Typescript OO: interface, class, event, encapsulation, inheritance, polymorphism, etc  
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
* 7. A test class is created for testing
**/

import assert from 'assert';

interface if_display_area {
   get_area(): number; 
}

interface if_display_size {
   get_size(): number; 
}

export interface if_display extends if_display_area, if_display_size {
}

// CLASS zcl_rectangle DEFINITION public create public global friends zcl_test_rectangle.
export default class Rectangle implements if_display {
    protected _length: number;
    protected _width: number;

    static number_of_instance: number;

    constructor(length: number, width: number) {
        this._length = length;
        this._width = width;
        Rectangle.number_of_instance++;
    }

    // This is a static block:
    static {
        Rectangle.number_of_instance = 0;
    }

    get length(): number {
        return this._length;
    } 
    
    get width(): number {
        return this._width;
    } 
    
    set length(length: number) {
        this._length = length;
    }

    set width(width: number) {
        this._width = width;
    } 
    
    get_area(): number {
        return this._length * this._width;
    }

    get_size(): number {
        return 2 * (this._length + this._width);
    }

    static get_number_of_instance(): number {
        return Rectangle.number_of_instance;
    }
}

//* CLASS zcl_square DEFINITION inheriting from zcl_rectangle PUBLIC FINAL CREATE PUBLIC .
export class Square extends Rectangle {
    constructor(side: number) {
        super(side, side);
    }

    get side(): number {
        return this._length;
    } 
    
    set side(side) {
        this.length = this.width = side;
    } 

    get_area(): number {
        return this.side * this.side;
    }

    get_size(): number {
        return 4 * this.side;
    }

    get size(): number {
        return this.get_size();
    }

    get area(): number {
        return this.get_area();
    }
}

class Test_Rectangle {
    static checking: () => void;
}
 
Test_Rectangle.checking = (): void => {
    console.log("Test class Rectangle - Begin")
    try {
        let rect: Rectangle = new Rectangle(10, 20);
        assert.strictEqual(rect.length, 10);
        assert.strictEqual(rect.width, 20);
        assert.strictEqual(rect.get_area(), 200);
        assert.strictEqual(rect.get_size(), 60);
        assert.strictEqual( Rectangle.number_of_instance, 1);

        let disp: if_display;
        disp = <if_display>rect;
        assert.strictEqual(disp.get_area(), 200);
        assert.strictEqual(disp.get_size(), 60);

        let disp_area: if_display_area;
        disp_area = <if_display_area>rect;
        assert.strictEqual(disp_area.get_area(), 200);

        let disp_size: if_display_size;
        disp_size = rect as if_display_size;
        assert.strictEqual(disp_size.get_size(), 60);

        let rect2: Rectangle; 
        rect2 = new Square(5);
        let square1: Square;
        square1 = rect2 as Square; // Widening cast
        assert.ok(rect2);
        assert.ok(square1);
        assert.strictEqual(square1.side, 5);
        assert.strictEqual( Rectangle.number_of_instance, 2);

        square1.side = 7;
        assert.strictEqual(square1.area, 49);

        console.log("Test class Rectangle - End")
    }
    catch(ex: any) {
        console.log({ message: ex.message || ex });
    }
}

export class Circle implements if_display {
    static readonly math_pi: number = 3.1415926;
    private _radius: number;

    constructor(r: number) {
        this._radius = r;
    }
    
    /*
    constructor(c: Circle, aa: boolean) {
        this._radius = c.radius;
    }
    */
        
    get radius(): number { 
        return this._radius; 
    }
        
    get diameter(): number { 
        return 2 * this._radius; 
    }
        
    set radius(radius: number) {
        this._radius = radius;
    }
        
    get_size(): number { 
        return 2 * this._radius * Circle.math_pi;
    } 
    
    get_area(): number { 
        return this._radius * this._radius * Circle.math_pi;
    } 
    
    get size(): number {
        return this.get_size();
    }

    get area(): number {
        return this.get_area();
    }
}

class Test_Circle {
    static checking(): void {
        try {
            console.log("\nCheck Class Circle - Begin"); 
        
            let circle: Circle = new Circle(2.5);
            assert.strictEqual(circle.radius, 2.5);
            assert.strictEqual(circle.diameter, 5.0);
            assert.ok(circle.get_size() >= 15);
            assert.ok(circle.get_area() > 18);
            assert.ok(circle.size >= 15);
            assert.ok(circle.area > 18);

            let d1: if_display_area = <if_display_area>circle;
            assert.ok(d1.get_area() > 18);

            let d: if_display = circle as if_display;
            assert.ok(d.get_size() >= 15);
            assert.ok(d.get_area() > 18);
            console.log("Check Class Circle - End");
        }
        catch(ex: any) {
            console.log({ message: ex.message || ex });
        }
    } 
}


/**
 * Unit Test
 */
if (require.main === module) {
    Test_Rectangle.checking();
    Test_Circle.checking();
}