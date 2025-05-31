cmake_minimum_required(VERSION 3.14)
project(a3 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  matplotplusplus
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
  GIT_TAG master
)
FetchContent_MakeAvailable(matplotplusplus)

find_package(pybind11 REQUIRED)

pybind11_add_module(a3 a3.cpp)
target_link_libraries(a3 PUBLIC matplot)
