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



char* RemoveLeftCrocodile(char* carr){
    char* c = malloc(strlen(carr) + 1);
    strcpy(c,carr);


    char* piece = strtok(c,">");
    char* str = piece;
    while(piece != NULL){
        str = piece;
        piece = strtok(NULL,">");
    }
    strip(str);
    char* filename = strtok(str," ");
    return filename;
    
}
void RemoveFileName(char* c, char* filename){
    int i = 0;
    bool string_found = false;
    for(i; c[i] != '\0'; i++){
        if(c[i] == filename[0]){
            string_found = true;
            int j = 0;
            for(j; j < strlen(filename); j++){
                if(c[i + j] != filename[j]){
                    string_found = false;
                    break;
                }
            }
            if(string_found){
                break;
            }
        }
    }

    int length = strlen(filename);
    if(c[i + length] == '\0'){
        for(int k = 0; k < length; k++){
            c[i++] = '\0';
        }
    }
    else{
        
        while(c[i + length] != '\0'){
            c[i] = c[i + length];
            i++;
        }
        while(c[i] != '\0'){
            c[i++] = '\0';
        }
    }

    i = 0;
    for(i; c[i] != '\0'; i++){
        if(c[i] == '>'){
            c[i] = ' ';
            break;
        }
    }
    // int spaces = 0;
    // for(int j = i; c[j] != ' '; j++){
    //     spaces++;
    // }
    // spaces--;
    // for(i; )


    
}
void main(){

    char prompt[128];
    printf("Enter string:");
    fgets(prompt,sizeof(prompt),stdin);

	prompt[strcspn(prompt, "\n")] = '\0';
    int left = CheckForLeftCrocodile(prompt);
    int right = CheckForRightCrocodile(prompt);
    int double_croc = CheckForDoubleCrocodile(prompt);
    
    bool valid = vaild_check(double_croc,left,right);
    if(!valid)
        return;

    if(left > 0){
        
        char* filename = RemoveLeftCrocodile(prompt);
        printf("filename = %s\n",prompt);

        RemoveFileName(prompt,filename);
        printf("stripped = %s\n",prompt);
    }
    int words = countWords(prompt);
    printf("Words = %d\n",words);
    char* command = getCommand(prompt);

    char** args = smallerTokenizer(prompt, words);

    // printf("Command = %s\n Args = ",command);
    // for(int i = 0; i < words + 1; i++){
    //     printf("%s, ",args[i]);
    // }
    printf("\n");

    // for(int i = 0; i < words + 1; i++)
    //     free(args[i]);


    if(!fork()){
        execvp(command,args);
    }
    else{
        wait(NULL);
    }
    // free(command);
    // free(args);

}

// > input.txt sort -r
// sort > input.txt -r
// sort -r < input.txt
