#include "neuralnetwork.h"

namespace mltoolkit {

std::vector<double> NeuralNetwork::feed_forward(const std::vector<double>& in_vec)
{
	return std::vector<double>();
}

NeuralNetwork::NeuralNetwork(std::vector<int> top, 
	std::function<double(double)> act_func,
	std::function<double(void)> init_func)
	: topology(top), activation_func(act_func) {

	bool first = true;
	int last;
	for (const auto& i : topology) {
		// loop through the layers and create the weight matrices
		// to transform to the next layer
		if (first) { first = false; last = i; continue; } // input layer is first in topology
		// usual weights, with bias term the last in the input
		weights.push_back(Matrix(i, last + 1, init_func));
		// final row to preserve bias term
		weights.back().append_row(std::vector<double>(last + 1, 0.0));
		weights.back().element_ij(i, last) = 1.0;
		last = i;
	}

};

} // namespace mltoolkit


