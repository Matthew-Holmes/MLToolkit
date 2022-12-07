#include "data.h"

#include <fstream>
#include <sstream>
#include <string>


namespace mltoolkit {

class FileData : public Data {
public:
	FileData(std::ifstream fin, char d = ',') : fin(fin), delim(d) {}
	~FiledData() override { fin.close()); }
private:
	bool past_last() override { return fin; }
	datumtype get_next() override;

	std::vector<double> readvec(std::istringstream); // TODO

	char delim;
	std::ifstream fin;

};

Data::datumtype FileData::get_next() {
	std::string line;
	if (!fin.getline(line))
		return datumtype; // off end of file, return empty datum
	
	// split on primary delim
	
	datumtype ret;
	ret.first = readvec()



	
}


} // namespace mltoolkit