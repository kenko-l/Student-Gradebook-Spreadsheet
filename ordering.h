#ifndef ORDERING_H
#define ORDERING_H

#include "spreadsheet.h"

int compareStudents(const void *a, const void *b);
int compareLastName(const void *a, const void *b);
int compareExam(const void *a, const void *b);
int compareTotal(const void *a, const void *b);

#endif // ORDERING_H