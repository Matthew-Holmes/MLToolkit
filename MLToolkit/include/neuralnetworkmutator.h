// this header files contains a class
// that can alter the internal state of a neural network
#ifndef MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
#define MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_

#include "neuralnetwork.h"
#include "modelmutator.h"

namespace mltoolkit {

class NeuralNetworkMutator : public ModelMutator<NeuralNetwork> {
public:
	typedef std::function<double(double, double)> xyfunc;
	typedef std::function<double(double)>         xfunc;

	NeuralNetworkMutator(xyfunc fxy = meansquared_grad, xfunc fx = logistic_grad, double d = 0.5)
		: error_gradient(fxy), act_gradient(fx), learning_rate(d) {}

	void delta_by_gradient(
		NeuralNetwork& target, const NeuralNetwork& nn,
		const std::vector<double>& in_vec,
		const std::vector<double>& correct_out_vec,
		double scale);

	void training_mutate(
		NeuralNetwork& nnet, const Data::datumtype& in_out_vec_pair) override;

	void compute_activations(const NeuralNetwork&, const std::vector<double>&);
	std::vector<std::vector<double>> get_activations() { return activations; }

	void set_error_gradient_fn(xyfunc fxy)
		{ error_gradient = fxy; }
	void set_act_gradient_fn(xfunc fx)
		{ act_gradient = fx; }
	void set_learning_rate(double d) { learning_rate = d; }
private:
	xyfunc error_gradient;
	xfunc act_gradient;
	double learning_rate;

	static xyfunc meansquared_grad;
	static xfunc logistic_func;
	static xfunc logistic_grad;

	std::vector<std::vector<double>> activations;
};

} // namespace mltoolkit



#endif // !MLTOOLKIT_INCLUDE_NEURALNETWORKMUTATOR_H_
