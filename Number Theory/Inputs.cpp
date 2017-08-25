#include <iostream>
#include <stdlib.h> 

int *inputs(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Incorrect amount of arguments supplied: " << argc << std::endl;
	}

	int N = atoi(argv[1]);
	int D = atoi(argv[2]);

	int *nums = new int[2];
	nums[1] = N;
	nums[2] = D;
	return nums;
}

//Euclidean division

int main(int argc, char *argv[]) {
    int *nums;
	nums = inputs(argc, argv);
    
	return 1;
}