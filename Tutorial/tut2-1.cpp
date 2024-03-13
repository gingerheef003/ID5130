#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

#ifdef _OPENMP
#include <omp.h>
#endif

double func(double x) {
	return sin(x)/(2 * pow(x,3));
}

void parallel_integrate(int n, double a, double b, double *result) {
	double h, x, total;
	int tc = omp_get_num_threads();
	int mr = omp_get_thread_num();
	int ln;
	double la, lb;

	h = (b-a) / n;

	ln = n / tc;
	la = a + mr * ln * h;;
	lb = la + ln*h;

	total = (func(la) + func(lb)) / 2.0;
	for(int i = 1; i <= ln-1; i++) {
		x = la + i*h;
		total += func(x);
	}

	total = total * h;

	#pragma omp critical
	*result += total;
}

int main(int argc, char* argv[]) {
	int tc = 1;

	if(argc == 2) 
		tc = strtol(argv[1], NULL, 10);
	else {
		printf("\n A command lineargument other than name of the executable is required...exiting the program...");
		return 1;
	}

	double a = 1, b = M_PI, final_result = 0.0;
	int n = 2048;

	#pragma omp parallel num_threads(tc)
	parallel_integrate(n, a, b, &final_result);

	printf("n The area under the curve sin(x)/(2x^3) between 1 and PI is equal to %lf\n\n", final_result);

	return 0;
}
