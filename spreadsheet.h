#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

typedef struct
{
    char id[5];
    char lastName[10];
    char firstName[10];
    int a1, a2, a3, midterm, final;
} Student;

void callMenu();
void clearScreen();

extern int currentSortOption;
extern int gradeACount, gradeBCount, gradeCCount, gradeDCount, gradeFCount;
extern int gradeMapping[4];

#endif // SPREADSHEET_H