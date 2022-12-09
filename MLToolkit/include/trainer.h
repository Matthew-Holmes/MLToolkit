#ifndef MLTOOLKIT_TRAINER_H
#define MLTOOLKIT_TRAINER_H

#include "neuralnetwork.h"
#include "neuralnetworkmutator.h"

#include <utility>

namespace mltoolkit {

class Data;
class Model;
class ModelMutator;

class Trainer {
public:
	void do_training(); // TODO 
	void evaluate(); // TODO
private:
	Model mod; // TODO make base class
	ModelMutator mod_mut; // TODO make base class
	Data train_data;
	Data test_data;
};


} // namespace mltoolkit

#endif // MLTOOLKIT_TRAINER_H
