cmake_minimum_required(VERSION 3.16)
project(GeometricFiguresTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Создаем тестовые исполняемые файлы
add_executable(test_point test_point.cpp)
add_executable(test_figures test_figures.cpp)
add_executable(test_array test_array.cpp)
add_executable(test_integration test_integration.cpp)

# Настраиваем пути для include файлов
target_include_directories(test_point PRIVATE ../include)
target_include_directories(test_figures PRIVATE ../include)
target_include_directories(test_array PRIVATE ../include)
target_include_directories(test_integration PRIVATE ../include)

# Опции компиляции
if(MSVC)
    target_compile_options(test_point PRIVATE /W4)
    target_compile_options(test_figures PRIVATE /W4)
    target_compile_options(test_array PRIVATE /W4)
    target_compile_options(test_integration PRIVATE /W4)
else()
    target_compile_options(test_point PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_figures PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_array PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_integration PRIVATE -Wall -Wextra -pedantic)
endif()

# Линковка математической библиотеки
if(UNIX)
    target_link_libraries(test_point m)
    target_link_libraries(test_figures m)
    target_link_libraries(test_array m)
    target_link_libraries(test_integration m)
endif()

# Добавляем тесты в CTest (опционально)
enable_testing()
add_test(NAME test_point COMMAND test_point)
add_test(NAME test_figures COMMAND test_figures)
add_test(NAME test_array COMMAND test_array)
add_test(NAME test_integration COMMAND test_integration)