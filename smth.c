#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<fcntl.h>
#define STRINGSIZE 128
int countWords(char* c){
    int sum = 0;
    for(int i = 0; c[i] != '\0'; i++){
        if(c[i] != ' '){
            sum++;
            while(c[i] != ' '){
                if(c[i] == '\0'){
                    return sum;
                }
                i++;
            }
        }
    }
    return sum;
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


int CheckForDoubleArrow(char* c){
	int counter = 0;
	for(int i = 0; c[i] != '\0'; i++){
		if(c[i] == '>' && c[i + 1] == '>'){
			counter++;
			i++;
		}
	}

	return counter;
}
int CheckForRightArrow(char* c){
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
int CheckForLeftArrow(char* c){
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


char** smallerTokenizer(char* c, int words){
    char** args = malloc(sizeof(char*) * (words + 1));

    char* copy = malloc(sizeof(char) * (strlen(c) + 1));

    strcpy(copy,c);
    char* piece = strtok(copy," ");
    int ind = 0;
    // args[ind] = malloc(sizeof(char) * (strlen(piece) + 1));

    // strcpy(args[ind],piece);
    // ind++;
    while(piece != NULL){
        args[ind] = malloc(sizeof(char) * (strlen(piece) + 1));
        strcpy(args[ind],piece);
        ind++;
        piece = strtok(NULL," ");
        
    }
    free(copy);
    args[ind] = NULL;
    return args;

}

char* getCommand(char* c){
    char* copy = malloc(strlen(c) + 1);
    strcpy(copy,c);
    char* command = strtok(copy," ");
    char* result = malloc(sizeof(char) * (strlen(command) + 1));
    strcpy(result,command);
    free(copy);
    return result;
}


bool vaild_check(int double_croc,int left,int right){
    bool initial_check = double_croc + right < 2;
    if(!initial_check){
        return false;
    }

    if(right > 1){
        return false;
    }
    return true;

}



// char* RemoveLeftCrocodile(char* carr,char* arrow){
//     char* c = malloc(strlen(carr) + 1);
//     strcpy(c,carr);


//     char* piece = strtok(c,arrow);
//     char* str = piece;
//     while(piece != NULL){
//         str = piece;
//         piece = strtok(NULL,arrow);
//     }
//     strip(str);
//     char* filename = strtok(str," ");
//     return filename;
    
// }


char* RemoveLeftCrocodile(char* carr, char* arrow){
    char* c = malloc(strlen(carr) + 1);
    strcpy(c, carr);

    char* piece = strtok(c, arrow);
    char* str = piece;
    while(piece != NULL){
        str = piece;
        piece = strtok(NULL, arrow);
    }
    strip(str);
    char* filename = strtok(str, " ");

    // Copy result before freeing c
    char* result = malloc(strlen(filename) + 1);
    strcpy(result, filename);
    free(c);
    return result;
}
void RemoveFileName(char* c, char* filename, char* arrow){
    if(strcmp(arrow,"<") == 0){
        for(int i = 0; c[i] != '\0'; i++){
            if(c[i] == '<'){
                c[i] = ' ';
            }
        }
    }
    else if(strcmp(arrow,">") == 0){
        for(int i = 0; c[i] != '\0'; i++){
            if(c[i] == '>'){
                c[i] = ' ';
            }
        }
    }
    else{
        for(int i = 0; c[i] != '\0'; i++){
            if(c[i] == '>' && c[i + 1] == '>'){
                c[i] = ' ';
                c[i + 1] = ' ';
                i++;
            }
        }
    }

    int i = 0;
    bool string_found = false;
    for(; c[i] != '\0'; i++){
        if(c[i] == filename[0]){
            string_found = true;
            for(int j = 0; j < strlen(filename); j++){
                if(c[i+j] != filename[j]){ string_found = false; break; }
            }
            if(string_found) break;
        }
    }

    // Shift characters to remove filename
    int length = strlen(filename);
    if(c[i + length] == '\0'){
        for(int k = 0; k < length; k++) c[i++] = '\0';
    } else {
        while(c[i + length] != '\0'){ c[i] = c[i + length]; i++; }
        while(c[i] != '\0') c[i++] = '\0';
    }

    strip(c);
}

int mainT(){

    char currdir[128];
    getcwd(currdir,128);
    printf("\n%s& ",currdir);
    char prompt[128];
    fgets(prompt,sizeof(prompt),stdin);

	prompt[strcspn(prompt, "\n")] = '\0';
    int right = CheckForRightArrow(prompt);
    int left = CheckForLeftArrow(prompt);
    int double_croc = CheckForDoubleArrow(prompt);

    char left_arrow[] = "<"; // write
    char right_arrow[] = ">"; //read
    char double_arrow[] = "<<";
    char* filename;
    char* input_filename;
    bool valid = vaild_check(double_croc,left,right);
    if(!valid){
        printf("Multiple redirections are not allowed\n");
        return 0;
    }

    if(left > 0){
        input_filename = RemoveLeftCrocodile(prompt,"<");
        RemoveFileName(prompt,input_filename, "<");
    }
    else if(double_croc > 0){
        filename = RemoveLeftCrocodile(prompt,">>");
        RemoveFileName(prompt,filename, ">>");
    }


    if(right > 0){
        filename = RemoveLeftCrocodile(prompt,">");

        RemoveFileName(prompt,filename, ">");
    }


    int words = countWords(prompt);
    char* command = getCommand(prompt);

    char** args = smallerTokenizer(prompt, words);





    if(strcmp(command,"cd") == 0){
        if(words == 1){
            chdir("..");
        }
        else{
            if(chdir(args[1]) != 0){
                printf("Couldn't change directory");
            }
        }
        return 0;
    }
    else if(strcmp(command,"exit") == 0){
        return -1;
    }
    if(!fork()){
        if(right > 0){
            int fd = open(filename,O_WRONLY | O_CREAT, 0777);
            dup2(fd,STDOUT_FILENO);
        }
        else if(double_croc> 0){
            int fd = open(filename,O_CREAT | O_WRONLY | O_APPEND, 0777);
            dup2(fd,STDOUT_FILENO);
        }
        if(left > 0){
            int fd = open(input_filename,O_RDONLY, 0777);
            dup2(fd,STDIN_FILENO);            
        }
        execvp(command,args);
    }
    else{
        wait(NULL);
    }

}

void main(){
    while(true){
        if(mainT() == -1){
            break;
        }
    }
}
