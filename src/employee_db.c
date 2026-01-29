#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    int id;
    char name[50];
    char dept[30];
    float salary;
    char phone[15];
};

void addEmployee();
void viewEmployee();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

int main() {
    int choice;

    while (1) {
        printf("\n=================================\n");
        printf(" EMPLOYEE DATABASE MANAGEMENT\n");
        printf("=================================\n");
        printf("1. Add Employee\n");
        printf("2. View All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: viewEmployee(); break;
        case 3: searchEmployee(); break;
        case 4: updateEmployee(); break;
        case 5: deleteEmployee(); break;
        case 6:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

void addEmployee() {
    struct employee e;
    FILE *fp = fopen("employee.dat", "ab");

    printf("Enter ID: ");
    scanf("%d", &e.id);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Department: ");
    scanf("%s", e.dept);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);
    printf("Enter Phone: ");
    scanf("%s", e.phone);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("Employee added successfully!\n");
}

void viewEmployee() {
    struct employee e;
    FILE *fp = fopen("employee.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nID\tName\tDept\tSalary\tPhone\n");
    while (fread(&e, sizeof(e), 1, fp)) {
        printf("%d\t%s\t%s\t%.2f\t%s\n",
               e.id, e.name, e.dept, e.salary, e.phone);
    }
    fclose(fp);
}

void searchEmployee() {
    struct employee e;
    int id, found = 0;
    FILE *fp = fopen("employee.dat", "rb");

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {
            printf("Record Found!\n");
            printf("Name: %s\nDept: %s\nSalary: %.2f\nPhone: %s\n",
                   e.name, e.dept, e.salary, e.phone);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");

    fclose(fp);
}

void updateEmployee() {
    struct employee e;
    int id, found = 0;
    FILE *fp = fopen("employee.dat", "rb+");

    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id == id) {
            printf("Enter new Name: ");
            scanf("%s", e.name);
            printf("Enter new Department: ");
            scanf("%s", e.dept);
            printf("Enter new Salary: ");
            scanf("%f", &e.salary);
            printf("Enter new Phone: ");
            scanf("%s", e.phone);

            fseek(fp, -sizeof(e), SEEK_CUR);
            fwrite(&e, sizeof(e), 1, fp);
            found = 1;
            printf("Employee updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");

    fclose(fp);
}

void deleteEmployee() {
    struct employee e;
    int id, found = 0;
    FILE *fp = fopen("employee.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.id != id)
            fwrite(&e, sizeof(e), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    if (found)
        printf("Employee deleted successfully!\n");
    else
        printf("Employee not found!\n");
}
