#include "structures.h"
#include "stdbool.h"

#ifndef __GAME_MODE__
#define __GAME_MODE__

bool is_cell_in_board(int row, int column, int i, int j);
void mode_A1(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A2(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A3(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A4(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A5(FILE *fp, cell *matrix, int i, int j, int row, int column);
void mode_A6(FILE *fp, cell *matrix, int i1, int j1, int i2, int j2, int row, int column);
int same_root(cell *matrix, int row, int column, int i1, int j1, int i2, int j2);
void CWQU(cell *matrix, int row, int column);
bool is_white(cell position);
bool is_grey(cell position);
bool is_black(cell position);
bool treasure_is_adjacent_to_src(int i1, int j1);

#endif