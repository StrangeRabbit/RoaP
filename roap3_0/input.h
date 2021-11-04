#include "structures.h"

#ifndef __INPUT__
#define __INPUT__

void program_caller_checker(int argc, char **argv);
void jump_map(FILE *fp, int wall_number);
char *get_filename(int argc, char **argv);
FILE *open_file(char *filename);
bool file_checker(char *filename);
void get_header(FILE *fp, mode *game_mode, int *i1, int *j1, int *i2, int *j2, int *wall_number);
void get_header_final(FILE *fp, int *i, int *j, int *wall_number);
cell *build_board(FILE *fp, int row, int column, int wall_number);
cell *init_matrix(int row, int column);
int get_index(int column, int i, int j);

#endif