#include<stdio.h>
#include<unistd.h>

void main(){
	int pid = fork();
	int n = -1;
	if(pid == 0)
		n = 0;
	else
		n = 6;

	for(int i = n; i < n + 5; i++){
		printf("%d",i);
	}


}
