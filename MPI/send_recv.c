#include <math.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int rank, n_ranks, my_pair;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank%2 == 0) {
		my_pair = rank + 1;
	} else {
		my_pair = rank - 1;
	}

	if(my_pair < n_ranks) {
		if(rank%2 == 0) {
			char *message = "Hello, world!\n";
			MPI_Send(message, 16, MPI_CHAR, my_pair, 0, MPI_COMM_WORLD);
		} else {
			char message[16];
			MPI_Status status;
			MPI_Recv(message, 16, MPI_CHAR, my_pair, 0, MPI_COMM_WORLD, &status);
			printf("%s", message);
		}


	}

		return MPI_Finalize();
}
