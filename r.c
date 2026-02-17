#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void main(){
	int x = 0;
	if(!fork()){
		x += 5;
		if(!fork())
			x+=10;
	}
	else{
		wait(NULL);
		x += 20;
		fork();

	}

	fork();
	printf("%d\n",x);


}
