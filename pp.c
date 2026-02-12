
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

int* getarry(){
	int arr[] = {1,2,3,4};
	return arr;
}

void main(){
	// char c[3] = "abc";
	// char** cc= malloc(1);
	// cc[0] = malloc(4);
	// strcpy(cc[0],c);
	// printf("%s, len = %ld",cc[0],strlen(cc[0]));

	// free(cc[0]);
	// free(cc);


	// char** c = malloc(2);
	// c[0] = "helllo";
	// c[1] = "world";

	// c = realloc(c,3);
	// c[2] = "biatch";

	// printf("%s %s %s\n",c[0],c[1],c[2]);

	// printf("%ld\n",strlen(c[1]));
	// free(c);

	int arr[] = getarry();
	for(int i = 0; i < 4; i++)
		printf("%d",arr[i]);
}

