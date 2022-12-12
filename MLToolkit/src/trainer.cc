#include "train.h"

namespace mltoolkit {

void Trainer::do_training() {
	// todo generalise for input/output values
	std::pair<std::vector<double>, std::vector<double>> in_out_vecs;
	while (train_data >> in_out_vecs) {
		mod_mut.training_muatate(model, in_out_vecs);
	}
}

void Trainer::evaluate() {
	std::pair<std::vector<double>, std::vector<double>> test_pair;
	std::vector<double> predicted;

	int cnt = 0; double total_error = 0.0; // for average error

	while (test_data >> test_pair) {
		predicted = model.predict(test_pair.first);
		for (it1  = predicted.begin(), it2 = test_pair.second.begin();
			 it1 != predicted.end();
			 it1++, it2++) {
			total_error += (*it1 - *it2) * (*it1 - *it2);
		}
		cnt++;
	}
	std::cout << "average MSE: " << total_error / (predicted.size() * cnt) << std::endl;
}

} // namespace mltoolkit