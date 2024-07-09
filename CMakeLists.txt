cmake_minimum_required(VERSION 3.22.1)
project(CGame)

add_executable(raylib_game main.cpp 
src/component/transform.cpp
src/nodes/node.cpp)

target_include_directories(raylib_game PUBLIC /src/component)
target_link_libraries(raylib_game raylib -lGL -lm -lpthread -ldl -lrt -lX11)
