#include "structures.h"

#ifndef __OUTPUT__
#define __OUTPUT__

FILE *create_file(char *filename);
void create_filename(int argc, char **argv, char *output_filename);
void create_filename_final(int argc, char **argv, char *output_filename);


#endif