#include <stdio.h>
#include <stdlib.h>

int main() {
    int *dynamic_variable;
    dynamic_variable = (int *)malloc(sizeof(int));  // Allocate memory
    if (dynamic_variable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    *dynamic_variable = 10;  // Assign value
    printf("Dynamic variable: %d\n", *dynamic_variable);
    free(dynamic_variable);  // Free allocated memory
    return 0;
}
