#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<time.h>
#include<stdbool.h>
#define STRINGSIZE 128
bool GhostExistsInRoom(char* room){
    //convert string to lowercase
    for(int i = 0; room[i] != '\0'; i++){
	if(room[i] >= 'A' || room[i] <= 'Z')
		room[i] +=32;
    }
    char ghost[] = "ghost";
    return strstr(room,ghost);
    //strstr finds substring
}

void AssignRoomsToInvestigators(char** lines, int size){
    int* assigned = malloc(sizeof(int) * size);
    int* child_pids = malloc(sizeof(int) * size);
    FILE* log = fopen("log.txt","w");

    int asg_ind = 0;
    int parent = 0;
    srandom(time(NULL));
    for(int i = 0; i < size; i++){
        int room_no = 0;
        bool isRepeated = false;
        //here we find a random number that hasn't already been assigned.
        do{
            isRepeated = false;
            room_no = random() % size;
            for(int j = 0; j < asg_ind; j++){
                if (room_no == assigned[j]){
                    isRepeated = true;
                }
            }
        }while(isRepeated);
        //here we actually assign the room
        int pid = fork();

        if(pid == 0){
            bool is_ghost_in_this_room = GhostExistsInRoom(lines[room_no]);
            if(is_ghost_in_this_room == true){
                int roll = random() % 10;
                if(roll > 3){
                    fprintf(log,"Investigator %d found a ghost in room %d and escaped.\n",i + 1, room_no + 1);
                    exit(EXIT_SUCCESS);
                }
                else{
                    exit(EXIT_FAILURE);
                }
            }
            else{
                //there's no ghost in this room, so the investigator exists successfully.
                exit(EXIT_SUCCESS);
            }

        }
        //here we update the assigned list
        assigned[asg_ind++] = room_no;

    }

    int status = 0;

    printf("Summary:\n");

    int survivors = 0;
    for(int i = 0; i < size; i++){
        wait(&status);
        if(status == 0){
            printf("Investigator %d escaped\n", i + 1);
            survivors++;
        }
        else{
            printf("Investigator %d taken\n",i + 1);
        }
    }

    printf("%d survived of %d\n",survivors,size);


    free(assigned);
    free(child_pids);
}




void main(){
    FILE* file;
    char buffer[STRINGSIZE];
    char filename[] = "house.txt";
    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error. File not found\n");
        return;
    }

    int initial_size = 13;
    char** lines = (char**)malloc(sizeof(char*) * initial_size);
    int size = 0;
    while(fgets(buffer,sizeof(buffer),file) != NULL){
        lines[size] = malloc(strlen(buffer) + 1);
        strcpy(lines[size++],buffer);
        buffer[0] = '\0';
    }

    AssignRoomsToInvestigators(lines,size);


    for(int i = 0; i < size ;i++){
        free(lines[i]);
    }
    free(lines);


}
