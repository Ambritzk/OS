
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#define STRINGSIZE 128
int mysln(char* c, int i){
	int count = 0;
	for(i; c[i] != '\0' && c[i] != ' '; i++)
		count++;
	return count;

}

int countspaces(char* c){
	int count = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] == ' ')
			count++;
	}

	return count;
}

void main(){

	char c[STRINGSIZE];
	printf("Enter a string: ");
	fgets(c,sizeof(c),stdin);
	c[strcspn(c, "\n")] = '\0';

//	from here we're going to try to separate the commands and the arguements
	char command[STRINGSIZE];
	int i = 0;
	for(i; c[i] != '\0'; i++){
		if(c[i] == ' ')
			break;
		command[i] = c[i];
	}
	command[i++] = '\0';
	int arg = countspaces(c);
	if(arg > 0){
		char** args = (char**) malloc(arg + 2);
		int string_no = 1;
		int string_ind = 0;
		args[0] = malloc(strlen(command) + 1);
		strcpy(args[0],command);
		args[1] = malloc(mysln(c,i) + 1);
		for(i; c[i] != '\0'; i++){
			if(c[i] == ' '){
				args[string_no++][string_ind] = '\0';
				string_ind = 0;
				args[string_no] = malloc(mysln(c,i + 1) + 1);
				continue;
			}
			args[string_no][string_ind++] = c[i];
		}
		args[string_no++][string_ind] = '\0';
		args[string_no] = NULL;

		for(int k = 0; k < arg + 2; k++){
			if(args[k] == NULL)
				printf("NULL\n");
			printf("%s ",args[k]);
		}

		int pid = fork();
		if(pid == 0)
			execvp(command,args);
		if (pid != 0)
			wait(NULL);



		int j = 0;
		while(args[j] != NULL){
			free(args[j]);
			j++;
		}
		free(args);
	}
	else{
		int pid2 = fork();
		if(pid2 == 0){
			execlp(command,command,NULL);
		}
		if(pid2 != 0){
			wait(NULL);
		}
	}
/*
	int pid = fork();
	if (pid == 0)
		execvp(command,args);
	if(pid != 0)
		wait(NULL);

*/

//	printf("%s",command);
//	for(int i = 0; i < arg_ind; i++)
//		printf("%s",args[i]);

}

