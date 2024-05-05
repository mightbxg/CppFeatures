cmake_minimum_required(VERSION 3.10)

project(CppFeatures)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

add_executable(IIFE_lambda IIFE_lambda.cpp)
target_link_libraries(IIFE_lambda PRIVATE Eigen3::Eigen)

add_executable(attribute_nodiscard attribute_nodiscard.cpp)
add_executable(attribute_deprecated attribute_deprecated.cpp)
add_executable(attribute_maybe_unused attribute_maybe_unused.cpp)
target_compile_options(attribute_maybe_unused PRIVATE "-Wunused")
