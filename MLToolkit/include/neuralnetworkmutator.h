// this header files contains a class
// that can alter the internal state of a neural network
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_

#include "neuralnetwork.h"

namespace mltoolkit {

class NeuralNetworkMutator {
public:
	void delta_by_gradient(
		NeuralNetwork&,	const NeuralNetwork&,
		const std::vector<double>&,
		const std::vector<double>&,
		std::function<double(double, double)>, 
		std::function<double(double)>,
		double);
	void get_activations(const NeuralNetwork&, const std::vector<double>&);
	std::vector<std::vector<double>> activations;
//private:
};


} // namespace mltoolkit



#endif // !MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
