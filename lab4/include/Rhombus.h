#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <numbers>
#include <type_traits>

template<typename T>
class Rhombus : public Figure<T> {
private:
    static_assert(std::is_arithmetic_v<T>, "Rhombus coordinates must be arithmetic types");
    
    std::unique_ptr<Point<T>> center_;
    T diagonal1, diagonal2;
    double angle;
    
public:
    Rhombus(Point<T> center, T d1, T d2, double angle = 0) 
        : center_(std::make_unique<Point<T>>(center)), 
          diagonal1(d1), diagonal2(d2), angle(angle) {}
    
    Rhombus(const Rhombus& other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          diagonal1(other.diagonal1),
          diagonal2(other.diagonal2),
          angle(other.angle) {}
    
    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            diagonal1 = other.diagonal1;
            diagonal2 = other.diagonal2;
            angle = other.angle;
        }
        return *this;
    }
    
    Rhombus(Rhombus&& other) noexcept = default;
    Rhombus& operator=(Rhombus&& other) noexcept = default;
    
    Point<T> center() const override {
        return *center_;
    }
    
    double area() const override {
        return (diagonal1 * diagonal2) / 2.0;
    }
    
    void print() const override {
        std::cout << "Rhombus";
    }
    
    std::vector<std::unique_ptr<Point<T>>> vertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        vertices.reserve(4);
        
        double cosA = std::cos(angle);
        double sinA = std::sin(angle);
        
        vertices.push_back(std::make_unique<Point<T>>(
            center_->x() + diagonal1/2 * cosA,
            center_->y() + diagonal1/2 * sinA
        ));
        
        vertices.push_back(std::make_unique<Point<T>>(
            center_->x() - diagonal2/2 * sinA,
            center_->y() + diagonal2/2 * cosA
        ));
        
        vertices.push_back(std::make_unique<Point<T>>(
            center_->x() - diagonal1/2 * cosA,
            center_->y() - diagonal1/2 * sinA
        ));
        
        vertices.push_back(std::make_unique<Point<T>>(
            center_->x() + diagonal2/2 * sinA,
            center_->y() - diagonal2/2 * cosA
        ));
        
        return vertices;
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Rhombus<T>>(*this);
    }
    
    bool equals(const Figure<T>& other) const override {
        if (auto* o = dynamic_cast<const Rhombus*>(&other)) {
            return *center_ == *o->center_ && 
                   diagonal1 == o->diagonal1 && 
                   diagonal2 == o->diagonal2 &&
                   std::abs(angle - o->angle) < 1e-9;
        }
        return false;
    }
};

#endif // RHOMBUS_H