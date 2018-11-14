#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#define MAX 655536

int main(){
	int noofelem,i,cur_max,current_max;
	omp_lock_t MLOCK;

	printf("\nEnter number of elements : ");
	scanf("%d",&noofelem);

	int *a = (int*) malloc(sizeof(int)*noofelem);

	srand(MAX);
	for(i=0;i<noofelem;i++)
		a[i]=rand();

	cur_max=0;
	omp_set_num_threads(8);
	omp_init_lock(&MLOCK);

	#pragma omp parallel for
	for(i=0;i<noofelem;i++)
	{
		if(a[i]>cur_max)
		{
		omp_set_lock(&MLOCK);
		if(a[i]>cur_max)
			cur_max=a[i];
		omp_unset_lock(&MLOCK);		
		}
	}
	omp_destroy_lock(&MLOCK);
	
	current_max=0;
	for(i=0;i<noofelem;i++)
		if(a[i]>cur_max)
			cur_max=a[i];

	printf("\nThe array elelmts are :-\n");
	for(i=0;i<noofelem;i++)
		printf("%d\t",a[i]);


	if(cur_max==current_max)
		printf("\nSerial = Parallel");		

	else printf("\nSerial = Parallel");		

	free(a);
}
