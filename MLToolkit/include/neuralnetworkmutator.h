// this header files contains a class
// that can alter the internal state of a neural network
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_

#include "neuralnetwork.h"

namespace mltoolkit {

class NeuralNetworkMutator {
public:
	void delta_by_gradient(NeuralNetwork& target, const NeuralNetwork& nn,
		std::vector<double> last_grad, double scale = 1.0) {
		// computes the gradient of NeuralNetwork nn given the final gradient
		// updates target network, which should have the same topology as nn
		// scale is applied to the gradient before this step
		if (target.topology != nn.topology)
			throw std::invalid_argument("target incompatible with operand neural net");
		// backpropagate
	}
private:
	std::vector<std::vector<double>> activations;
	void prealloc_activations(const NeuralNetwork&);
};


} // namespace mltoolkit



#endif // !MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
