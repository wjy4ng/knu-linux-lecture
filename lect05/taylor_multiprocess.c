#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#define _USE_MATH_DEFINES
#define N 4

/*
	자식 프로세스를 여러 개 생성하여
	테일러 급수 프로그램을 병렬로 수행
	
	- fork()와 wait()를 사용
	- 데이터 전달을 위해 파이프 사용
		- 자식의 결과값을 부모에 전달
	- gcc는 -lm 붙여서
	- 업로드는 lect05/taylor_multiprocess.c 링크로
*/

void sinx_taylor(int num_elements, int terms, double* x, double* result) {
	for(int i=0; i<num_elements; i++){
		double value = x[i];
		double numer = x[i] * x[i] * x[i];
		double denom = 6.; // 3!
		int sign = -1;

		for(int j=1; j<=terms; j++){
			value += (double)sign * numer / denom;
			numer *= x[i] * x[i];
			denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
			sign *= -1;
		}
		result[i] = value;
	}
}

int main(){
	double x[N] = {0, M_PI/6., M_PI/3., 0.134};
	double res[N];
    
    int pipes[N][2];
    pid_t pids[N];

    for (int i = 0; i < N; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("파이프 생성 실패\n");
			return 1;
        }
    }

	printf("파이프 생성 성공\n");

    for (int i = 0; i < N; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork 에러\n");
            return 1;
        }

        if (pids[i] == 0) {
			printf("fork 성공\n");
            close(pipes[i][0]);

            double child_res;
            sinx_taylor(1, 10, &x[i], &child_res); 

            write(pipes[i][1], &child_res, sizeof(double));
            close(pipes[i][1]);

			return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        close(pipes[i][1]);
        waitpid(pids[i], NULL, 0);
        read(pipes[i][0], &res[i], sizeof(double));
        close(pipes[i][0]);
    }

	for(int i=0; i<N; i++){
		printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}

	return 0;
}
