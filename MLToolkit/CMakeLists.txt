cmake_minimum_required(VERSION 3.15)

project(MLToolkit VERSION 1.0)

add_executable(MLToolkit src/main.cc src/matrix.cc src/neuralnetwork.cc src/neuralnetworkmutator.cc "include/trainer.h" "include/data.h" "include/filedata.h")
target_include_directories(MLToolkit
	PRIVATE
	include/)