

add_executable(MLToolkit_test main.cc test_test.cc matrix_test.cc neuralnetwork_test.cc trainer_test.cc )

add_test(NAME MLToolkit_test COMMAND MLToolkit_test)
#         | name of added test         | executable target to run at command line

target_link_libraries(MLToolkit_test PUBLIC MLToolkit_lib gtest)
