#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

FILE *create_file(char *filename)
{
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) exit(CREATE_FILE_ERROR);
    return fp;
}

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
