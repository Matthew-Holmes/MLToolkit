#include "test.h"

namespace {
	// file level statics
	auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
	auto actn_func = [](double d) { return 1.0 / (1 + std::exp(-d)); };
	auto actn_grad = [](double d) { return actn_func(d) * (1 - actn_func(d)); };
	auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };
}

TEST(NeuralNetworkMutatorDeltaByGradient, OverfitsOneDatum) {
	mltoolkit::NeuralNetwork nnet(std::vector<int> {3, 5, 10, 5, 3}, actn_func, rand_getter);
	mltoolkit::NeuralNetworkMutator nnet_mut;

	nnet_mut.set_act_gradient_fn(actn_grad);
	nnet_mut.set_error_gradient_fn(errr_grad);

	std::vector<double> invec{ 0.2, 0.9, 0.2 };
	std::vector<double> outvec{ 0.0, 1.0, 0.0 };

	std::vector<double> actual = nnet.predict(invec);
	double max_difference = 0.0001;
	for (int i = 0; i != 3; i++)
		EXPECT_THAT(actual[i], ::testing::Not(::testing::DoubleNear(outvec[i], max_difference)));

	for (int i = 0; i != 1000; i++) {
		nnet_mut.delta_by_gradient(nnet, nnet, invec, outvec, -0.05);
	}
	actual = nnet.predict(invec);
	max_difference = 0.05;

	for (int i = 0; i != 3; i++)
		EXPECT_THAT(actual[i], ::testing::DoubleNear(outvec[i], max_difference));

}

TEST(NeuralNetworkMutatorDeltaByGradient, OverfitsTwoData) {
	// setu[
	mltoolkit::NeuralNetwork nnet(std::vector<int> {3, 5, 10, 5, 3}, actn_func, rand_getter);
	mltoolkit::NeuralNetworkMutator nnet_mut;

	nnet_mut.set_act_gradient_fn(actn_grad);
	nnet_mut.set_error_gradient_fn(errr_grad);

	std::vector<double> invec1{ 0.2, 0.9, 0.2 };
	std::vector<double> outvec1{ 0.0, 1.0, 0.0 };

	std::vector<double> invec2{ 0.9, 0.5, 0.05 };
	std::vector<double> outvec2{ 1.0, 0.0, 0.0 };

	// check neural network isn't already predicting
	// TODO handle and exception and reroll nnet?

	double max_difference = 0.0001;

	std::vector<double> actual1 = nnet.predict(invec1);
	for (int i = 0; i != 3; i++)
		EXPECT_THAT(actual1[i], ::testing::Not(::testing::DoubleNear(outvec1[i], max_difference)));

	std::vector<double> actual2 = nnet.predict(invec2);
	for (int i = 0; i != 3; i++)
		EXPECT_THAT(actual2[i], ::testing::Not(::testing::DoubleNear(outvec2[i], max_difference)));

	// train the network on the two data

	for (int i = 0; i != 1000; i++) {
		// use annealing alphas so we don't end up just oscilating between two locations
		nnet_mut.delta_by_gradient(nnet, nnet, invec1, outvec1, -100.0 / (i + 100));
		nnet_mut.delta_by_gradient(nnet, nnet, invec2, outvec2, -100.0 / (i + 100));
	}
	actual1 = nnet.predict(invec1);
	actual2 = nnet.predict(invec2);
	max_difference = 0.05;

	// check that now it predicts them correctly
	for (int i = 0; i != 3; i++) {
		EXPECT_THAT(actual1[i], ::testing::DoubleNear(outvec1[i], max_difference))
			<< "datum 1 entry: " << i << " not fitted for" << std::endl;
		EXPECT_THAT(actual2[i], ::testing::DoubleNear(outvec2[i], max_difference))
			<< "datum 2 entry: " << i << " not fitted for" << std::endl;
	}
}