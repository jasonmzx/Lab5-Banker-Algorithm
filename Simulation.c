
#include "core/Banker.h"

pthread_mutex_t mutex;

void *customer_thread(void *arg){

}

int main(int argc, char** argv){
    if(argc < 4 || argc > 4){
        printf("Must have 3 args to represent resources to allocate\n");
        exit(1);
    }
    available[0] = atoi(argv[1]);
    available[1] = atoi(argv[2]);
    available[2] = atoi(argv[3]);

    //init need with original maximum and allocation values
    //inital allocation value can be changed based on simulation needs
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    pthread_mutex_init(&mutex, NULL);

}