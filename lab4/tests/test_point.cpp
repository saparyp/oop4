#include <iostream>
#include <cassert>
#include <type_traits>
#include "../include/Point.h"

void test_point_creation() {
    std::cout << "Test 1: Point creation and accessors" << std::endl;
    
    Point<int> p1(10, 20);
    assert(p1.x() == 10);
    assert(p1.y() == 20);
    
    Point<double> p2(3.14, 2.71);
    assert(std::abs(p2.x() - 3.14) < 1e-9);
    assert(std::abs(p2.y() - 2.71) < 1e-9);
    
    std::cout << "  ✓ Point creation passed" << std::endl;
}

void test_point_operations() {
    std::cout << "Test 2: Point operations" << std::endl;
    
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    
    // Тестируем сложение
    auto p3 = p1 + p2;
    assert(std::abs(p3.x() - 4.0) < 1e-9);
    assert(std::abs(p3.y() - 6.0) < 1e-9);
    
    // Тестируем деление
    auto p4 = p1 / 2.0;
    assert(std::abs(p4.x() - 0.5) < 1e-9);
    assert(std::abs(p4.y() - 1.0) < 1e-9);
    
    // Тестируем вычитание
    auto p5 = p2 - p1;
    assert(std::abs(p5.x() - 2.0) < 1e-9);
    assert(std::abs(p5.y() - 2.0) < 1e-9);
    
    // Тестируем умножение
    auto p6 = p1 * 3.0;
    assert(std::abs(p6.x() - 3.0) < 1e-9);
    assert(std::abs(p6.y() - 6.0) < 1e-9);
    
    // Тестируем расстояние
    double distance = p1.distanceTo(p2);
    double expected = std::sqrt(std::pow(1.0-3.0, 2) + std::pow(2.0-4.0, 2));
    assert(std::abs(distance - expected) < 1e-9);
    
    std::cout << "  ✓ Point operations passed" << std::endl;
}

void test_point_comparison() {
    std::cout << "Test 3: Point comparison" << std::endl;
    
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(5, 15);
    
    assert(p1 == p2);
    assert(p1 != p3);
    assert(!(p1 == p3));
    
    std::cout << "  ✓ Point comparison passed" << std::endl;
}

void test_concept_validation() {
    std::cout << "Test 4: Concept validation (compile-time)" << std::endl;
    
    // Эти строки должны компилироваться
    Point<int> pi;
    Point<double> pd;
    Point<float> pf;
    
    // Проверяем статическое утверждение
    static_assert(std::is_same_v<decltype(pi.x()), int>);
    static_assert(std::is_same_v<decltype(pd.x()), double>);
    
    std::cout << "  ✓ Concept validation passed" << std::endl;
}

int main() {
    std::cout << "=== Running Point Tests ===" << std::endl;
    
    test_point_creation();
    test_point_operations();
    test_point_comparison();
    test_concept_validation();
    
    std::cout << "\n=== All Point tests passed! ===" << std::endl;
    return 0;
}