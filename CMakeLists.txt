cmake_minimum_required(VERSION 3.10)
project(MyGame)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Let CMake search Homebrew for SFML if needed
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml")

# Find SFML libraries
find_package(SFML 2.6
COMPONENTS 
graphics window system audio REQUIRED
)

# Add executable
add_executable(MyGame main.cpp)

# Link SFML
target_link_libraries(MyGame sfml-graphics sfml-window sfml-system sfml-audio)