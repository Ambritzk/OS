
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#define STRINGSIZE 128
int myStrLen(char* c){
	int count = 0;
	for(int i = 0; c[i] != '\0' && c[i] != ' '; i++)
		count++;
	return count;

}

void main(){
	char c[3] = "abc";
	char** cc= malloc(1);
	cc[0] = malloc(4);
	strcpy(cc[0],c);
	printf("%s, len = %ld",cc[0],strlen(cc[0]));

	free(cc[0]);
	free(cc);
}

