#include <cmath>
#include <cstdlib>
#include <iostream>
#include <omp.h>

using namespace std;

int main() {
	double del = 0.1, del2 = 0.01;
	double ll = -1.0, ul = 1.0;
	int n = (ul - ll) / del + 1;
	bool loop;

	double a[n][n];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			a[i][j] = 0;
		}
	}

	double q[n][n], f[n][n];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			double x2 = pow(-1 + del*j, 2);
			double y2 = pow(-1 + del*i, 2);
			q[i][j] = 2 * (2 - x2 - y2);
			f[i][j] = (x2 - 1) * (y2 - 1);
		}
	}

	int cnt = 0;
	double start = omp_get_wtime();
	do {
		cnt++;
		for(int i = 1; i < n-1; i++) {
			for(int j = 1; j < n-1; j++) {
				a[i][j] = 1.0/4 * (a[i+1][j] + a[i-1][j] + a[i][j+1] + a[i][j-1]) + del2/4 * q[i][j]; 
			}
		}
		loop = false;
		for(int i = 1; i < n-1; i++) {
			for(int j = 1; j < n-1; j++) {
				if(abs(a[i][j] - f[i][j]) > del2 * f[i][j]) {
					loop = true;
					continue;
				}
			}
		}
	} while(loop);
	double end = omp_get_wtime();

	cout << "Time taken: " << end - start << endl;

	cout << "Number of iterations: " << cnt << endl;

	cout << "Values of phi with x for y=0.5:" << endl;
	cout << "[";
	int j05 = (0.5 - (-1)) / del;
	for(int i = 0; i < n-1; i++) {
		cout << a[i][j05] << ",";
	}
	cout << a[n-1][j05] << "]" << endl;

}
