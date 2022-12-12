#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "model.h"
#include "modelmutator.h"
#include "data.h"

#include <utility>

namespace mltoolkit {

template <typename MOD>
class Trainer {
public:
	Trainer(MOD mod, ModelMutator<MOD> mod_mut, Data train, Data test)
		: model(mod), model_mut(mod_mut), train_data(train), test_data(test) {}
	void do_training(); // TODO 
	void evaluate(); // TODO
private:
	MOD model;
	ModelMutator<MOD> model_mut;
	Data train_data;
	Data test_data;
};


} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
