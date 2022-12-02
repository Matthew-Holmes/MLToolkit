#include "train.h"

namespace mltoolkit {

void Trainer::do_training() {
	// todo generalise for input/output values
	std::pair<std::vector<double>, std::vector<double>> in_out_vecs;
	while (train_data >> in_out_vecs) {
		mod_mut.train_mut(mod, in_out_vecs);
	}
}

void Trainer::evaluate() {
}

} // namespace mltoolkit