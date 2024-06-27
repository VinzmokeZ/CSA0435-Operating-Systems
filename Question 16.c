#include <stdio.h>
#include <stdlib.h>

// Structure to represent an employee
struct Employee {
    int id;
    char name[50];
    float salary;
};

// Function to add employee record to the file
void addEmployee(FILE *file) {
    struct Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee added successfully\n");
}

// Function to display employee record from the file
void displayEmployee(FILE *file) {
    struct Employee emp;
    int id;

    printf("Enter employee ID to display: ");
    scanf("%d", &id);

    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    if (emp.id != 0) {
        printf("Employee ID: %d\n", emp.id);
        printf("Employee Name: %s\n", emp.name);
        printf("Employee Salary: %.2f\n", emp.salary);
    } else {
        printf("Employee not found\n");
    }
}

int main() {
    FILE *file;
    int choice;

    // Open the file in binary mode for read/write
    file = fopen("employees.dat", "rb+");

    // Check if the file exists
    if (file == NULL) {
        // If the file does not exist, create it
        file = fopen("employees.dat", "wb+");
        if (file == NULL) {
            printf("Error creating/opening file\n");
            exit(1);
        }
    }

    do {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayEmployee(file);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    fclose(file);  // Close the file
    return 0;
}
