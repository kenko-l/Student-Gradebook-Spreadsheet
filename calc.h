#ifndef CALC_H
#define CALC_H

#include "spreadsheet.h"

void displaySpreadsheet(Student *students, int count);
void displayHistogram();
void setSortColumn();
void updateLastName(Student *students, int count);
void updateExamGrade(Student *students, int count);
void adjustGradeMapping();
void deleteStudent(Student *students, int *count);
float calculateTotal(Student *student);
char calculateGrade(float total);
void waitForContinue();

#endif // CALC_H