#include "ordering.h"
#include "calc.h"

int compareStudents(const void *a, const void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return atoi(studentA->id) - atoi(studentB->id);
}

int compareLastName(const void *a, const void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->lastName, studentB->lastName);
}

int compareExam(const void *a, const void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return studentB->final - studentA->final;
}

int compareTotal(const void *a, const void *b)
{
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    float totalA = calculateTotal(studentA);
    float totalB = calculateTotal(studentB);
    if (totalA < totalB)
        return 1;
    if (totalA > totalB)
        return -1;
    return 0;
}