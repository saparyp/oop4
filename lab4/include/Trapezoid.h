#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> vertices_;
    
public:
    Trapezoid(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
        vertices_.reserve(4);
        vertices_.push_back(std::make_unique<Point<T>>(a));
        vertices_.push_back(std::make_unique<Point<T>>(b));
        vertices_.push_back(std::make_unique<Point<T>>(c));
        vertices_.push_back(std::make_unique<Point<T>>(d));
    }
    
    Trapezoid(const Trapezoid& other) {
        for (const auto& v : other.vertices_) {
            vertices_.push_back(std::make_unique<Point<T>>(*v));
        }
    }
    
    Trapezoid& operator=(const Trapezoid& other) {
        if (this != &other) {
            vertices_.clear();
            for (const auto& v : other.vertices_) {
                vertices_.push_back(std::make_unique<Point<T>>(*v));
            }
        }
        return *this;
    }
    
    Trapezoid(Trapezoid&& other) noexcept = default;
    Trapezoid& operator=(Trapezoid&& other) noexcept = default;
    
    Point<T> center() const override {
        T sumX = 0, sumY = 0;
        for (const auto& v : vertices_) {
            sumX += v->x();
            sumY += v->y();
        }
        return Point<T>(sumX / 4, sumY / 4);
    }
    
    double area() const override {
        double a = vertices_[0]->distanceTo(*vertices_[1]);
        double b = vertices_[2]->distanceTo(*vertices_[3]);
        double h = std::abs(vertices_[0]->y() - vertices_[2]->y());
        return (a + b) * h / 2.0;
    }
    
    void print() const override {
        std::cout << "Trapezoid";
    }
    
    std::vector<std::unique_ptr<Point<T>>> vertices() const override {
        std::vector<std::unique_ptr<Point<T>>> copy;
        for (const auto& v : vertices_) {
            copy.push_back(std::make_unique<Point<T>>(*v));
        }
        return copy;
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Trapezoid<T>>(*this);
    }
    
    bool equals(const Figure<T>& other) const override {
        if (auto* o = dynamic_cast<const Trapezoid*>(&other)) {
            if (vertices_.size() != o->vertices_.size()) {
                return false;
            }
            for (size_t i = 0; i < vertices_.size(); ++i) {
                if (*vertices_[i] != *o->vertices_[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

#endif // TRAPEZOID_H