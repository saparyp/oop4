#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include "../include/Array.h"
#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"

void test_integration_complete() {
    std::cout << "Test: Complete system integration" << std::endl;
    
    using FigurePtr = std::shared_ptr<Figure<double>>;
    Array<FigurePtr> figures;
    
    // Создаем разнообразные фигуры
    auto trapezoid = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(5, 0),
        Point<double>(4, 3),
        Point<double>(1, 3)
    );
    
    auto rhombus = std::make_shared<Rhombus<double>>(
        Point<double>(10, 5),
        6.0,
        8.0,
        0.785398  // 45 градусов в радианах
    );
    
    auto pentagon = std::make_shared<Pentagon<double>>(
        Point<double>(20, 10),
        4.0
    );
    
    // Добавляем в массив
    figures.push_back(trapezoid);
    figures.push_back(rhombus);
    figures.push_back(pentagon);
    
    // Проверяем размер
    assert(figures.size() == 3);
    
    // Проверяем полиморфное поведение
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        auto& fig = figures[i];
        
        // Все методы должны работать полиморфно
        double area = fig->area();
        auto center = fig->center();
        auto vertices = fig->vertices();
        
        assert(area > 0);
        assert(vertices.size() > 0);
        
        total_area += area;
        
        // Проверяем приведение к double
        double casted_area = static_cast<double>(*fig);
        assert(std::abs(area - casted_area) < 1e-9);
    }
    
    // Проверяем общую площадь через метод массива
    double array_total_area = figures.totalArea();
    assert(std::abs(total_area - array_total_area) < 1e-9);
    
    // Проверяем операции с массивом
    assert(!figures.empty());
    
    // Клонируем первую фигуру
    auto cloned = figures[0]->clone();
    assert(std::abs(figures[0]->area() - cloned->area()) < 1e-9);
    
    // Проверяем сравнение
    assert(figures[0]->equals(*cloned));
    
    // Удаляем фигуру
    size_t initial_size = figures.size();
    figures.remove(1);
    assert(figures.size() == initial_size - 1);
    
    // Очищаем массив
    figures.clear();
    assert(figures.empty());
    assert(figures.size() == 0);
    
    std::cout << "  ✓ Complete integration test passed" << std::endl;
}

void test_different_coord_types() {
    std::cout << "Test: Different coordinate types" << std::endl;
    
    // Тестируем с разными типами координат
    {
        Array<std::shared_ptr<Figure<int>>> int_figures;
        auto trap_int = std::make_shared<Trapezoid<int>>(
            Point<int>(0, 0),
            Point<int>(4, 0),
            Point<int>(3, 3),
            Point<int>(1, 3)
        );
        int_figures.push_back(trap_int);
        assert(int_figures.size() == 1);
    }
    
    {
        Array<std::shared_ptr<Figure<float>>> float_figures;
        auto trap_float = std::make_shared<Trapezoid<float>>(
            Point<float>(0.0f, 0.0f),
            Point<float>(4.0f, 0.0f),
            Point<float>(3.0f, 3.0f),
            Point<float>(1.0f, 3.0f)
        );
        float_figures.push_back(trap_float);
        assert(float_figures.size() == 1);
    }
    
    std::cout << "  ✓ Different coordinate types test passed" << std::endl;
}

void test_move_semantics_array() {
    std::cout << "Test: Move semantics in Array" << std::endl;
    
    // Создаем массив с маленькой начальной емкостью
    Array<std::shared_ptr<Figure<double>>> figures(2);
    
    // Заполняем до ресайза
    auto fig1 = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(2, 0),
        Point<double>(1.5, 1),
        Point<double>(0.5, 1)
    );
    
    auto fig2 = std::make_shared<Rhombus<double>>(
        Point<double>(5, 5), 3, 4
    );
    
    auto fig3 = std::make_shared<Pentagon<double>>(
        Point<double>(10, 10), 2
    );
    
    figures.push_back(fig1);
    figures.push_back(fig2);
    
    // Сохраняем указатели для проверки
    auto saved_ptr1 = figures[0];
    auto saved_ptr2 = figures[1];
    
    // Добавляем третий элемент - произойдет ресайз с move
    figures.push_back(fig3);
    
    // Проверяем, что указатели остались валидными
    assert(figures[0] == saved_ptr1);
    assert(figures[1] == saved_ptr2);
    assert(figures[2] == fig3);
    
    std::cout << "  ✓ Move semantics test passed" << std::endl;
}

int main() {
    std::cout << "=== Running Integration Tests ===" << std::endl;
    
    test_integration_complete();
    test_different_coord_types();
    test_move_semantics_array();
    
    std::cout << "\n=== All Integration tests passed! ===" << std::endl;
    return 0;
}