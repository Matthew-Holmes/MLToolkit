#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "model.h"
#include "modelmutator.h"
#include "neuralnetworkmutator.h"
#include "data.h"

#include <utility>
#include <iostream>
#include <memory>

namespace mltoolkit {

// WARNING - ModelMutator<MOD> may be getting sliced down

template <typename MOD>
class Trainer {
public:
	Trainer(MOD& mod, std::unique_ptr<Data> train, std::unique_ptr<Data> test, int max_it = 9999999)
		: model_ref(std::ref(mod)),
		  model_mut_uptr(std::make_unique<ModelMutator<MOD>>()),
		  train_data_uptr(std::move(train)),
		  test_data_uptr(std::move(test)),
		  it_limit(max_it) {}
	// constructor that takes a ModelMutator
	Trainer(MOD& mod, std::unique_ptr<ModelMutator<MOD>> mut_uptr, std::unique_ptr<Data> train,
		    std::unique_ptr<Data> test, int max_it = 9999999)
		: model_ref(std::ref(mod)),
		  model_mut_uptr(std::move(mut_uptr)),
		  train_data_uptr(std::move(train)),
		  test_data_uptr(std::move(test)),
		  it_limit(max_it) {}

	void do_training();
	void evaluate();
	void set_it_limit(int max_it) { it_limit = max_it; }
private:
	MOD& model_ref; // works on a copy of the model passed
	std::unique_ptr<ModelMutator<MOD>> model_mut_uptr;
	std::unique_ptr<Data> train_data_uptr;
	std::unique_ptr<Data> test_data_uptr;
	int it_limit;
};


template <typename MOD>
void Trainer<MOD>::do_training() {
	// todo generalise for input/output values
	std::pair<std::vector<double>, std::vector<double>> in_out_vecs;
	int cnt = 0;
		while (*train_data_uptr >> in_out_vecs && cnt < it_limit) {
			/*
			for (int i = 0; i != in_out_vecs.first.size(); i++)
				std::cout << in_out_vecs.first[i] << " ";
			std::cout << "| ";
			for (int i = 0; i != in_out_vecs.second.size(); i++)
				std::cout << in_out_vecs.second[i] << " ";
			std::cout << std::endl;
			*/
			cnt++;
			model_mut_uptr->training_mutate(model_ref, in_out_vecs);
		}
	std::cout << "trained for " << cnt << " iterations" << std::endl;
}

template <typename MOD>
void Trainer<MOD>::evaluate() {
	std::pair<std::vector<double>, std::vector<double>> test_pair;
	std::vector<double> predicted;

	int cnt = 0; double total_error = 0.0; // for average error

	while (*test_data_uptr >> test_pair && cnt < it_limit) {
		predicted = model_ref.predict(test_pair.first);
		auto it1 = predicted.begin();
		auto it2 = test_pair.second.begin();
		while (	it1 != predicted.end()) {
			total_error += (*it1 - *it2) * (*it1 - *it2);
			it1++; it2++;
		}
		cnt++;
	}
	std::cout << "evaluated on " << cnt << " datapoints" << std::endl;
	std::cout << "average MSE: " << total_error / (predicted.size() * cnt) << std::endl;
}



} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
