#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <vector>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print() const = 0;
    virtual std::vector<std::unique_ptr<Point<T>>> vertices() const = 0;
    
    virtual explicit operator double() const {
        return area();
    }
    
    virtual std::shared_ptr<Figure<T>> clone() const = 0;
    
    virtual bool equals(const Figure<T>& other) const = 0;
};

#endif // FIGURE_H