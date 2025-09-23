#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int result = 0;
	
	if(argc != 4) {
		printf("사용법: %s <숫자1> <연산자> <숫자2>\n", argv[0]);
		printf("예시: %s 1 + 3\n", argv[0]);
		return 1;
	}
	
	int num1 = atoi(argv[1]);
	char* operator = argv[2];
	int num2 = atoi(argv[3]);

	if(strcmp(operator, "+") == 0) result = num1 + num2;
	else if(strcmp(operator, "x") == 0) result = num1 * num2;
	else {
		printf("지원하지 않는 연산자입니다: %s\n", operator);
		printf("지원하는 연산자: +, x\n");
		return 1;
	}

	printf("result = %d\n", result);
	return 0;
}
