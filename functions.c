#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIALCAPACITY 100
/**
 * This function reads data from file and returns
 * an array of student type containing structs of students
 */
student *readStudentDataFromFile(const char *filename, int *num_students)
{
    /**
     * Declare Variables
     * element_size - The size of each student struct
     * max_students - maximum number of structs in array(100)
     * students - array of student structs
     *
     */
    size_t element_size;
    int max_students;
    student *students;
    size_t elements_read;
    /**
     * Open the binary file
     */
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File not found: %s\n", filename);
        return NULL;
    }

    /**
     * Read data from the file using fread()
     */

    element_size = sizeof(student);
    max_students = INITIALCAPACITY;

    students = (student *)malloc(max_students * sizeof(student));
    if (students == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    while ((elements_read = fread(&students[*num_students], element_size, 1, file)) > 0)
    {
        (*num_students)++;

        /**
         * Dynamically Increase the size of the students
         * array using realloc if it is full
         */
        if (*num_students >= max_students)
        {
            max_students *= 2;
            students = (student *)realloc(students, max_students * sizeof(student));
            if (students == NULL)
            {
                printf("Memory reallocation failed.\n");
                fclose(file);
                return NULL;
            }
        }
    }

    /**
     * Close the file and return students array
     */
    fclose(file);
    return students;
}

/**
 * This function calculates and returns median
 */
double calculate_median(double *percentMarks, int num_students)
{
    /**
     * Declare Variables
     * i & j - for loop iteration
     * middle - for middle of array to calculate median
     * temp - to temp hold array element in sorting
     */
    int i, j, middle;
    double temp;

    /**
     * sort the array in ascending order using bubble sort
     */

    for (i = 0; i < num_students - 1; i++)
    {
        for (j = 0; j < num_students - i - 1; j++)
        {
            if (percentMarks[j] > percentMarks[j + 1])
            {
                temp = percentMarks[j];
                percentMarks[j] = percentMarks[j + 1];
                percentMarks[j + 1] = temp;
            }
        }
    }

    /**
     * Calculate the median based on the number of student structs in students array
     */
    if (num_students % 2 == 0)
    {
        middle = num_students / 2;
        return (percentMarks[middle - 1] + percentMarks[middle]) / 2.0;
    }
    else
    {
        middle = num_students / 2;
        return percentMarks[middle];
    }
}

/**
 * qsort function to sort the array of structs based on studentID
 */
int compare_by_studentID(const void *a, const void *b)
{
    const student *studentA = (const student *)a;
    const student *studentB = (const student *)b;

    if (studentA->studentID < studentB->studentID)
        return -1;
    else if (studentA->studentID > studentB->studentID)
        return 1;
    else
        return 0;
}

/**
 * Function to convert double student grade into char type
 */
char *grade(double percentMark)
{
    char *convertedGrade;

    if (percentMark >= 90.0 && percentMark <= 100.0)
    {
        convertedGrade = "A+";
    }
    else if (percentMark >= 85.0)
    {
        convertedGrade = "A";
    }
    else if (percentMark >= 80.0)
    {
        convertedGrade = "A-";
    }
    else if (percentMark >= 77.0)
    {
        convertedGrade = "B+";
    }
    else if (percentMark >= 73.0)
    {
        convertedGrade = "B";
    }
    else if (percentMark >= 70.0)
    {
        convertedGrade = "B-";
    }
    else if (percentMark >= 67.0)
    {
        convertedGrade = "C+";
    }
    else if (percentMark >= 63.0)
    {
        convertedGrade = "C";
    }
    else if (percentMark >= 60.0)
    {
        convertedGrade = "C-";
    }
    else if (percentMark >= 57.0)
    {
        convertedGrade = "D+";
    }
    else if (percentMark >= 53.0)
    {
        convertedGrade = "D";
    }
    else if (percentMark >= 50.0)
    {
        convertedGrade = "D-";
    }
    else
    {
        convertedGrade = "F";
    }
    return convertedGrade;
}

/**
 * this function prints student struct Data
 */
void printStudentData(const student *students, int num_students)
{
    /**
     * Declare Variables
     * i - loop iterator
     * studentGrade - pointer to converted grade in char
     */
    int i;
    char *studentGrade;
    printf("\nStudent data printed in ascending order according to student ID: \n\n");

    for (i = 0; i < num_students; i++)
    {
        /*
         * Call grade function to calculate the grade based on student marks
         */
        studentGrade = grade(students[i].percentMark);
        printf("Student ID: %8d, Percent Mark: %6.2f, Letter Grade: %s\n", students[i].studentID, students[i].percentMark, studentGrade);
    }
}

/**
 * This function prints average and median of all data
 */
void printAvgMedian(int num_students, const student *students)
{

    /**
     * Initialize variables
     * i - loop iterator
     * totalPercentMark - total marks to calculate average
     * medianPercenMark - to store value from caclculate_median
     * *percentMarks - array of student marks
     */
    int i;
    double totalPercentMark;
    double averagePercentMark;
    double medianPercentMark;
    double *percentMarks;

    totalPercentMark = 0.0;
    percentMarks = (double *)malloc(num_students * sizeof(double));
    if (percentMarks == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    for (i = 0; i < num_students; i++)
    {
        totalPercentMark += students[i].percentMark;
        percentMarks[i] = students[i].percentMark;
    }

    /**
     * Calculate average and median numeric grades
     */
    averagePercentMark = totalPercentMark / num_students;
    medianPercentMark = calculate_median(percentMarks, num_students);

    printf("\nMedian Percent Mark: %.2f\n", medianPercentMark);
    printf("Average Percent Mark: %.2f\n", averagePercentMark);

    /**
     * Free dynamically allocated memory
     */
    free(percentMarks);
}
