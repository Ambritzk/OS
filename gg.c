#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<fcntl.h>
#define STRINGSIZE 128
int mysln(char* c, int i){
	int count = 0;
	for(i; c[i] != '\0' && c[i] != ' '; i++)
		count++;
	return count;

}

void strip(char* c){
	int len = strlen(c);
	if(len == 0)
		return;
	int ind1 = 0;
	int ind2 = 0;
	for(int i = len - 1; c[i] == ' ' && i >=0 ; i--){
		c[i] = '\0';
	}
	
	while(c[ind2] == ' '){
		ind2++;
	}
	for(ind2; c[ind2] != '\0';ind2++){
		c[ind1++] = c[ind2];
	}
	c[ind1] = '\0';

}

int countspaces(char* c){
	int count = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] != ' ' && c[i + 1] == ' ')
			count++;
	}

	return count;
}

int CheckForDoubleCrocodile(char* c){
	int counter = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] == '>' && c[i + 1] == '>'){
			counter++;
			i++;
		}
	}
	
	return counter;
}
int CheckForLeftCrocodile(char* c){
	int counter = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] == '>'){
			if(c[i + 1] != '>')
				counter++;
			i++;
		}
	}
	
	return counter;
}
int CheckForRightCrocodile(char* c){
	int counter = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] == '<'){
			if(c[i + 1] != '<')
				counter++;
			i++;
		}
	}
	
	return counter;
}

char** Tokenize(char* command, char* c, int i,int arg){
		char** args = (char**) malloc(sizeof(char*) * (arg + 2));
		int string_no = 1;
		int string_ind = 0;
		args[0] = malloc(strlen(command) + 1); // changed to 2 form 1
		strcpy(args[0],command);
		args[1] = malloc(mysln(c,i) + 1);
		for(i; c[i] != '\0'; i++){
			if(c[i] == ' '){
				while(c[i + 1] == ' '){
					i++;
				}
				args[string_no++][string_ind] = '\0';
				string_ind = 0;
				args[string_no] = malloc(mysln(c,i + 1) + 1);
				
				continue;
			}
			args[string_no][string_ind++] = c[i];
		}
		args[string_no++][string_ind] = '\0';
		args[string_no] = NULL;

		return args;
}
bool vaild_check(int double_croc,int left,int right){
	if(double_croc == 0){
		if(left == 0 || left == 1){
			if(right == 0 || right == 1){
				return true;
			}
		}
		return false;
	}
	else{
		if(left == 0){
			if(right == 0 || right == 1){
				return true;
			}
		}
		return false;
	}
}

void mainT(){

	char cwd[STRINGSIZE];
	char c[STRINGSIZE];
	getcwd(cwd,STRINGSIZE);
	printf("%s&",cwd);
	fgets(c,sizeof(c),stdin);
	c[strcspn(c, "\n")] = '\0';
	strip(c);



	int double_croc = CheckForDoubleCrocodile(c);
	int left = CheckForLeftCrocodile(c);
	int right = CheckForRightCrocodile(c);
	bool valid = vaild_check(double_croc,left,right);

	if(!valid){
		printf("Not valid");
		return;
	}
//	from here we're going to try to separate the commands and the arguements
	char command[STRINGSIZE];
	int i = 0;
	for(i; c[i] != '\0'; i++){
		if(c[i] == ' ')
			break;
		command[i] = c[i];
	}
	command[i++] = '\0';

	if(strcmp(command,"exit") == 0){
		printf("\nExit");
		exit(0);
	}

	int arg = countspaces(c);

	if(arg > 0){

		char** args = Tokenize(command,c,i,arg);
		if(strcmp(command,"cd") == 0){
			chdir(args[1]);
			return;
		}

		if(double_croc == 0 && left == 0 && right == 0){
			int pid = fork();
			if(pid == 0)
				execvp(command,args);
			if (pid != 0)
				wait(NULL);
		}

		if(right > 0){
			char* filename;
			for(int i = 0; args[i] != NULL; i++){
				if(strcmp(args[i],"<") == 0){
					filename = args[i + 1];
					if(left == 0 && double_croc == 0){
						args[i] = NULL;
					}
					else{
						args[i] = " ";
					}
					break;
				}
			}
			int fileid = open(filename,O_RDONLY);
			if(fileid < 0){
				printf("File not found");
				return;
			}

			dup2(fileid,STDIN_FILENO);
			if(left == 0 && double_croc == 0){
				execvp(command,args);
			}
		}


		if(left > 0){
			char* filename;
			for(int i = 0; args[i] != NULL; i++){

				if(strcmp(args[i],">") == 0){
					filename = args[i + 1];
					args[i] = NULL;
					break;
				}
			}
			int pid3 = fork();
			if(pid3 == 0){
				printf("FIlename = %s\nAnd the args = ",filename);
				for(int i = 0; args[i] != NULL; i++)
					printf("%s ",args[i]);
				printf("\n");
				int filep = open(filename,O_WRONLY | O_CREAT,0777);
//				close(filep);
				dup2(filep,STDOUT_FILENO);
				execvp(command,args);
				exit(0);
			}
			else{
				wait(NULL);
			}
		}
		else if(double_croc > 0){
			char* filename;
			for(int i = 0; args[i] != NULL; i++){
				if(strcmp(args[i],">>") == 0){
					filename = args[i + 1];
					args[i] = NULL;
				}
			}
			int pid3 = fork();
			if(pid3 == 0){
				if(filename == NULL){
					printf("No file");
					return;
				}
				int file_double = open(filename,O_CREAT | O_WRONLY | O_APPEND,0777);
				dup2(file_double,STDOUT_FILENO);
				execvp(command,args);
				exit(0);
			}
			else{
				wait(NULL);
			}
		}



	}
	else{
		if(strcmp(command,"cd") == 0){
			chdir("..");
		}

		int pid2 = fork();
		if(pid2 == 0){
			execlp(command,command,NULL);
		}
		if(pid2 != 0){
			wait(NULL);
		}
	}




}

void main(){
	while(true){
		mainT();
	}

}
