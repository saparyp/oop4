#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <concepts>
#include <cmath>
#include <type_traits>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;
    
public:
    Point(T x = 0, T y = 0) : x_(x), y_(y) {}
    
    T x() const { return x_; }
    T y() const { return y_; }
    
    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }
    
    double distanceTo(const Point<T>& other) const {
        return std::sqrt(std::pow(x_ - other.x_, 2) + std::pow(y_ - other.y_, 2));
    }
    
    bool operator==(const Point<T>& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
    
    Point<T> operator+(const Point<T>& other) const {
        return Point<T>(x_ + other.x_, y_ + other.y_);
    }
    
    Point<T> operator/(T divisor) const {
        return Point<T>(x_ / divisor, y_ / divisor);
    }
    
    Point<T> operator-(const Point<T>& other) const {
        return Point<T>(x_ - other.x_, y_ - other.y_);
    }
    
    Point<T> operator*(T factor) const {
        return Point<T>(x_ * factor, y_ * factor);
    }
};

#endif // POINT_H