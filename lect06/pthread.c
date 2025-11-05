#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int S[100], A[100], B[100];

void InitArray(){
	for(int i=0; i<100; i++){
		A[i] = i;
		B[i] = i;
	}
}

void *TaskCode(void *argument){
	int tid;
	tid = *((int*) argument);
	/*
		tid=0이면 0~24
		tid=1이면 25~49
		tid=2이면 50~74
		tid=3이면 75~99까지 thread를 나눠서 실행
	*/
	for(int i=tid*25; i<(tid+1)*25; i++){
		S[i] = A[i] + B[i];
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t threads[4];
	int args[4];
	int i;

	InitArray();	

	// create all threads
	for(i=0; i<4; i++){
		args[i] = i;
		pthread_create(&threads[i], NULL, TaskCode, (void *) &args[i]);
	}

	// wait for all threads to complete
	for(i=0; i<4; i++) pthread_join(threads[i], NULL);

	for(int i=0; i<100; i++) printf("S: %d\n", S[i]);
	return 0;
}
