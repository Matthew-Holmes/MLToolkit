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
	Trainer(MOD mod, std::unique_ptr<Data> train, std::unique_ptr<Data> test)
		: model(mod), train_data(std::move(train)), test_data(std::move(test)) {}
	Trainer(MOD mod, ModelMutator<Mod> mut,
			std::unique_ptr<Data> train, std::unique_ptr<Data> test)
		: model(mod), model_mut(mut), 
		  train_data(std::move(train)), test_data(std::move(test)) {}

	void do_training();
	void evaluate();
private:
	MOD model; // works on a copy of the model passed
	ModelMutator<MOD> model_mut;
	std::unique_ptr<Data> train_data_uptr;
	std::unique_ptr<Data> test_data_uptr;
};


} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
