#include "neuralnetworkmutator.h"


NeuralNetworkMutator::prealloc_activations(
	const NeuralNetwork& target) {
	for (const auto& i : target.topology)
		activations.push_back(std::vector<double>(i, 0.0));
	}
