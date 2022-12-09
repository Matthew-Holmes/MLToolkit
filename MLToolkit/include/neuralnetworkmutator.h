// this header files contains a class
// that can alter the internal state of a neural network
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_

#include "neuralnetwork.h"
#include "modelmutator.h"

namespace mltoolkit {

class NeuralNetworkMutator : public ModelMutator<NeuralNetwork> {
public:
	// TODO constructor

	void training_mutate(
		NeuralNetwork& nnet, const Data::datumtype& in_out_vec_pair) override;
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
	void set_learning_rate(double d) { learning_rate = d; }
	std::vector<std::vector<double>> activations;
private:
	std::function<double(double, double)> error_gradient;
	std::function<double(double)> act_gradient;
	double learning_rate = 0.1;
};


} // namespace mltoolkit



#endif // !MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
