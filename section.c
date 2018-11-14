#include<stdio.h>
#include<omp.h>
#define N 50

int main(){
	int a[N],b[N],c[N],d[N],tid,i,nthreads;

	for(i=0;i<N;i++)
		a[i]=b[i]=i;

	#pragma omp parallel shared(a,b,c,d) private(tid,i)
	{
		tid=omp_get_thread_num();
		if(tid==0)
			printf("\nNo. of threads : %d",omp_get_num_threads());

		printf("\nStarting thread %d",tid);
		
		#pragma omp sections nowait
		{
			
			#pragma omp section
			{
				printf("\nThread %d doing section 1",tid);
				for(i=0;i<N;i++){
					c[i]=a[i]+b[i];
					printf("\nThread %d :- c[%d] = %d",tid,i,c[i]);
				}
			}
		
			#pragma omp section
			{
				printf("\nThread %d doing section 2",tid);
				for(i=0;i<N;i++){
					d[i]=a[i]*b[i];
					printf("\nThread %d :- d[%d] = %d",tid,i,d[i]);
				}
			}
		}
	}
}

