#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int hap = 0;
	for(int i=0; i<argc; i++){
		if(strcmp(argv[i], "calc") == 0){
			if(strcmp(argv[i+2], "+") == 0) hap = atoi(argv[i+1]) + atoi(argv[i+3]);
			else if(strcmp(argv[i+2], "x") == 0) hap = atoi(argv[i+1]) * atoi(argv[i+3]);
		}
	}
	printf("hap = %d\n", hap);
}
