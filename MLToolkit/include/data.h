// this header file defines the abstrac Data base class
#ifndef MLTOOLKIT_DATA_H
#define MLTOOLKIT_DATA_H

#include <pair>
#include <vector>

namespace mltoolkit {
// the abstract Data base class handles data reading and saving
// << operator lets us read through the data points
// parent to FileData and MemoryData classes

class Data {
	typedef std::pair<std::vector<double>, std::vector<double>> datumtype;
	friend Data& mltoolkit::operator>>(Data&, datumtype);
public:
	virtual ~Data() = default;
	explicit operator bool() const { return past_last() }
private:
	virtual datumtype get_next() = 0;
	virtual bool      past_last() = 0;

};

Data& operator>>(Data& data, Data::datumtype& datum) {
	datum = data.get_next();
	return data;
}

} // namespace mltoolkit


#endif