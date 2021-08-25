cmake_minimum_required(VERSION 3.20)
project(trees C)

set(CMAKE_C_STANDARD 11)

# output executables into <root>/bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(trees
        src/aliquot.c src/aliquot.h)

# link math lib - https://stackoverflow.com/questions/34625627/how-to-link-to-the-c-math-library-with-cmake
target_link_libraries(trees m)
