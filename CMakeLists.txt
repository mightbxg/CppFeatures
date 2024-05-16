cmake_minimum_required(VERSION 3.10)

project(CppFeatures)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

add_executable(1_IIFE_lambda 1_IIFE_lambda.cpp)
target_link_libraries(1_IIFE_lambda PRIVATE Eigen3::Eigen)

add_executable(2_attributes 2_attributes.cpp)
target_compile_options(2_attributes PRIVATE "-Wunused")

add_executable(3_constexpr 3_constexpr.cpp)

add_executable(4_if_constexpr 4_if_constexpr.cpp)

add_executable(5_inline_variable 5_inline_variable.cpp 5_inline_variable_main.cpp)
