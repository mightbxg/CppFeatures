cmake_minimum_required(VERSION 3.10)

project(CppFeatures)

add_executable(IIFE_lambda IIFE_lambda.cpp)
target_compile_features(IIFE_lambda PRIVATE cxx_std_17)
