#include <iostream>
#include <eigen3/Eigen/Dense>

int main() {

	int max_iterations = 500;
	double accuracy = 1e-9;

	Eigen::MatrixXd A(4, 4);
	Eigen::VectorXd b(4);
	Eigen::VectorXd x(4); //Solution of Ax = b
	A << 4,1,0,0,
		 1,4,1,0,
		 0,1,4,1,
		 0,0,1,4;

	b << 5,6,6,5;

	Eigen::MatrixXd M = A.diagonal().asDiagonal();
	Eigen::MatrixXd M_inverse = M.inverse();

	Eigen::VectorXd x_old(4); //For comparison
	int n=0;

	for(int i=0; i<max_iterations; i++){

		//print current x
		std:: cout << x[0];
		for (int j=1; j<x.size(); j++){
			std::cout << "," << x[j];
		}
		std::cout << std::endl;

		//calculate new x
		x_old = x;
		x = x + M_inverse * (b - A * x);
		n+=1;

		//check for convergence
		if((x-x_old).norm()<accuracy) break;
		

	}

	std::cout << std::endl << n << " iterations" << std::endl;
	
	return 0;
}