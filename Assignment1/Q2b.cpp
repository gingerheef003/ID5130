#include <cmath>
#include <cstdlib>
#include <iostream>
#include <omp.h>

using namespace std;

void printArr(double a[4], int n) {
	for(int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

double f(double x) {
	return sin(5*x);
}

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printf("A command line argument other than name of the executable is required...exiting the program..\n");
		return 1;
	}

	int thread_count = strtol(argv[1], NULL, 10);

	double ll = 0, ul = 3;
	int n = 100;
	double h = (ul - ll) / (n - 1);

	double a[n], b[n], c[n], y[n], x[n];
	for(int i = 0; i < n; i++) {
		a[i] = 1;
		b[i] = 4;
		c[i] = 1;
		y[i] = 3/h * (f(h*(i+1)) - f(h*(i-1)));
	}
	a[0] = 0; a[n-1] = 2;
	b[0] = 1; b[n-1] = 1;
	c[0] = 2; c[n-1] = 0;
	y[0]  = 1/h * (-5.0/2*f(ll) + 2*f(ll + h) + 1.0/2*f(ll + 2*h));
	y[n-1] = 1/h * (5.0/2*f(ul) - 2*f(ul - h) - 1.0/2*f(ul - 2*h));

	double alpha, beta;
	int lim = ceil(log2(n));

	int pow2,i,k;
	double ak[n+1], bk[n+1], ck[n+1], yk[n+1];

	double start = omp_get_wtime();

	#pragma omp parallel num_threads(thread_count) private(i,alpha,beta) shared(a,b,c,y,pow2,ak,bk,ck,yk,k,n,lim) default(none)
	for(k = 0; k < lim; k++) {
		pow2 = pow(2,k);

		// Calculating the new a,b,c,y values
		#pragma omp for
		for(i = 0; i < n; i++) {
			bk[i] = b[i];
			yk[i] = y[i];
			if(i >= pow2) {
				alpha = -a[i] / b[i-pow2];
				ak[i] = alpha * a[i-pow2];
				bk[i] += alpha * c[i-pow2];
				yk[i] += alpha * y[i-pow2];
			}
			if(i < n-pow2) {
				beta = -c[i]/b[i+pow2];
				ck[i] = beta * c[i+pow2];
				bk[i] += beta * a[i+pow2];
				yk[i] += beta * y[i+pow2];
			}
		}

		// Updating a,b,c,y with new values
		for(i = 0; i < n; i++) {
			if(i >= pow2) {
				a[i] = ak[i];
			}
			if(i < n-pow2) {
				c[i] = ck[i];
			}
			b[i] = bk[i];
			y[i] = yk[i];
		}
	}

	double end = omp_get_wtime();

	// Computing the answer
	for(int i = 0; i < n; i++) {
		x[i] = y[i] / b[i];
	}

	// Printing the answer
	cout << "[";
	for(int i = 0; i < n-1; i++) {
		cout << x[i] << ",";
	}
	cout << x[n-1] << "]" << endl;

	cout << "Time taken: " << end - start << endl;
}
