#include "data.h"

int readStudentsFromFile(const char *filename, Student *students)
{
    FILE *pF = fopen(filename, "r");
    if (pF == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    char buffer[255];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), pF) != NULL && count < MAX_STUDENTS)
    {
        char *token = strtok(buffer, "|");
        int index = 0;

        while (token != NULL)
        {
            switch (index)
            {
            case 0:
                strncpy(students[count].id, token, sizeof(students[count].id) - 1);
                students[count].id[sizeof(students[count].id) - 1] = '\0';
                break;
            case 1:
                strncpy(students[count].lastName, token, sizeof(students[count].lastName) - 1);
                students[count].lastName[sizeof(students[count].lastName) - 1] = '\0';
                break;
            case 2:
                strncpy(students[count].firstName, token, sizeof(students[count].firstName) - 1);
                students[count].firstName[sizeof(students[count].firstName) - 1] = '\0';
                break;
            case 3:
                students[count].a1 = atoi(token);
                break;
            case 4:
                students[count].a2 = atoi(token);
                break;
            case 5:
                students[count].a3 = atoi(token);
                break;
            case 6:
                students[count].midterm = atoi(token);
                break;
            case 7:
                students[count].final = atoi(token);
                break;
            }
            token = strtok(NULL, "|");
            index++;
        }
        count++;
    }

    fclose(pF);
    return count;
}