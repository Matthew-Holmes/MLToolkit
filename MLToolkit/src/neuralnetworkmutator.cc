#include "neuralnetworkmutator.h"

namespace mltoolkit {

void NeuralNetworkMutator::get_activations(
	const NeuralNetwork& nn, const std::vector<double>& in_vec) {

	activations.clear();
	activations.push_back(in_vec);
	activations.back().push_back(1.0); // for bias

	for (const auto& mat : nn.weights) {
		activations.push_back(
			mat.vec_mult(activations.back()));
		// apply activation function
		for (auto& d :activations.back())
			d = nn.activation_func(d); // should map to [0,1] interval
		activations.back().back() = 1.0; // preserve bias term
	}
	activations.back().pop_back(); // last output doesn't need bias
}

void NeuralNetworkMutator::delta_by_gradient(
                          NeuralNetwork& target,
                    const NeuralNetwork& nn, 
              const std::vector<double>& in_vec,
              const std::vector<double>& correct_out_vec,
                                  double scale = 1.0) {
	// computes the gradient of NeuralNetwork nn
	// given the input in_vec and desired output correct_out_vec
	// updates target network, which should have the same topology as nn
	// scale is applied to the gradient before this step
	if (target.topology != nn.topology)
		throw std::invalid_argument("target incompatible with operand neural net");
	if (in_vec.size() != nn.topology.front()
		|| correct_out_vec.size() != nn.topology.back())
		throw std::invalid_argument("input or output vectors wrong sizes");
	// compute activations
	get_activations(nn, in_vec);
	// get gradient at last layer - depedant on their contribution to the loss
	for (int i = 0; i != correct_out_vec.size(); i++)
		activations.back()[i] = act_gradient(
			error_gradient(activations.back()[i], correct_out_vec[i]) );
	// now loop over the remaining layers in reverse propagating errors
	for (int i = nn.weights.size() - 1; i >= 0; i--) {
		// multiply by transpose matrix
		activations[i] = nn.weights[i].transpose_vec_mult(activations[i + 1]);
	}
	
	// TODO consider the activation function gradient inclusion
	// TODO then loop back through computing the error at each step
		
}

} // namespace mltoolkit