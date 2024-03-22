#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} };

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} };



int main(int argc, char** argv){
    if(argc < 4 || argc > 4){
        printf("Must have 3 args to represent resources to allocate\n");
        exit(1);
    }
    available[0] = atoi(argv[1]);
    available[1] = atoi(argv[2]);
    available[2] = atoi(argv[3]);

    //printf("%d | %d | %d\n",available[0],available[1],available[2]);
}