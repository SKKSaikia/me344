//program credit: LLNL tutorial
// required MPI include file  
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	int  numtasks, rank, len, rc; 
	char hostname[MPI_MAX_PROCESSOR_NAME];

	//initialize MPI  
	MPI_Init(&argc,&argv);

	// get number of tasks 
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	// get my rank  
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// this one is obvious  
	MPI_Get_processor_name(hostname, &len);

	MPI_Barrier(MPI_COMM_WORLD);

	// do some work with message passing 
	int my_neighbor_left = (rank-1+numtasks)%numtasks;
	int my_neighbor_right = (rank+1+numtasks)%numtasks;

        int inmsg;	
	int outmsg=rank;

	printf ("Number of tasks= %d My rank= %d Running on %s, going to send %d\n", numtasks,rank,hostname, outmsg);
	
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Status stat;
	MPI_Request reqs[4]; 
	int tag=1;

	//MPI_Isend(&outmsg, 1, MPI_INTEGER, my_neighbor_left, tag, MPI_COMM_WORLD, &reqs[0]); 
	MPI_Recv(&inmsg, 1, MPI_INTEGER, my_neighbor_right, tag, MPI_COMM_WORLD, &stat); 
	MPI_Send(&outmsg, 1, MPI_INTEGER, my_neighbor_left, tag, MPI_COMM_WORLD); 
	//MPI_Waitall(1, reqs, &stat);

	printf("%d received from the rank %d\n",rank, inmsg);

	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0)
		printf("\n DONE WITH THE PROGRAM \n");
	MPI_Barrier(MPI_COMM_WORLD);

	// done with MPI  
	MPI_Finalize();
}
