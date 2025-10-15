#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int result = 0;
	
	if(strcmp(argv[2], "+") == 0) result = atoi(argv[1]) + atoi(argv[3]);
	else if(strcmp(argv[2], "x") == 0) result = atoi(argv[1]) * atoi(argv[3]);

	printf("result = %d\n", result);
}
