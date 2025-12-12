#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include "../include/Array.h"
#include "../include/Point.h"
#include "../include/Trapezoid.h"

void test_array_basic() {
    std::cout << "Test 1: Array basic operations" << std::endl;
    
    Array<int> arr;
    
    // Проверяем начальное состояние
    assert(arr.size() == 0);
    assert(arr.empty());
    
    // Добавляем элементы
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    assert(arr.size() == 3);
    assert(!arr.empty());
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    
    // Проверяем доступ с bounds checking
    try {
        int x = arr[10];
        assert(false);  // Не должно дойти сюда
    } catch (const std::out_of_range&) {
        // Ожидаемое исключение
    }
    
    std::cout << "  ✓ Array basic operations passed" << std::endl;
}

void test_array_resize() {
    std::cout << "Test 2: Array resize and move semantics" << std::endl;
    
    // Создаем массив с начальной емкостью 2
    Array<std::string> arr(2);
    
    assert(arr.capacity() == 2);
    
    // Добавляем элементы
    arr.push_back("first");
    arr.push_back("second");
    
    assert(arr.size() == 2);
    assert(arr.capacity() == 2);
    
    // Добавляем третий элемент - должен произойти ресайз
    arr.push_back("third");
    
    assert(arr.size() == 3);
    assert(arr.capacity() > 2);  // Емкость увеличилась
    
    // Проверяем, что элементы сохранились
    assert(arr[0] == "first");
    assert(arr[1] == "second");
    assert(arr[2] == "third");
    
    std::cout << "  ✓ Array resize tests passed" << std::endl;
}

void test_array_removal() {
    std::cout << "Test 3: Array element removal" << std::endl;
    
    Array<int> arr;
    
    for (int i = 0; i < 5; ++i) {
        arr.push_back(i * 10);
    }
    
    assert(arr.size() == 5);
    
    // Удаляем элемент в середине
    arr.remove(2);
    
    assert(arr.size() == 4);
    assert(arr[0] == 0);
    assert(arr[1] == 10);
    assert(arr[2] == 30);  // 20 был удален
    assert(arr[3] == 40);
    
    // Удаляем первый элемент
    arr.remove(0);
    assert(arr.size() == 3);
    assert(arr[0] == 10);
    
    // Удаляем последний элемент
    arr.remove(arr.size() - 1);
    assert(arr.size() == 2);
    
    std::cout << "  ✓ Array removal tests passed" << std::endl;
}

void test_array_copy_move() {
    std::cout << "Test 4: Array copy and move semantics" << std::endl;
    
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    
    // Тест копирования
    Array<int> arr2 = arr1;
    assert(arr2.size() == 3);
    assert(arr2[0] == 1);
    assert(arr2[1] == 2);
    assert(arr2[2] == 3);
    
    // Изменяем копию, оригинал не должен измениться
    arr2[0] = 100;
    assert(arr1[0] == 1);
    assert(arr2[0] == 100);
    
    // Тест перемещения
    Array<int> arr3 = std::move(arr2);
    assert(arr3.size() == 3);
    assert(arr3[0] == 100);
    assert(arr2.empty());  // arr2 должен быть пустым после перемещения
    
    std::cout << "  ✓ Array copy/move tests passed" << std::endl;
}

void test_array_with_figures() {
    std::cout << "Test 5: Array with figures" << std::endl;
    
    using FigurePtr = std::shared_ptr<Figure<double>>;
    Array<FigurePtr> figures;
    
    // Добавляем фигуры
    auto trap = std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    
    auto trap2 = std::make_shared<Trapezoid<double>>(
        Point<double>(5, 5),
        Point<double>(9, 5),
        Point<double>(8, 8),
        Point<double>(6, 8)
    );
    
    figures.push_back(trap);
    figures.push_back(trap2);
    
    assert(figures.size() == 2);
    
    // Проверяем общую площадь
    double total_area = figures.totalArea();
    assert(total_area > 0);
    assert(std::abs(total_area - (trap->area() + trap2->area())) < 1e-9);
    
    // Удаляем фигуру
    figures.remove(0);
    assert(figures.size() == 1);
    assert(std::abs(figures.totalArea() - trap2->area()) < 1e-9);
    
    std::cout << "  ✓ Array with figures tests passed" << std::endl;
}

int main() {
    std::cout << "=== Running Array Tests ===" << std::endl;
    
    test_array_basic();
    test_array_resize();
    test_array_removal();
    test_array_copy_move();
    test_array_with_figures();
    
    std::cout << "\n=== All Array tests passed! ===" << std::endl;
    return 0;
}