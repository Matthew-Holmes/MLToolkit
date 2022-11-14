#include "mltoolkit.h"

#include <cmath>

int main() {
	auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
	auto actn_func = [](double d) { return d; };
	// mltoolkit::Matrix mat(3, 3, rand_getter);
	mltoolkit::Matrix mat(3, 3, 1.0);
	std::cout << "matrix with size: ";
	std::cout << mat.size().first << " " << mat.size().second << std::endl;
	std::cout << "so " << mat.number_of_rows() << " rows, and " 
		<< mat.number_of_cols() << " cols" << std::endl;
	std::cout << "data is: " << std::endl;	
	mat.element_ij(1, 1) = 0.0;
	for (int i = 0; i < mat.number_of_rows(); i++) {
		for (int j = 0; j < mat.number_of_cols(); j++) {
			std::cout << mat.element_ij(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "testing matrix vector multiplication" << std::endl;
	std::vector<double> vec{ 1.0, 2.0, 3.0 };
	vec = mat.vec_mult(vec);
	for (auto d : vec) {
		std::cout << d << " ";
	}
	std::cout << std::endl;

	int k;
	std::cin >> k;
	return 0;
}
