#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"

void test_trapezoid() {
    std::cout << "Test 1: Trapezoid" << std::endl;
    
    // Создаем симметричную трапецию
    Trapezoid<double> trap(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    // Проверяем центр
    auto center = trap.center();
    assert(std::abs(center.x() - 2.0) < 1e-9);
    assert(std::abs(center.y() - 1.5) < 1e-9);
    
    // Проверяем площадь
    double area = trap.area();
    double expected_area = (4.0 + 2.0) * 3.0 / 2.0;  // (a+b)*h/2
    assert(std::abs(area - expected_area) < 1e-9);
    
    // Проверяем вершины
    auto vertices = trap.vertices();
    assert(vertices.size() == 4);
    
    // Проверяем клонирование
    auto cloned = trap.clone();
    assert(cloned->area() == trap.area());
    
    std::cout << "  ✓ Trapezoid tests passed" << std::endl;
}

void test_rhombus() {
    std::cout << "Test 2: Rhombus" << std::endl;
    
    Rhombus<double> rhombus(
        Point<double>(0, 0),
        6.0,  // diagonal1
        8.0,  // diagonal2
        0.0   // angle
    );
    
    // Проверяем центр
    auto center = rhombus.center();
    assert(center.x() == 0.0);
    assert(center.y() == 0.0);
    
    // Проверяем площадь
    double area = rhombus.area();
    double expected_area = (6.0 * 8.0) / 2.0;
    assert(std::abs(area - expected_area) < 1e-9);
    
    // Проверяем вершины
    auto vertices = rhombus.vertices();
    assert(vertices.size() == 4);
    
    // Проверяем повернутый ромб
    Rhombus<double> rotated_rhombus(
        Point<double>(0, 0),
        6.0,
        8.0,
        3.14159 / 4.0  // 45 градусов
    );
    
    assert(std::abs(rotated_rhombus.area() - expected_area) < 1e-9);
    
    std::cout << "  ✓ Rhombus tests passed" << std::endl;
}

void test_pentagon() {
    std::cout << "Test 3: Pentagon" << std::endl;
    
    Pentagon<double> pentagon(
        Point<double>(0, 0),
        5.0  // radius
    );
    
    // Проверяем центр
    auto center = pentagon.center();
    assert(center.x() == 0.0);
    assert(center.y() == 0.0);
    
    // Проверяем площадь (должна быть положительной)
    double area = pentagon.area();
    assert(area > 0);
    
    // Проверяем вершины
    auto vertices = pentagon.vertices();
    assert(vertices.size() == 5);
    
    // Проверяем приведение к double
    double area_cast = static_cast<double>(pentagon);
    assert(area_cast == area);
    
    std::cout << "  ✓ Pentagon tests passed" << std::endl;
}

void test_figure_comparison() {
    std::cout << "Test 4: Figure comparison" << std::endl;
    
    // Создаем две одинаковые трапеции
    auto trap1 = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    auto trap2 = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    auto trap3 = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(5, 0),  // другое основание
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    // Используем метод equals
    assert(trap1->equals(*trap2));
    assert(!trap1->equals(*trap3));
    
    std::cout << "  ✓ Figure comparison tests passed" << std::endl;
}

void test_polymorphism() {
    std::cout << "Test 5: Polymorphism" << std::endl;
    
    std::shared_ptr<Figure<double>> figures[3];
    
    figures[0] = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    figures[1] = std::make_shared<Rhombus<double>>(
        Point<double>(0, 0), 6, 8
    );
    
    figures[2] = std::make_shared<Pentagon<double>>(
        Point<double>(0, 0), 5
    );
    
    // Проверяем, что все фигуры имеют площадь > 0
    for (auto& fig : figures) {
        assert(fig->area() > 0);
        assert(static_cast<double>(*fig) > 0);
        
        auto vertices = fig->vertices();
        assert(vertices.size() > 0);
    }
    
    std::cout << "  ✓ Polymorphism tests passed" << std::endl;
}

int main() {
    std::cout << "=== Running Figure Tests ===" << std::endl;
    
    test_trapezoid();
    test_rhombus();
    test_pentagon();
    test_figure_comparison();
    test_polymorphism();
    
    std::cout << "\n=== All Figure tests passed! ===" << std::endl;
    return 0;
}