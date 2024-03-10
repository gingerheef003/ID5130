#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int rank, neighbour;
	int max_count = 1000000;
	int counter = 0;
	int bored;
	int ball = 1;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	neighbour = 1 - rank;
	
	if(rank == 0) {
		MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}

	counter = 0;
	bored = 0;
	while(!bored) {
		MPI_Recv(&ball, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &status);

		counter += 1;
		MPI_Send(&ball, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD);

		bored = counter >= max_count;
	}

	printf("Rank %d is bored and giving up\n", rank);

	return MPI_Finalize();
}
