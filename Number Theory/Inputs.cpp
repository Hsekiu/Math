#include <iostream>
#include <stdlib.h> 
#include <map>
#include <string>

#include "maths.h"

//Since there is no reflection just use a map.
typedef int(*funcPtr)(int*);
std::map<std::string, funcPtr> func_map;

int *inputs(int argc, char *argv[]) {

	int *nums = new int[argc-2];

	for(int i = 0; i <= argc-3; i++) {
		int tmp = atoi(argv[i+1]);
		nums[i] = tmp;
	}

	return nums;
}

void processFuncs() {
	func_map["gcd"] = &gcd;
	func_map["phi"] = &phi;
}

int main(int argc, char *argv[]) {
	int *nums;
	nums = inputs(argc, argv);
	processFuncs();

	int result = func_map[argv[argc-1]](nums);

	std::cout << "Result of " << argv[argc-1] << " is :" << result << std::endl;

	return 1;
}