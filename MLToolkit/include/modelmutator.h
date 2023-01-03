#ifndef MLTOOLKIT_MODELMUTATOR_H
#define MLTOOLKIT_MODELMUTATOR_H

#include "data.h"
#include "model.h"

namespace mltoolkit {

template <typename MOD>
class ModelMutator {
	friend MOD;
public:
	virtual ~ModelMutator() = default;
	virtual void training_mutate(
		MOD& M, const Data::datumtype& in_out_vec_pair, int cnt, int max_cnt) {
		std::cout << "base" << std::endl; return;
	}
};


}

#endif