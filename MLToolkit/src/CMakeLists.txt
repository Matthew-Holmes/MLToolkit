#cmake_minimum_required(VERSION 3.15)

#project(MLToolkit VERSION 1.0)

add_executable(MLToolkit main.cc matrix.cc neuralnetwork.cc neuralnetworkmutator.cc data.cc filedata.cc)
#     name of executable    |     |            |       sources        |                |         |			

# thi is now handles by top level CMakeLists.txt file
#target_include_directories(MLToolkit
	#PRIVATE
	#include/)

add_library(MLToolkit_lib STATIC main.cc matrix.cc neuralnetwork.cc neuralnetworkmutator.cc data.cc filedata.cc)
#			name of library			built from these source files			
# STATIC libraries are archives of object files for use when linking other targets