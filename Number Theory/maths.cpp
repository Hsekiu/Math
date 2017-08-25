#include "maths.h"

int *vars = new int[2];

int gcd(int* nums) {
	int N = nums[0];
	int D = nums[1];

	if (D == 0) {
		return N;
	} else {
		vars[0] = D;
		vars[1] = N % D;
		return gcd(vars);
	}
}

//Euler's totient function
int phi(int* nums) {
	int N = nums[0];

    int res = 0;

    for (int i = 1; i <= N; i++) {
    	vars[0] = N;
    	vars[1] = i;
        if (gcd(vars) == 1) {
            res++;
        }
    }
    return res;
}
