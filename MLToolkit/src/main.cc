#include "mltoolkit.h"

#include <cmath>

int main() {
	auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
	auto actn_func = [] (double d) { return 1.0 / (1 + std::exp(-d)); };
	auto actn_grad = [actn_func] (double d) { return actn_func(d) * (1 - actn_func(d)); };
	auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };
	// mltoolkit::Matrix mat(3, 3, rand_getter);
	mltoolkit::Matrix mat(3, 3, 1.0);
	std::cout << "matrix with size: ";
	std::cout << mat.size().first << " " << mat.size().second << std::endl;
	std::cout << "so " << mat.number_of_rows() << " rows, and " 
		<< mat.number_of_cols() << " cols" << std::endl;
	std::cout << "data is: " << std::endl;	
	mat.element_ij(1, 1) = 0.0;
	for (int i = 0; i < mat.number_of_rows(); i++) {
		for (int j = 0; j < mat.number_of_cols(); j++) {
			std::cout << mat.element_ij(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "testing matrix vector multiplication" << std::endl;
	std::vector<double> vec{ 1.0, 2.0, 3.0 };
	vec = mat.vec_mult(vec);
	for (auto d : vec) {
		std::cout << d << " ";
	}
	std::cout << std::endl;
	vec = mat.transpose_vec_mult(vec);
	for (auto d : vec) {
		std::cout << d << " ";
	}
	std::cout << std::endl;

	std::cout << "testing neural networks" << std::endl;
	mltoolkit::NeuralNetwork nnet(std::vector<int> {3, 5, 10, 5, 3}, actn_func, rand_getter);
	auto out = nnet.feed_forward(vec);
	for (auto d :out) {
		std::cout << d << " ";
	}
	std::cout << std::endl;


	std::cout << "testing nnet mutators" << std::endl;
	mltoolkit::NeuralNetworkMutator nnet_mut;
	nnet_mut.get_activations(nnet, vec);
	for (const auto &v : nnet_mut.activations) {
		for (const auto& d : v)
			std::cout << d << " ";
		std::cout << std::endl;
	}
	std::cout << "tested activations getter" << std::endl;
	std::cout << "testing gradient descent" << std::endl;
	nnet_mut.set_act_gradient_fn(actn_grad);
	nnet_mut.set_error_gradient_fn(errr_grad);
	std::vector<double> invec{ 0.2, 0.9, 0.2 };
	std::vector<double> outvec{ 0.0, 1.0, 0.0 };
	for (const auto& d : nnet.feed_forward(invec))
		std::cout << d << " ";
	std::cout << std::endl;
	for (int i = 0; i != 1000; i++) {
		nnet_mut.delta_by_gradient(nnet, nnet, invec, outvec, -0.05);
		if (i % 100 == 0) {
			for (const auto& d : nnet.feed_forward(invec))
				std::cout << d << " ";
			std::cout << std::endl;
		}
	}
	std::cout << "tested gradient descent" << std::endl;
	nnet;
	int k;
	std::cin >> k;
	return 0;
}
