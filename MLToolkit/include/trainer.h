#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "model.h"
#include "modelmutator.h"
#include "data.h"

#include <utility>
#include <iostream>
#include <memory>

namespace mltoolkit {

template <typename MOD>
class Trainer {
public:
	Trainer(MOD mod, std::unique_ptr<Data> train, std::unique_ptr<Data> test, int max_it = 9999999)
		: model(mod), train_data_uptr(std::move(train)), test_data_uptr(std::move(test)), it_limit(max_it) {}
	Trainer(MOD mod, ModelMutator<MOD> mut,
			std::unique_ptr<Data> train, std::unique_ptr<Data> test, int max_it = 9999999)
		: model(mod), model_mut(mut), 
		  train_data_uptr(std::move(train)), test_data_uptr(std::move(test)), it_limit(max_it) {}

	void do_training();
	void evaluate();
	void set_it_limit(int max_it) { it_limit = max_it; }
private:
	MOD model; // works on a copy of the model passed
	ModelMutator<MOD> model_mut;
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
			cnt++;
			model_mut.training_mutate(model, in_out_vecs);
		}
	std::cout << "trained for " << cnt << " iterations" << std::endl;
}

template <typename MOD>
void Trainer<MOD>::evaluate() {
	std::pair<std::vector<double>, std::vector<double>> test_pair;
	std::vector<double> predicted;

	int cnt = 0; double total_error = 0.0; // for average error

	while (*test_data_uptr >> test_pair && cnt < it_limit) {
		predicted = model.predict(test_pair.first);
		for (it1 = predicted.begin(), it2 = test_pair.second.begin();
			it1 != predicted.end();
			it1++, it2++) {
			total_error += (*it1 - *it2) * (*it1 - *it2);
		}
		cnt++;
	}
	std::cout << "evaluated on " << cnt << " datapoints" << std::endl;
	std::cout << "average MSE: " << total_error / (predicted.size() * cnt) << std::endl;
}



} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
