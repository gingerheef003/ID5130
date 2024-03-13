#include <math.h>
#include <mpi.h>
#include <stdio.h>

#define PI 3.1415

double func(double x) {
	return (1.0 + sin(x));
}

double trapezoidal_rule(double la, double lb, double ln, double h) {
	double total;
	double x;
	int i;

	total = (func(la) + func(lb))/2.0;
	for(i = 1; i < ln; i++) {
		x = la + i*h;
		total += func(x);
	}
	total *= h;

	return total;
}

int main(int argc, char* argv[]) {
	double a, b, final_result, la, lb, lsum, h;
	int myid, nprocs, proc;
	int n, ln;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	n = 1024;
	a = 0.0;
	b = PI;
	final_result = 0.0;

	h = (b-a)/n;
	ln = n/nprocs;

	la = a + myid*ln*h;
	lb = la + ln*h;
	lsum = trapezoidal_rule(la, lb, ln, h);

	if(myid != 0) {
		MPI_Send(&lsum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	} else {
		final_result = lsum;
		for(proc = 1; proc < nprocs; proc++) {
			MPI_Recv(&lsum, 1, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			final_result += lsum;
		}

		printf("The integral of f(x) = 1 + sin(x) from %f to %f is %f\n", a, b, final_result);
	}


	MPI_Finalize();
}
