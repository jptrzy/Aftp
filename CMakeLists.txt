cmake_minimum_required(VERSION 3.10)

# Define project name as a variable
set(PROJECT_NAME A2)

# Set the project name and version
project(${PROJECT_NAME} VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/node.cpp
)

# Include directories if needed
target_include_directories(${PROJECT_NAME} PRIVATE src)
