// C program to generate 10 random number using rand()
// function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int i = 0;
    // Loop through 10 times
    srandom(time(NULL));
    for (; i < 10; i++) {
        // Generate a random number using the rand()
        // function

        int value = random();

        // Print the generated random value
        printf("%d ", value % 12 + 1);
    }

    return 0;
}