cmake_minimum_required(VERSION 3.20)
project(trees C)

set(CMAKE_C_STANDARD 11)

add_executable(trees
        aliquot.c aliquot.h)

# link math lib - https://stackoverflow.com/questions/34625627/how-to-link-to-the-c-math-library-with-cmake
target_link_libraries(trees m)
