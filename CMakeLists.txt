cmake_minimum_required(VERSION 3.10)
project(MyGame)

# set(CMAKE_CXX_STANDARD 17)
add_executable(MyGame main.cpp)

# Find SFML
find_package(SFML 3.0.1 COMPONENTS graphics window system audio REQUIRED)


# Link SFML
target_link_libraries(MyGame sfml-graphics sfml-window sfml-system sfml-audio)