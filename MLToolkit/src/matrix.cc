#include "matrix.h"

namespace mltoolkit {

double dot(const std::vector<double>& lhs,
		    const std::vector<double>& rhs) {
	if (lhs.size() != rhs.size()) {
		throw std::invalid_argument("vector sizes differ for dot product");
	}
	double d = 0.0;
	for (int i = 0; i != lhs.size(); i++) {
		d += lhs[i] * rhs[i];
	}
	return d;	
}
std::vector<double> Matrix::vec_mult(const std::vector<double>& vec) const{
	if (vec.size() != size_pair.second) {
		throw std::invalid_argument("matrix incompatible with vector");
	}
	std::vector<double> out;
	for (const auto &row : data) {
		out.push_back(dot(row, vec));
	}
	return out;
}

std::vector<double> Matrix::vec_mult(const std::vector<double>& vec) const {
	if (vec.size() != size_pair.first) {
		throw std::invalid_argument("matrix incompatible with vector");
	}
	std::vector<double> out(size_pair.second, 0.0);
	
	auto it = vec.begin();
	for (const auto& row : data) {
		for (/*  */; i != size_pair.second; i++) {
			out[i] += row[i] * (*it);
		}
		it++;
	}
	return out;
}

void Matrix::append_row(std::vector<double> row)
{
	if (row.size() != size_pair.second) {
		throw std::invalid_argument("appending incompatible row");
	}
	data.push_back(row);
	size_pair.first++;
}




} // namespace mltoolkit