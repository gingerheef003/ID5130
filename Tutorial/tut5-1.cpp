#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

double getSum(double* e, double* x, int n) {
	double sum = 0;
	for(int i = 0; i < n; i++) sum += arr[i];
	return sum;
}


int main() {
	int n;
	cout << "Give value of n: ";
	cin >> n;

	double eps = 0.001;
	int iter = 0;




	double** A = new double*[n];
	for (int i = 0; i<n; i++) {
		A[i] = new double[n];
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) A[i][j] = i+j;
			else if(i == 0 && j == n-1) A[i][j] = 1;
			else if(j == 0 && i == n-1) A[i][j] = 2*n-1;
			else A[i][j] = 1.0/n;
		}
	}

	double* x = new double[n];
	double* b = new double[n];
	double* e = new double[n];

	b[0] = 1; x[0] = 0; e[0] = 0;
	for(int i = 1; i < n; i++) {
		x[i] = 0;
		b[i] = 0;
		e[i] = 0;
	}





	do {
		double* x_new = new double[n];
		
		for(int i = 0; i < n; i++) {
			cout << x[i] << " ";
			x_new[i] = 0;
			for(int j = 0; j < n; j++) {
				if(i == j) continue;
				x_new[i] += A[i][j] * x[j];
			}
			x_new[i] = b[i] = x_new[i];
			x_new[i] = x_new[i] / A[i][i];
		}
		cout << endl;
		for(int i = 0; i < n; i++) {
			e[i] = abs(x_new[i] - x[i]);
			x[i] = x_new[i];
			cout << endl;
		}
	} while(getError(e, x, n, eps));


}
