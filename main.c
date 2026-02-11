// Source - https://stackoverflow.com/a/19757967
// Posted by steveha, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-08, License - CC BY-SA 3.0
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#define STRING_SIZE 128
void parse(char* c){
	char els[STRING_SIZE] = "ls";

	int pid = fork();
	if(pid == 0){
		execlp(c,c,NULL);
	}
	if (pid != 0)
		wait(NULL);

}

void empty(char c[]){
	for(int i = 0; c[i] != '\0'; i++){
		c[i] = '\0';
	}

}
void main(){

	char prompt[STRING_SIZE];

	while(true){
		printf(">");
		fgets(prompt, sizeof(prompt), stdin);
		prompt[strcspn(prompt,"\n")] = '\0';
		parse(prompt);
		empty(prompt);
	}
}
