#include <cmath>
#include <cstdlib>
#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printf("\n A command line argument other than name of the executable is required...exiting the program..\n");
		return 1;
	}

	int thread_count = strtol(argv[1], NULL, 10);

	double del = 0.01;
	double del2 = pow(del,2);
	double ll = -1.0, ul = 1.0;
	int n = (ul - ll) / del + 1;
	bool loop;

	double a[n][n], q[n][n], f[n][n];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			a[i][j] = 0;
			double x2 = pow(-1 + del*j, 2);
			double y2 = pow(-1 + del*i, 2);
			q[i][j] = del2 * 2 * (2 - x2 - y2) / 4;
			f[i][j] = (x2 - 1) * (y2 - 1);
		}
	}

	int i,j,k;
	int start, end;

	double start_time = omp_get_wtime();
	#pragma omp parallel num_threads(thread_count) private(i,j) shared(k,n,q,loop,start,end,a,f) default(none)
	{
		#pragma omp single
		{
			do {
				for(k = 2; k < 2*n-3; k++) {
					if(k < n) {
						start = 1;
						end = k;
					} else {
						start = 2 + k - n;
						end = n-1;
					}
					#pragma omp parallel for
					for(j = start; j < end; j++) {
						i = k - j;
						
						a[i][j] = 1.0/4 * (a[i+1][j] + a[i-1][j] + a[i][j+1] + a[i][j-1]) + q[i][j]; 
					}
				}
		
		
				loop = false;
				for(int i = 1; i < n-1; i++) {
					for(int j = 1; j < n-1; j++) {
						if(abs(a[i][j] - f[i][j]) > 0.01 * f[i][j]) {
							loop = true;
							break;
						}
					}
					if(loop) break;
				}
			} while(loop);
	
		}
	}
		double end_time = omp_get_wtime();

	cout << "Time taken: " << end_time - start_time << endl;

//	int j05 = (0.5 - (-1)) / del;
//	cout << "Values of phi with x for y=0.5:" << endl;
//	cout << "[";
//	for(int i = 0; i < n-1; i++) {
//		cout << a[i][j05] << ",";
//	}
//	cout << a[n-1][j05] << "]" << endl;

}
