#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define INITIALCAPACITY 100

int main(int argc, char *argv[])
{
    /**
     * Declare Variables
     * num_students - the number of students
     * *filename - char pointer to file
     * *students - 1D array of student structs
     */
    int num_students;
    char *filename;
    student *students;
    if (argc != 2)
    {
        printf("Please enter the name of one file to open.\n");
        return 1;
    }
    else
    {
        filename = argv[1];
    }

    num_students = 0;
    students = readStudentDataFromFile(filename, &num_students);
    if (students == NULL)
    {
        return 1;
    }

    /**
     * sort the array using Student ID
     * Print student data by calling these methods
     */
    qsort(students, num_students, sizeof(student), compare_by_studentID);
    printStudentData(students, num_students);
    printAvgMedian(num_students, students);

    /**
     * Free dynamically allocated memory of students array that
     * contains the student structs
     */
    free(students);

    return 0;
}
