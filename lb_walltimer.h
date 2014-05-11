#ifndef LB_WALLTIMER_INCLUDED
	typedef struct walltimer_metadata {
		int rank_id;
		double time0;
		double time1;
	} WalltimerMetadata;
	#define Initialize_Walltimer(rank) WalltimerMetadata __wtmmd; __wtmmd.time0 = MPI_Wtime(); __wtmmd.rank_id = rank;
	#define Walltimer_Label(msg) __wtmmd.time1 = MPI_Wtime(); printf("## [Rank %d] " msg " (%fs)\n",__wtmmd.rank_id,__wtmmd.time1 - __wtmmd.time0); __wtmmd.time0 = __wtmmd.time1;
	#define LB_WALLTIMER_INCLUDED
#endif
