#include "filedata.h"


namespace mltoolkit {

Data::datumtype FileData::get_next() {
	std::string line;
	if (!std::getline(fin, line))
	{
		return datumtype(std::vector<double>(), std::vector<double>());
	}
	// off end of file, return empty datum
	std::istringstream linestream(line);

	// split on primary delim, overwriting 'line'
	// then pass to be read into a vector
	// expects a space delimated input for the readvec call
	datumtype ret;
	getline(linestream, line, delim);
	ret.first = readvec(std::istringstream(line));
	getline(linestream, line, delim);
	ret.second = readvec(std::istringstream(line));
	return ret;
}

std::vector<double> FileData::readvec(std::istringstream& is) {
	std::vector<double> dvec;
	double d;
	while (is >> d)
		dvec.push_back(d);
	return dvec;
}


} // namespace mltoolkit