#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int acc = 0;
pthread_mutex_t lock;  // 뮤텍스 선언

void *TaskCode(void *argument){
    int tid = *((int*) argument);

    /*
        tid=0이면 0~24
        tid=1이면 25~49
        tid=2이면 50~74
        tid=3이면 75~99까지 thread를 나눠서 실행
    */
    for(int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);   // 임계 구역 진입
        acc += 1;
        pthread_mutex_unlock(&lock); // 임계 구역 해제
    }

    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t threads[4];
    int args[4];
    int i;

    // 뮤텍스 초기화
    pthread_mutex_init(&lock, NULL);

    // create all threads
    for(i = 0; i < 4; i++){
        args[i] = i;
        pthread_create(&threads[i], NULL, TaskCode, (void *)&args[i]);
    }

    // wait for all threads to complete
    for(i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    // 결과 출력
    printf("Final acc value: %d\n", acc);

    // 뮤텍스 해제
    pthread_mutex_destroy(&lock);

    return 0;
}
