#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int acc = 0;
pthread_mutex_t lock; // mutex 선언

void *TaskCode(void *argument){
	int tid = *((int*) argument);

	// 기존의 lock은 한명 한명이 옷을 한번만 갈아입는걸 100만 번 반복해야 하는 문제 발생
	// 이를 해결하기 위해 각 쓰레드가 계산을 하고 마지막에 lock으로 누적시키면 됨
	int partial_acc = 0;
	for(int i=0; i<1000000; i++) partial_acc = partial_acc + 1;

	/*
		tid=0이면 0~24
		tid=1이면 25~49
		tid=2이면 50~74
		tid=3이면 75~99까지 thread를 나눠서 실행
	*/

	pthread_mutex_lock(&lock);
	acc += partial_acc;
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t threads[4];
	int args[4];
	int i;

	// Init Mutex
	pthread_mutex_init(&lock, NULL);

	// create all threads
	for(i=0; i<4; i++){
		args[i] = i;
		pthread_create(&threads[i], NULL, TaskCode, (void *) &args[i]);
	}

	// wait for all threads to complete
	for(i=0; i<4; i++) pthread_join(threads[i], NULL);

	printf("Final acc value: %d\n", acc);

	// clear Mutex
	pthread_mutex_destroy(&lock);

	return 0;
}
