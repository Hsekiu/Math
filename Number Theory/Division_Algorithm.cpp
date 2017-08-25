#include <iostream>
#include <stdlib.h> 
#include <map>
#include <string>

//#include "maths.h"

int eulerDivAlg(int N) {
	return N;
}

//Since there is no reflection just use a map.
typedef int(*funcPtr)(int);
std::map<std::string, funcPtr> func_map;

int *inputs(int argc, char *argv[]) {
	if (argc != 4) {
		std::cout << "Incorrect amount of arguments supplied: " << argc << std::endl;
	}

	int N = atoi(argv[1]);
	int D = atoi(argv[2]);

	int *nums = new int[2];
	nums[1] = N;
	nums[2] = D;
	return nums;
}

void processFuncs() {
	func_map["euler"] = &eulerDivAlg;
}

int main(int argc, char *argv[]) {
    int *nums;
	nums = inputs(argc, argv);
	processFuncs();
	int test = func_map[argv[3]](4);

	return 1;
}