#include "calc.h"
#include "ordering.h"

void displaySpreadsheet(Student *students, int count)
{
    clearScreen();
    printf("COMP 348 GRADE SHEET\n\n");
    printf("%-5s %-10s %-10s %4s %4s %4s %7s %5s %7s %5s\n", "ID", "Last", "First", "A1", "A2", "A3", "Midterm", "Final", "Total", "Grade");
    printf("%-5s %-10s %-10s %4s %4s %4s %7s %5s %7s %5s\n", "--", "----", "-----", "--", "--", "--", "-------", "-----", "-----", "-----");

    switch (currentSortOption)
    {
    case 1:
        qsort(students, count, sizeof(Student), compareStudents);
        break;
    case 2:
        qsort(students, count, sizeof(Student), compareLastName);
        break;
    case 3:
        qsort(students, count, sizeof(Student), compareExam);
        break;
    case 4:
        qsort(students, count, sizeof(Student), compareTotal);
        break;
    }

    gradeACount = gradeBCount = gradeCCount = gradeDCount = gradeFCount = 0;

    for (int i = 0; i < count; i++)
    {
        float total = calculateTotal(&students[i]);
        char grade = calculateGrade(total);

        printf("%-5s %-10s %-10s %4d %4d %4d %7d %5d %7.2f %5c\n",
               students[i].id, students[i].lastName, students[i].firstName,
               students[i].a1, students[i].a2, students[i].a3,
               students[i].midterm, students[i].final, total, grade);

        switch (grade)
        {
        case 'A':
            gradeACount++;
            break;
        case 'B':
            gradeBCount++;
            break;
        case 'C':
            gradeCCount++;
            break;
        case 'D':
            gradeDCount++;
            break;
        case 'F':
            gradeFCount++;
            break;
        }
    }

    printf("\n");
    waitForContinue();
}

void displayHistogram()
{
    clearScreen();
    printf("COMP 348 GRADE SHEET\n\n");
    printf("Grade Distribution:\n\n");

    printf("A: ");
    for (int i = 0; i < gradeACount; i++)
        printf("*");
    printf("\n");
    printf("B: ");
    for (int i = 0; i < gradeBCount; i++)
        printf("*");
    printf("\n");
    printf("C: ");
    for (int i = 0; i < gradeCCount; i++)
        printf("*");
    printf("\n");
    printf("D: ");
    for (int i = 0; i < gradeDCount; i++)
        printf("*");
    printf("\n");
    printf("F: ");
    for (int i = 0; i < gradeFCount; i++)
        printf("*");
    printf("\n");

    printf("\n");
    waitForContinue();
}

void setSortColumn()
{
    clearScreen();
    printf("Column Options\n");
    printf("--------------\n");
    printf("1. Student ID\n");
    printf("2. Last Name\n");
    printf("3. Exam\n");
    printf("4. Total\n\n");

    printf("Sort Column: ");
    scanf("%d", &currentSortOption);

    if (currentSortOption < 1 || currentSortOption > 4)
    {
        printf("Invalid option. Setting to default (Student ID).\n");
        currentSortOption = 1;
    }
    else
    {
        printf("\nSort Column updated\n\n");
    }

    waitForContinue();
}

void updateLastName(Student *students, int count)
{
    char id[5];
    char newLastName[10];

    clearScreen();
    displaySpreadsheet(students, count);

    printf("\nEnter Student ID: ");
    scanf("%s", id);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            printf("Enter updated Last Name: ");
            scanf("%s", newLastName);
            strncpy(students[i].lastName, newLastName, sizeof(students[i].lastName) - 1);
            students[i].lastName[sizeof(students[i].lastName) - 1] = '\0';
            printf("Last name updated\n");
            waitForContinue();
            return;
        }
    }

    printf("Student ID not found.\n");
    waitForContinue();
}

void updateExamGrade(Student *students, int count)
{
    char id[5];
    int newGrade;

    clearScreen();
    displaySpreadsheet(students, count);

    printf("\nEnter Student ID: ");
    scanf("%s", id);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            printf("Enter updated Final Grade: ");
            scanf("%d", &newGrade);
            if (newGrade >= 0 && newGrade <= 40)
            {
                students[i].final = newGrade;
                printf("Final grade updated\n");
            }
            else
            {
                printf("Invalid grade. Must be between 0 and 40.\n");
            }
            waitForContinue();
            return;
        }
    }

    printf("Student ID not found.\n");
    waitForContinue();
}

void adjustGradeMapping()
{
    clearScreen();
    printf("Current Mapping:\n");
    printf("A: >= %d\n", gradeMapping[0]);
    printf("B: >= %d\n", gradeMapping[1]);
    printf("C: >= %d\n", gradeMapping[2]);
    printf("D: >= %d\n", gradeMapping[3]);
    printf("F:  < %d\n\n", gradeMapping[3]);

    printf("Enter new A baseline: ");
    scanf("%d", &gradeMapping[0]);
    printf("Enter new B baseline: ");
    scanf("%d", &gradeMapping[1]);
    printf("Enter new C baseline: ");
    scanf("%d", &gradeMapping[2]);
    printf("Enter new D baseline: ");
    scanf("%d", &gradeMapping[3]);

    for (int i = 0; i < 3; i++)
    {
        if (gradeMapping[i] <= gradeMapping[i + 1])
        {
            printf("Error: Each baseline must be greater than the next.\n");
            printf("Reverting to default mapping.\n");
            gradeMapping[0] = 80;
            gradeMapping[1] = 70;
            gradeMapping[2] = 60;
            gradeMapping[3] = 50;
            break;
        }
    }

    printf("\nNew Mapping:\n");
    printf("A: >= %d\n", gradeMapping[0]);
    printf("B: >= %d\n", gradeMapping[1]);
    printf("C: >= %d\n", gradeMapping[2]);
    printf("D: >= %d\n", gradeMapping[3]);
    printf("F:  < %d\n\n", gradeMapping[3]);

    waitForContinue();
}

void deleteStudent(Student *students, int *count)
{
    char id[5];

    clearScreen();
    displaySpreadsheet(students, *count);

    printf("\nEnter Student ID to delete: ");
    scanf("%s", id);

    for (int i = 0; i < *count; i++)
    {
        if (strcmp(students[i].id, id) == 0)
        {
            for (int j = i; j < *count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student successfully deleted\n");
            waitForContinue();
            return;
        }
    }

    printf("Student ID not  found.\n");
    waitForContinue();
}

float calculateTotal(Student *student)
{
    return ((float)student->a1 / 40) * 100 * 0.1 +
           ((float)student->a2 / 40) * 100 * 0.1 +
           ((float)student->a3 / 40) * 100 * 0.1 +
           ((float)student->midterm / 25) * 100 * 0.3 +
           ((float)student->final / 40) * 100 * 0.4;
}

char calculateGrade(float total)
{
    if (total >= gradeMapping[0])
        return 'A';
    if (total >= gradeMapping[1])
        return 'B';
    if (total >= gradeMapping[2])
        return 'C';
    if (total >= gradeMapping[3])
        return 'D';
    return 'F';
}

void waitForContinue()
{
    while (1)
    {
        printf("Press 'c' or 'C' to continue: ");
        char input;
        scanf(" %c", &input);
        if (input == 'c' || input == 'C')
        {
            clearScreen();
            break;
        }
        else
        {
            printf("Invalid input. ");
        }
    }
}