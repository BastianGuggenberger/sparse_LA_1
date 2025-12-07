#include <iostream>
#include <eigen3/Eigen/Dense>

int main() {
	Eigen::MatrixXd A(4, 4);
	Eigen::VectorXd b(4);
	Eigen::VectorXd x(4); //Solution of Ax = b
	A << 4,1,0,0,
		 1,4,1,0,
		 0,1,4,1,
		 0,0,1,4;

	b << 5,6,6,5;

	for (int i=0; i<500; i++){
		
	}

	return 0;
}
