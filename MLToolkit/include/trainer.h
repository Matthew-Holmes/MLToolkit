#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "model.h"
#include "modelmutator.h"
#include "data.h"

#include <utility>
#include <iostream>

namespace mltoolkit {

// TODO decide how Data works
// hold a pointer of make a new version
// pehaps use a unique ptr to transfer ownership of the data to the class
// since data follows a stream model, essentially a ifstream in a wrapper for FileData

template <typename MOD>
class Trainer {
public:
	Trainer(MOD mod, Data train, Data test)
		: model(mod), train_data(train), test_data(test) {}
	Trainer(MOD mod, ModelMutator<MOD> mut, Data train, Data test)
		: model(mod), model_mut(mut) train_data(train), test_data(test) {}

	void do_training();
	void evaluate();
private:
	MOD model; // works on a copy of the model passed
	ModelMutator<MOD> model_mut;
	Data train_data;
	Data test_data;
};


} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
