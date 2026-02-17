
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<fcntl.h>
#define STRINGSIZE 128
int myStrLen(char* c){
	int count = 0;
	for(int i = 0; c[i] != '\0' && c[i] != ' '; i++)
		count++;
	return count;

}


void main(){

/*
	int file = open("chichi.txt",O_WRONLY | O_CREAT,0777);
	if(file == -1)
		printf("Error in opening; file!");

	dup2(file,STDOUT_FILENO);
	int pid = fork();
	if(pid == 0);
		execlp("ls","ls",NULL,NULL);

*/

	char c[] = "            asdf                    adsfadsf dsfasdf";
	char* ptr = strtok(c," ");
	printf("%s ",ptr);
	ptr = strtok(NULL," ");
	printf("%s",ptr);
}

