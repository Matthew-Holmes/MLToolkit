cmake_minimum_required(VERSION 3.15)

project(MLToolkit VERSION 1.0)

add_executable(MLToolkit src/main.cc)
target_include_directories(MLToolkit
	PRIVATE
	include/)