cmake_minimum_required(VERSION 3.16)
project(GeometricFigures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(geometric_figures 
    src/main.cpp
)

target_include_directories(geometric_figures PRIVATE include)

if(MSVC)
    target_compile_options(geometric_figures PRIVATE /W4 /WX)
else()
    target_compile_options(geometric_figures PRIVATE -Wall -Wextra -pedantic)
endif()

if(UNIX)
    target_link_libraries(geometric_figures m)
endif()

add_subdirectory(tests)