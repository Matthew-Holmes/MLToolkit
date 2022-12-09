#include "data.h"

namespace mltoolkit {
// overloaded >> so we can read into datum variables from a Data object
// just like std::cin
Data& operator>>(Data& data, Data::datumtype& datum) {
	datum = data.get_next();
	return data;
}

std::ostream& operator<<(std::ostream& os, const Data::datumtype& datum) {
	const auto& vec1 = datum.first;
	const auto& vec2 = datum.second;
	os << "( ";
	for (const auto& d : vec1)
		os << d << " ";
	os << ", ";
	for (const auto& d : vec2)
		os << d << " ";
	os << ")";
	return os;
}

}