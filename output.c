#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

/**
 * @brief Creates a pointer to a file 
 * @param filename name of the file to be created 
 * @return Pointer to a File with the expected name
 */
FILE *create_file(char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        exit(0);
    return fp;
}

/**
 * @brief modifies a file name to correspont to the expected one to an output file 
 * @param argc argument count
 * @param argv argument vector
 * @param output_filename pointer to a string that will be changed 
 * @return VOID
 */
void create_filename(int argc, char **argv, char *output_filename)
{
    strcpy(output_filename, get_filename(argc, argv));
    int len = strlen(output_filename);
    output_filename[len - 3] = 's';
    output_filename[len - 2] = 'o';
    output_filename[len - 1] = 'l';
    output_filename[len] = '1';
    output_filename[len + 1] = '\0';
    return;
}
