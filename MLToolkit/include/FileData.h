#ifndef MLTOOLKIT_FILEDATA_H
#define MLTOOLKIT_FILEDATA_H

#include "data.h"

#include <fstream>
#include <sstream>
#include <string>


namespace mltoolkit {

class FileData : public Data {
public:
	FileData(std::string fname, char d = ',') : fin(fname), delim(d) { 
		if (!fin.is_open())
			std::cout << "failed to open file" << std::endl;
	}
	~FileData() { fin.close(); } // don't override here; will call ~Data() next
private:
	bool past_last() const override { return fin ? true : false; }
	datumtype get_next() override;

	std::vector<double> readvec(std::istringstream&);

	char delim;
	std::ifstream fin;
};


} // namespace mltoolkit

#endif