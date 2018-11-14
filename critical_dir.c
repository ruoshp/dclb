#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<unistd.h>

void A(int *a){
	printf("\na++");
	(*a)++;
}

void B(int *a){
	printf("\na--");
	(*a)--;
}

void f(int *a){
	#pragma omp critical
	printf("\nThis is thread %d of %d",omp_get_thread_num(),omp_get_num_threads());
	A(a);

	sleep(5);

	#pragma omp critical
	printf("\nThis is thread %d of %d",omp_get_thread_num(),omp_get_num_threads());
	B(a);

}

int main(){
	int i,a=0;
	#pragma omp parallel for
	for(i=0;i<4;i++){
		printf("\nThe number of threads triggered is %d",omp_get_num_threads());
		f(&a);
	}
}
