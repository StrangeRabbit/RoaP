#include "structures.h"

#ifndef __GAME_MODE__
#define __GAME_MODE__

BOOL is_cell_in_board(int row, int column, int i, int j);
void mode_A1(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A2(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A3(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A4(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A5(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A6(FILE *fp, cell *matrix, int i1, int j1, int i2, int j2, int row, int column);
int same_root(cell *matrix, int row, int column, int i1, int j1, int i2, int j2);
void CWQU(cell *matrix, int row, int column);
BOOL is_white(cell position);
BOOL is_grey(cell position);
BOOL is_black(cell position);

#endif