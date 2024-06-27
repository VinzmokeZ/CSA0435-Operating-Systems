#include <stdio.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);
int is_safe_state();

int main() {
    // Initialize available resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        printf("Enter available instances of resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources each customer can request
    printf("Enter maximum resources each customer can request:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        printf("Customer %d: ", i + 1);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    // Initialize allocated resources for each customer
    printf("Enter allocated resources for each customer:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        printf("Customer %d: ", i + 1);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }

    // Simulate resource requests
    int request[NUMBER_OF_RESOURCES] = {0};
    printf("Enter customer number and resource request (e.g., '1 0 1 0' for customer 1 requesting 1 unit of resource 1 and 1 unit of resource 3):\n");
    int customer_num;
    while (scanf("%d", &customer_num) != EOF) {
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
            scanf("%d", &request[i]);
        }

        if (request_resources(customer_num - 1, request))
            printf("Request granted.\n");
        else
            printf("Request denied.\n");

        printf("Enter customer number and resource request:\n");
    }

    return 0;
}

int request_resources(int customer_num, int request[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        if (request[i] > need[customer_num][i] || request[i] > available[i]) {
            return 0;
        }
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }

    if (!is_safe_state()) {
        // If granting the request leads to an unsafe state, revert changes
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }
        return 0;
    }

    return 1;
}

void release_resources(int customer_num, int release[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
}

int is_safe_state() {
    int work[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS] = {0};

    // Initialize work with available resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        work[i] = available[i];
    }

    // Check if a customer can finish
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        if (!finish[i]) {
            int can_finish = 1;
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
                if (need[i][j] > work[j]) {
                    can_finish = 0;
                    break;
                }
            }
            if (can_finish) {
                // Simulate finish and release of resources
                finish[i] = 1;
                for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
                    work[j] += allocation[i][j];
                }
                i = -1; // Restart loop to check if more can finish
            }
        }
    }

    // If all customers can finish, return safe state
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        if (!finish[i]) {
            return 0;
        }
    }
    return 1;
}

