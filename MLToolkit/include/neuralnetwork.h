// this header file defines the NeuralNetwork class
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORK_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORK_H_

#include <vector>
#include <functional>

#include "matrix.h"

namespace mltoolkit {

// the NeuralNetwork class stores network weights and performs feed forward
// we can think of the "layers" being connected by webs of weights
// ultimately computing an output is just matrix multiplications
// mixed with normalisations - but we have an extra bias term that makes
// sure every layer gets to do something, even if a zero vector input occurs
class NeuralNetwork {
public:
	NeuralNetwork() = default;
	NeuralNetwork(std::vector<int> top, std::function<double(double)> act,
		std::function<double(void)> init);


	std::vector<double> feed_forward(const std::vector<double>& in_vec);
private:
	std::vector<Matrix> weights;
	std::vector<int> topology;
	std::function<double(double)> activation_func;
};

} // namespace mltoolkit

#endif