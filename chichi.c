#include <stdio.h>
#include <unistd.h>
int main() {
    int a = 9;
   
    printf("Hello!");
    int pid = fork();
   
    printf("I am %d \n", pid);

    if(pid == 0)
    {
        printf("Sum of 3+6 = %d\n", a);
        int pid1 = fork();
    }
    else
    {
        a =16;
        printf("I love FASt. a = %d\n", a);
    }
    return 0;
}
