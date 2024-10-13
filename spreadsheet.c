#include "spreadsheet.h"
#include "ordering.h"
#include "data.h"
#include "calc.h"

int currentSortOption = 1;
int gradeACount = 0, gradeBCount = 0, gradeCCount = 0, gradeDCount = 0, gradeFCount = 0;
int gradeMapping[4] = {80, 70, 60, 50};

int main()
{
    Student students[MAX_STUDENTS];
    int count = readStudentsFromFile("students.txt", students);
    int option = 0;

    while (option != 8)
    {
        callMenu();
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            displaySpreadsheet(students, count);
            break;
        case 2:
            displayHistogram();
            break;
        case 3:
            setSortColumn();
            break;
        case 4:
            updateLastName(students, count);
            break;
        case 5:
            updateExamGrade(students, count);
            break;
        case 6:
            adjustGradeMapping();
            break;
        case 7:
            deleteStudent(students, &count);
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid selection. Please try again.\n");
            break;
        }
    }

    return 0;
}

void callMenu()
{
    printf("Spreadsheet Menu\n");
    printf("----------------\n");
    printf("1. Display Spreadsheet\n");
    printf("2. Display Histogram\n");
    printf("3. Set sort column\n");
    printf("4. Update Last Name\n");
    printf("5. Update Exam Grade\n");
    printf("6. Update Grade Mapping\n");
    printf("7. Delete Student\n");
    printf("8. Exit\n\n");
    printf("Selection: ");
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}