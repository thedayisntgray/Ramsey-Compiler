#include <iostream>
#include <string>

class Shape{
public:
    Shape();
    virtual ~Shape() {};
    
    Shape(const Color& c);

    virtual void        color(Color c)              {this->colur = c; }
    Color       color() const;  
    
    virtual double      area() const = 0;
    virtual double      perimeter() const = 0;
    virtual void        move(double x, double y) = 0;

    virtual std::ostream&   render(std::ostream& os) const = 0;
private:
    Color colur;
};