#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <type_traits>
#include <cmath>

template<typename T>
class Pentagon : public Figure<T> {
private:
    static_assert(std::is_arithmetic_v<T>, "Pentagon coordinates must be arithmetic types");
    
    std::unique_ptr<Point<T>> center_;
    T radius;
    
public:
    Pentagon(Point<T> center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius(radius) {}
    
    Pentagon(const Pentagon& other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          radius(other.radius) {}
    
    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            radius = other.radius;
        }
        return *this;
    }
    
    Pentagon(Pentagon&& other) noexcept = default;
    Pentagon& operator=(Pentagon&& other) noexcept = default;
    
    Point<T> center() const override {
        return *center_;
    }
    
    double area() const override {
        const double pi = 3.14159265358979323846;
        double side = 2 * radius * std::sin(pi / 5);
        return (5.0 / 4.0) * side * side * (1.0 / std::tan(pi / 5));
    }
    
    void print() const override {
        std::cout << "Pentagon";
    }
    
    std::vector<std::unique_ptr<Point<T>>> vertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        vertices.reserve(5);
        
        const double pi = 3.14159265358979323846;
        for (int i = 0; i < 5; ++i) {
            double angle = 2 * pi * i / 5;
            vertices.push_back(std::make_unique<Point<T>>(
                center_->x() + radius * std::cos(angle),
                center_->y() + radius * std::sin(angle)
            ));
        }
        
        return vertices;
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Pentagon<T>>(*this);
    }
    
    bool equals(const Figure<T>& other) const override {
        if (auto* o = dynamic_cast<const Pentagon*>(&other)) {
            return *center_ == *o->center_ && radius == o->radius;
        }
        return false;
    }
};

#endif // PENTAGON_H