#include "mltoolkit.h"

#include <cmath>

int main() {
	auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
	auto actn_func = [](double d) { return 1.0 / (1 + std::exp(-d)); };
	auto actn_grad = [actn_func](double d) { return actn_func(d) * (1 - actn_func(d)); };
	auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };
	// mltoolkit::Matrix mat(3, 3, rand_getter);


	std::vector<double> vec{ 1.0, 2.0, 3.0 };


	std::cout << "testing neural networks" << std::endl;
	mltoolkit::NeuralNetwork nnet(std::vector<int> {3, 5, 10, 5, 3}, actn_func, rand_getter);
	auto out = nnet.predict(vec);
	for (auto d : out) {
		std::cout << d << " ";
	}
	std::cout << std::endl;


	std::cout << "testing nnet mutators" << std::endl;
	mltoolkit::NeuralNetworkMutator nnet_mut;
	nnet_mut.compute_activations(nnet, vec);
	for (const auto& v : nnet_mut.get_activations()) {
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
	for (const auto& d : nnet.predict(invec))
		std::cout << d << " ";
	std::cout << std::endl;
	for (int i = 0; i != 1000; i++) {
		nnet_mut.delta_by_gradient(nnet, nnet, invec, outvec, -0.05);
		if (i % 100 == 0) {
			for (const auto& d : nnet.predict(invec))
				std::cout << d << " ";
			std::cout << std::endl;
		}
	}
	std::cout << "tested gradient descent" << std::endl;


	std::cout << "testing input from datafile" << std::endl;
	mltoolkit::FileData filedat("C:/Users/Matthew/Documents/Work/Coding/CPProjects/MLTookit/MLToolkit/data/testdata.txt");
	mltoolkit::Data::datumtype datum;
	using mltoolkit::operator<<; // so less clunky output
	while (filedat >> datum) {
		std::cout << "next datum:" << std::endl;
		std::cout << datum << std::endl;
	}

	std::cout << "testing input from mnist datafile" << std::endl;
	mltoolkit::FileData mnist_train("C:/Users/Matthew/Documents/Work/Coding/CPProjects/MLTookit/MLToolkit/data/datasets/mnist_train_formatted.txt");
	mnist_train >> datum;
	std::cout << datum << std::endl;

	std::cout << "tested input from datafile" << std::endl;

	std::cout << "testing Trainer class" << std::endl;
	mltoolkit::NeuralNetwork mnist_nnet(std::vector<int> {784, 100, 50, 10}, actn_func, rand_getter);
	std::string train_str = "C:/Users/Matthew/Documents/Work/Coding/CPProjects/MLTookit/MLToolkit/data/datasets/mnist_train_formatted.txt";
	std::string test_str = "C:/Users/Matthew/Documents/Work/Coding/CPProjects/MLTookit/MLToolkit/data/datasets/mnist_test_formatted.txt";
	// we'll use default mutator
	mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(mnist_nnet,
		std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData(train_str)),
		std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData(test_str)));
	trainer.set_it_limit(100);

	std::cout << "running Trainer class with over 100 iteration max" << std::endl;
#
	// define the class?
	trainer.do_training();
	trainer.evaluate();
	trainer.evaluate();
	trainer.evaluate();

	std::cout << "running Trainer class with over 1000 iteration max train, 100 test" << std::endl;

	trainer.set_it_limit(1000);
	trainer.do_training();
	trainer.set_it_limit(100);
	trainer.evaluate();
	trainer.evaluate();
	trainer.evaluate();


	std::cout << "tested Trainer class" << std::endl;


	int k;
	std::cin >> k;
	return 0;
}
