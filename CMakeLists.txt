cmake_minimum_required(VERSION 3.22.1)
project(CGame)

add_executable(raylib_game main.cpp 
src/component/transform.cpp
src/nodes/node.cpp
src/systems/debug.h)

## Maybe not needed?
#set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-linux")
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(raylib_game raylib spdlog::spdlog -lGL -lm -lpthread -ldl -lrt -lX11)
