#include "mltoolkit.h"

int main() {
	mltoolkit::Matrix mat(3, 3, 1.0);
	std::cout << "matrix with size: ";
	std::cout << mat.size().first << " " << mat.size().second << std::endl;
	std::cout << "so " << mat.number_of_rows() << " rows, and " 
		<< mat.number_of_cols() << " cols" << std::endl;
	std::cout << "data is: " << std::endl;	
	for (int i = 0; i < mat.number_of_rows(); i++) {
		for (int j = 0; j < mat.number_of_cols(); j++) {
			std::cout << mat.element_ij(i, j) << " ";
		}
		std::cout << std::endl;
	}
	int k;
	std::cin >> k;
	return 0;
}
