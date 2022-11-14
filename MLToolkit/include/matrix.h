// this header file defines the matrix class
#ifndef MLTOOLKIT_INCLUDE_MATRIX_H_
#define MLTOOLKIT_INCLUDE_MATRIX_H_

#include <vector>
#include <utility>
#include <stdexcept>
#include <functional>

namespace mltoolkit {

// standard n x m matrix of doubles implementation
// Matrix.data[i][j] should return the element in row i and column j
class Matrix {
public:
	Matrix() = default;
	Matrix(int rows, int cols, double fill = 0.0)
		: size_pair{ rows, cols } {
		for (int i = 0; i != rows; i++)
			data.push_back(std::vector<double>(cols, fill));
	}

	Matrix(int rows, int cols, std::function<double(void)> init_func)
		: size_pair{ rows, cols } {
		// constructor that takes an function to randomly generate inputs
		for (int i = 0; i != rows; i++) {
			std::vector<double> row;
			for (int j = 0; j != cols; j++)
				row.push_back(init_func());
			data.push_back(row);
		}
	}
	// individual element access - std::vector.at() checks for out_of_range errors
	double& element_ij(int row, int col) { return (data.at(row)).at(col); }
	const double& element_ij(int row, int col) const 
		{ return (data.at(row)).at(col); }

	// matrix size information
	const std::pair<int, int> size() const { return size_pair; };
	const int number_of_rows() const { return size_pair.first; };
	const int number_of_cols() const { return size_pair.second; };

	// arithmetic operations
	std::vector<double> vec_mult(const std::vector<double>& vec) const;
	// transformation option
	void append_row(std::vector<double> row);
private:
	// not const but getters/setters should be for the time being
	std::pair<int, int> size_pair;
	std::vector<std::vector<double>> data;
};

} // namespace mltoolkit
#endif