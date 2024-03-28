#include "Banker.h"

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

int request_resources(int customer_num, int request[]){
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        if(request[i] <= need[customer_num][i]){
            if(request[i] <= available[i]){
                available[i] = available[i] - request[i];
                allocation[customer_num][i] = allocation[customer_num][i] + request[i];
                need[customer_num][i] = need[customer_num][i] - request[i];
            }else{
                printf("Resource Request for Customer %d can not be fulfilled\n",customer_num);
                return -1;
            }
        }else{
            printf("Error, Customer %d is requesting more resources than it needs\n",customer_num);
            return -1;
        }
    }
    printf("Resource Request for Customer %d can be fulfilled sucessfully\n",customer_num);
    return 0;
}

int release_resources(int customer_num, int release[]){
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (release[i] > allocation[customer_num][i]) {
            printf("Error, Customer %d is releasing more resources than it has allocated\n", customer_num);
            return -1;
        }
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];  
    }

    printf("Resource release for Customer %d fulfilled successfully\n", customer_num);
    return 0;
}

bool is_safe_state(){

    bool finished[NUMBER_OF_CUSTOMERS] = {false};
    int work[NUMBER_OF_RESOURCES];

    for(int i = 0;i < NUMBER_OF_RESOURCES; i++){
        work[i] = available[i];
    }
    for(int i = 0;i< NUMBER_OF_CUSTOMERS; i++){
        for(int j = 0;j < NUMBER_OF_RESOURCES; j++){
            if(finished[i]==false && need[i][j] <= work[j]){
                work[j] = work[j] + allocation[i][j];
                finished[i] = true;
            }

        }
    }

    bool safe = true;
    for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
        if(finished[i] ==  false){
            safe = false;
            break;
        }
    }
    printf("Current state is safe?: %s\n", safe ? "True" : "False");
    return safe;
}