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
                                  double scale = -1.0) {
	// computes the gradient of NeuralNetwork nn
	// given the input in_vec and desired output correct_out_vec
	// updates target network, which should have the same topology as nn
	// scale is applied to the gradient before this step

	// compatibility between nn and target checking
	if (target.topology != nn.topology)
		throw std::invalid_argument(
			"target incompatible with operand neural net");
	if (in_vec.size() != nn.topology.front() || 
		correct_out_vec.size() != nn.topology.back())
		throw std::invalid_argument(
			"input or output vectors wrong sizes");

	get_activations(nn, in_vec); // get nodewise activations
	// last layer error contribution
	// includes error gradient
	for (int i = 0; i != correct_out_vec.size(); i++) {
		activations.back()[i] = error_gradient(activations.back()[i], correct_out_vec[i]);
		activations.back()[i] *= act_gradient(activations.back()[i]);
	}
	activations.back().push_back(1.0); // bias term 

	// now loop over the remaining layers in reverse
	// computing weight gradients
	// then propagating errors
	for (int i = nn.weights.size() - 1; i >= 0; i--) {
		// update the target weights
		// don't update last row since that is only for bias
		for (int j = 0; j != nn.weights[i].number_of_rows() - 1; j++) {
			for (int k = 0; k != nn.weights[i].number_of_cols(); k++) {
				// vector outer product gives the gradient for each entry
				target.weights[i].element_ij(j, k)
					+= scale * (activations[i + 1][j] * activations[i][k]);
				//  += for gradient descent use negative scale value
			} 
		}
		// now overwrite activations with error backpropagated
		activations[i] = nn.weights[i].transpose_vec_mult(activations[i + 1]);
		for (auto& d : activations[i])
			d *= act_gradient(d);
	} // end for loop over weight matrices
} // NeuralNetworkMutator::delta_by_gradient

} // namespace mltoolkit