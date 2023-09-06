#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct student
{
    int studentID;
    double percentMark;
} student;

student *readStudentDataFromFile(const char *filename, int *num_students);
double calculate_median(double *percentMarks, int num_students);
int compare_by_studentID(const void *a, const void *b);
char *grade(double percentMark);
void printStudentData(const student *students, int num_students);
void printAvgMedian(int num_students, const student *students);

#endif
