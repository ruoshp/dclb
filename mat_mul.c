#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define NRA 3
#define NCA 3
#define NCB 3

int main(){
	int a[NRA][NCA],b[NCA][NCB],c[NRA][NCB],tid,i,k,j,chunk=10;

	#pragma omp parallel shared(a,b,c,chunk) private(tid,i,k,j)
	{
		tid = omp_get_thread_num();
		if(tid==0){
			printf("\nThe number of threads are :- %d",omp_get_num_threads());
		}

		#pragma omp for schedule(static,chunk)
		for(i=0;i<NRA;i++)
			for(j=0;j<NCA;j++)
				a[i][j]=i+j;

		#pragma omp for schedule(static,chunk)
		for(i=0;i<NCA;i++)
			for(j=0;j<NCB;j++)
				b[i][j]=i*j;

		#pragma omp for schedule(static,chunk)
		for(i=0;i<NRA;i++)
			for(j=0;j<NCB;j++)
				c[i][j]=0;

		printf("\nThread %d is starting multiplication......",tid);
		#pragma omp for schedule(static,chunk)
		for(i=0;i<NRA;i++){
			printf("\nThread %d did row %d",tid,i);
			for(j=0;j<NCB;j++)
				for(k=0;k<NCA;k++)
					c[i][j] = a[k][i]*b[k][j];
		}
	}

	printf("\n\nRes matrix :-\n\n");
	for(int i=0;i<NRA;i++){
		for(int j=0;j<NCB;j++)
			printf("%6d",c[i][j]);
		printf("\n");
	}
}
