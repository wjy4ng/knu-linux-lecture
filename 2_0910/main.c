#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 100
char line[MAXLINE];
char longest[MAXLINE];

int main(){
	int len;
	int max=0;
	while(fgets(line, MAXLINE, stdin) != NULL){
		len = strlen(line);
		if(len > max){
			max = len;
			copy(line, longest);
		}
	}

	if(max > 0) printf("%s", longest);

	return 0;
}
