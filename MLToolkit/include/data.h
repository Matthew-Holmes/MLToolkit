// this header file defines the abstrac Data base class
#ifndef MLTOOLKIT_DATA_H
#define MLTOOLKIT_DATA_H

#include <utility>
#include <vector>
#include <iostream>

namespace mltoolkit {
// the abstract Data base class for data reading and saving
// << operator lets us read through the data points
// parent to FileData and MemoryData classes

class Data {
public:
	// each datum is a pair of vectors of doubles, 'invec' and 'outvec'
	typedef std::pair<std::vector<double>, std::vector<double>> datumtype;
	virtual ~Data() = default;
	// conversion to bool; false when Data finds itself past the last datum
	explicit operator bool() const { return past_last(); }
private:
	virtual datumtype   get_next() = 0; // retrieve next datum
	virtual bool past_last() const = 0; // guts of bool conversion (note const)

friend Data& operator>>(Data&, datumtype&);
};

// overloaded >> so we can read into datum variables from a Data object
// just like std::cin
Data& operator>>(Data& data, Data::datumtype& datum) {
	datum = data.get_next();
	return data;
}

std::ostream& operator<<(std::ostream& os, const Data::datumtype& datum) {
	const auto &vec1 = datum.first;
	const auto &vec2 = datum.second;
	os << "( ";
	for (const auto& d : vec1)
		os << d << " ";
	os << ", ";
	for (const auto& d : vec2)
		os << d << " ";
	os << ")";
	return os;
}





} // namespace mltoolkit


#endif