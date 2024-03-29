#include <time.h> 
#include <unistd.h>

#include "core/Banker.h"

pthread_mutex_t mutex;

void *customer_thread(void *arg){
    int customer_num = *(int *)arg;
    int rand_request[NUMBER_OF_RESOURCES];
    int rand_release[NUMBER_OF_RESOURCES];
    while(1){
        sleep(rand() % 5); //FOR TESTING
        printf("\n****************************************************\n");
        pthread_mutex_lock(&mutex);

        //generate random request
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
            rand_request[i] = rand() % (maximum[customer_num][i] + 1);
        }
        printf("Customer %d is Requesting: %d, %d, %d resources\n",customer_num,rand_request[0],rand_request[1],rand_request[2]);
        int req = request_resources(customer_num,rand_request);
        if(req == -1){
            printf("Request Failed\n");
            //pthread_mutex_unlock(&mutex); 
            //continue;
            //goto Release;
        }
        
        if(!is_safe_state()){
            printf("Restoring State\n");
            release_resources(customer_num,rand_request);
            pthread_mutex_unlock(&mutex); 
            continue;
        }  
        printf("Customer %d Using %d %d %d resources\n",customer_num,allocation[customer_num][0],allocation[customer_num][1],allocation[customer_num][2]);
    //Release:
        //generate random release
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
            rand_release[i] = rand() % (allocation[customer_num][i] + 1);
        }

        printf("Customer %d is Releasing: %d, %d, %d resources\n",customer_num,rand_release[0],rand_release[1],rand_release[2]);
        int rel = release_resources(customer_num,rand_release);
        if(rel == -1){
            printf("Release Failed\n");
        }
        pthread_mutex_unlock(&mutex); 
        //sleep(rand() % 5); //FOR TESTING
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv){

    pthread_t threads[NUMBER_OF_CUSTOMERS];
    int thread_args[NUMBER_OF_CUSTOMERS];
    srand(time(0)); 

    if(argc < 4 || argc > 4){
        printf("Must have 3 args to represent resources to allocate\n");
        exit(1);
    }

    //Work (Available)

    available[0] = atoi(argv[1]);
    available[1] = atoi(argv[2]);
    available[2] = atoi(argv[3]);

    //init need with original maximum and allocation values
    //inital allocation value can be changed based on simulation needs

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {  // Need = Max - Allocation
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        thread_args[i] = i; 
        if (pthread_create(&threads[i], NULL, customer_thread, &thread_args[i]) != 0) {
            printf("Error creating thread: %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread: %d\n", i);
            exit(1);
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}