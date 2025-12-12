#include <iostream>
#include <memory>
#include "../include/Point.h"
#include "../include/Figure.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"

using CoordType = double;
using FigurePtr = std::shared_ptr<Figure<CoordType>>;

int main() {
    std::cout << "Testing Array with base Figure pointers" << std::endl;
    
    Array<FigurePtr> figures;
    
    auto trapezoid = std::make_shared<Trapezoid<CoordType>>(
        Point<CoordType>(0, 0),
        Point<CoordType>(4, 0),
        Point<CoordType>(3, 3),
        Point<CoordType>(1, 3)
    );
    
    auto rhombus = std::make_shared<Rhombus<CoordType>>(
        Point<CoordType>(5, 5), 6, 8, 0.5
    );
    
    auto pentagon = std::make_shared<Pentagon<CoordType>>(
        Point<CoordType>(10, 10), 5
    );
    
    figures.push_back(trapezoid);
    figures.push_back(rhombus);
    figures.push_back(pentagon);
    
    std::cout << "\nPrinting all figures" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "\nFigure " << i << ":" << std::endl;
        figures[i]->print();
        std::cout << std::endl;
        
        std::cout << "Center: (" << figures[i]->center().x() 
                  << ", " << figures[i]->center().y() << ")" << std::endl;
        
        std::cout << "Vertices: ";
        auto vertices = figures[i]->vertices();
        for (const auto& v : vertices) {
            std::cout << "(" << v->x() << ", " << v->y() << ") ";
        }
        std::cout << std::endl;
        
        std::cout << "Area: " << figures[i]->area() << std::endl;
    }
    
    // Общая площадь
    std::cout << "\nTotal area of all figures: " << figures.totalArea() << std::endl;
    
    // Удаление фигуры по индексу
    std::cout << "\nRemoving figure at index 1" << std::endl;
    figures.remove(1);
    std::cout << "Figures after removal: " << figures.size() << std::endl;
    std::cout << "New total area: " << figures.totalArea() << std::endl;
    
    // Массив конкретных фигур
    std::cout << "\nTesting Array with specific figures" << std::endl;
    Array<std::shared_ptr<Trapezoid<CoordType>>> trapezoids;
    
    auto trap1 = std::make_shared<Trapezoid<CoordType>>(
        Point<CoordType>(0, 0),
        Point<CoordType>(2, 0),
        Point<CoordType>(1.5, 1),
        Point<CoordType>(0.5, 1)
    );
    
    auto trap2 = std::make_shared<Trapezoid<CoordType>>(
        Point<CoordType>(5, 5),
        Point<CoordType>(7, 5),
        Point<CoordType>(6.5, 6),
        Point<CoordType>(5.5, 6)
    );
    
    trapezoids.push_back(trap1);
    trapezoids.push_back(trap2);
    
    std::cout << "Number of trapezoids: " << trapezoids.size() << std::endl;
    std::cout << "Total area of trapezoids: " << trapezoids.totalArea() << std::endl;
    
    // Проверка сравнения
    std::cout << "\nTesting comparison" << std::endl;
    auto trap3 = std::make_shared<Trapezoid<CoordType>>(*trap1);
    std::cout << "trap1 equals trap3: " << trap1->equals(*trap3) << std::endl;
    std::cout << "trap1 equals trap2: " << trap1->equals(*trap2) << std::endl;
    
    // Проверка копирования
    std::cout << "\nTesting cloning" << std::endl;
    auto cloned = trapezoid->clone();
    std::cout << "Original area: " << trapezoid->area() << std::endl;
    std::cout << "Cloned area: " << cloned->area() << std::endl;
    
    // Проверка move семантики
    std::cout << "\nTesting move semantics on array resize" << std::endl;
    Array<FigurePtr> smallArray(2);
    smallArray.push_back(trapezoid);
    smallArray.push_back(rhombus);
    std::cout << "Capacity before: " << smallArray.capacity() << std::endl;
    
    // Добавим третий элемент
    smallArray.push_back(pentagon);
    std::cout << "Capacity after: " << smallArray.capacity() << std::endl;
    std::cout << "Size after: " << smallArray.size() << std::endl;
    
    return 0;
}