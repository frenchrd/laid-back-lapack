#ifndef LB_WALLTIMER_INCLUDED
	#define Initialize_Walltimer() double time0 = MPI_Wtime(); double time1;
	#define Walltimer_Label(rank_id,msg) time1 = MPI_Wtime(); printf("## [Rank %d] " msg " (%fs)\n",rank_id,time1 - time0); time0 = time1;
	#define LB_WALLTIMER_INCLUDED
#endif
