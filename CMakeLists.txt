cmake_minimum_required(VERSION 3.21)

project(ACM_WORKSPACE)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(LOCAL_DEBUG)
add_compile_definitions(PROJECT_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(a a/main.cpp)
add_executable(b b/main.cpp)
add_executable(c c/main.cpp)
add_executable(d d/main.cpp)
add_executable(e e/main.cpp)
add_executable(f f/main.cpp)
add_executable(g g/main.cpp)
add_executable(h h/main.cpp)
add_executable(i i/main.cpp)
add_executable(j j/main.cpp)
add_executable(k k/main.cpp)
add_executable(l l/main.cpp)
add_executable(m m/main.cpp)
add_executable(n n/main.cpp)
add_executable(o o/main.cpp)