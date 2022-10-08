#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "test.txt"
#define MAX_FIELD_SIZE 20
#define BUFFER_SIZE 100

struct Worker {
    int id;
    char name[MAX_FIELD_SIZE];
    char department[MAX_FIELD_SIZE];
    int salary;
};

struct WorkerDTO {
    char name[MAX_FIELD_SIZE];
    char department[MAX_FIELD_SIZE];
    int salary;
};

void addWorker(const char *filename, const struct Worker *worker) {
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening file %s", filename);
        exit(1);
    }

    fprintf(file, "%d %s %s %d\n", worker->id, worker->name, worker->department, worker->salary);
    fclose(file);
}

void deleteWorker(const char *filename, const int id) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("Error opening file %s", filename);
        exit(1);
    }

    char line[BUFFER_SIZE];

    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        int position = 0;
        while (line[position] != ' ') {
            position++;
        }

        char idString[position + 1];
        strncpy(idString, line, position);

        if (strtol(idString, NULL, 10) != id) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

void editWorker(const char *filename, const int id, const struct WorkerDTO *worker) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("Error opening file %s", filename);
        exit(1);
    }

    char line[BUFFER_SIZE];

    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        int position = 0;
        while (line[position] != ' ') {
            position++;
        }

        char idString[position + 1];
        strncpy(idString, line, position);

        if (strtol(idString, NULL, 10) != id) {
            fprintf(temp, "%s", line);
        } else {
            fprintf(temp, "%d %s %s %d\n", id, worker->name, worker->department, worker->salary);
        }
    }

    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

int getDepartmentAvgSalary(const char *filename, const char *department) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s", filename);
        exit(1);
    }

    int totalSalary = 0;
    int count = 0;
    char line[BUFFER_SIZE];

    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        char *token = strtok(line, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        if (strcmp(token, department) == 0) {
            token = strtok(NULL, " ");
            totalSalary += strtol(token, NULL, 10);
            count++;
        }
    }

    fclose(file);
    return totalSalary / count;
}

int main() {
    // implement
    return 0;
}
