// this header files contains a class
// that can alter the internal state of a neural network
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_

#include "neuralnetwork.h"

namespace mltoolkit {

class NeuralNetworkMutator {
public:
	// TODO set public debug functions so works with main
	void delta_by_gradient(
		NeuralNetwork& target,	const NeuralNetwork& nn,
		const std::vector<double>& in_vec,
		const std::vector<double>& correct_out_vec,
		double scale);
	void get_activations(const NeuralNetwork&, const std::vector<double>&);
	void set_error_gradient_fn(std::function<double(double, double)> fxy)
		{ error_gradient = fxy; }
	void set_act_gradient_fn(std::function<double(double)> fx)
		{ act_gradient = fx; }
	std::vector<std::vector<double>> activations;
	std::function<double(double, double)> error_gradient;
	std::function<double(double)> act_gradient;
//private:
};


} // namespace mltoolkit



#endif // !MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
