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
                return -1;
            }
        }else{
            return -1;
        }
    }
    return 0;
}

int release_resources(int customer_num, int release[]){
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
            if(finished[j]==false && need[i][j] <= work[j]){
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

    return safe;
}