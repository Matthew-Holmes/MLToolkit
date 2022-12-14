#include "test.h"

TEST(NeuralNetwork, ZeroWeights) {
	// create topology
	std::vector<int> topology = { 2, 3, 1 };

	// create activation function
	std::function<double(double)> act_func = [](double x) { return x; };

	// create weight initialization function
	std::function<double(void)> init_func = [] { return 0.0; };

	// create neural network with all zero weights
	mltoolkit::NeuralNetwork nn(topology, act_func, init_func);

	// create input vector
	std::vector<double> in_vec = { 1.0, 2.0 };

	// compute output
	std::vector<double> output = nn.predict(in_vec);

	// check that output is all zeros
	for (double val : output) {
		EXPECT_DOUBLE_EQ(val, 0.0);
	}
}

TEST(NeuralNetwork, IdentityWeights) {
	// Create a neural network with a single layer and identity matrix weights
	std::vector<int> topology = { 2, 2 };
	std::function<double(double)> activation_func = [](double x) { return x; };
	std::function<double(int, int)> init_func = [] (int i, int j) -> double { return i == j ? 1.0 : 0.0; };
	mltoolkit::NeuralNetwork nn(topology, activation_func, init_func);

	// Test the neural network with different input vectors
	std::vector<double> input = { 1.0, 2.0 };
	std::vector<double> expected_output = { 1.0, 2.0 };
	std::vector<double> actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { 0.0, 0.0 };
	expected_output = { 0.0, 0.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { -1.0, 1.0 };
	expected_output = { -1.0, 1.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);
}

TEST(NeuralNetwork, ScalarActivation) {
	// Create a neural network with a single layer and identity matrix weights
	std::vector<int> topology = { 3, 3, 3 };
	std::function<double(double)> activation_func = [](double x) { return 2 * x; };
	// identity weights
	std::function<double(int, int)> init_func = [](int i, int j) -> double { return i == j ? 1.0 : 0.0; };
	mltoolkit::NeuralNetwork nn(topology, activation_func, init_func);

	// Test the neural network with different input vectors
	std::vector<double> input = { 1.0, 2.0, 3.0 };
	std::vector<double> expected_output = { 4.0, 8.0, 12.0 };
	std::vector<double> actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { 0.0, 0.0, 0.0 };
	expected_output = { 0.0, 0.0, 0.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { -1.0, 1.0, 0.0 };
	expected_output = { -4.0, 4.0, 0.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);
}

TEST(NeuralNetwork, SigmoidActivation) {
	// Create a neural network with a single layer and identity matrix weights
	std::vector<int> topology = { 3, 3 };
	std::function<double(double)> activation_func = [](double x) { return 1.0 / (1 + std::exp(-x)); };
	// identity weights
	std::function<double(int, int)> init_func = [](int i, int j) -> double { return i == j ? 1.0 : 0.0; };
	mltoolkit::NeuralNetwork nn(topology, activation_func, init_func);

	// Test the neural network with different input vectors
	std::vector<double> input = { 1.0, 2.0, 3.0 };
	std::vector<double> expected_output = { 1.0 / (1.0 + std::exp(-1.0)),
										    1.0 / (1.0 + std::exp(-2.0)),
											1.0 / (1.0 + std::exp(-3.0)) };
	std::vector<double> actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { 0.0, 0.0, 0.0 };
	expected_output = { 0.5, 0.5, 0.5 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { -1.0, 1.0, 0.0 };
	expected_output = { 1.0 / (1.0 + std::exp(1.0)), 1.0 / (1.0 + std::exp(-1.0)), 0.5};
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);
}

TEST(NeuralNetwork, BiasIncorporated) {
	// Create a neural network with a single layer and identity matrix weights
	std::vector<int> topology = { 2, 2 };
	std::function<double(double)> activation_func = [] (double x) { return x; };
	// last column all ones to pick up the bias term
	std::function<double(int, int)> init_func = [] (int i, int j) -> double { return j == 2 ? i + 1 : 0.0; };
	mltoolkit::NeuralNetwork nn(topology, activation_func, init_func);

	// Test the neural network with different input vectors
	std::vector<double> input = { 1.0, 2.0 };
	std::vector<double> expected_output = { 1.0, 2.0 };
	std::vector<double> actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { 0.0, 0.0 };
	expected_output = { 1.0, 2.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);

	input = { -1.0, 1.0 };
	expected_output = { 1.0, 2.0 };
	actual_output = nn.predict(input);
	EXPECT_EQ(expected_output, actual_output);
}


