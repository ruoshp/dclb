#include<stdio.h>
#include<omp.h>

int main(){
	int tid,nthreads;

	#pragma omp parallel private(tid,nthreads)
	{
		tid=omp_get_thread_num();
		if(tid==0)
		{
			printf("\nThread %d getting the environment info....",tid);

			printf("\nThe number of processors are = %d",omp_get_num_procs());
			printf("\nThe number of threads are = %d",omp_get_num_threads());
			printf("\nThe max number of threads are = %d",omp_get_max_threads());
			printf("\nIn parallel enabled = %d",omp_in_parallel());
			printf("\nDynamic threads enabled = %d",omp_get_dynamic());
			printf("\nNested parallelism supported = %d",omp_get_nested());			
		}
	}
}

