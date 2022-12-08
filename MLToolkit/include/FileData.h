#ifndef MLTOOLKIT_FILEDATA_H
#define MLTOOLKIT_FILEDATA_H

#include "data.h"

#include <fstream>
#include <sstream>
#include <string>


namespace mltoolkit {

class FileData : public Data {
public:
	FileData(std::string fname, char d = ',') : fin(fname), delim(d) {}
	~FileData() { fin.close(); } // don't override here; will call ~Data() next
private:
	bool past_last() const override { return fin ? true : false; }
	datumtype get_next() override;

	std::vector<double> readvec(std::istringstream&);
	char delim;
	std::ifstream fin;

};

Data::datumtype FileData::get_next() {
	std::string line;
	if (!getline(fin, line))
		return datumtype(std::vector<double>(), std::vector<double>());
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

#endif