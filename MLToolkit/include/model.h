#ifndef MLTOOLKIT_MODEL_H
#define MLTOOLKIT_MODEL_H

#include <vector>

namespace mltoolkit {

class Model {
public:
	virtual ~Model() = default;
	virtual std::vector<double> predict(const std::vector<double>&) = 0;
};



} // namespace mltoolkit


#endif