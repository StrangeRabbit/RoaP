#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

/**
 * @brief Confirms if konsole input has all it need 
 * @param argc argument count
 * @param argv argument vector
 * @return VOID
 */
void program_caller_checker(int argc, char **argv)
{
    if (argc != 3)
        exit(0);
    if (strlen(argv[1]) != 2)
        exit(0);
    if (argv[1][0] != '-')
        exit(0);
    if (argv[1][1] != 's')
        exit(0);
}

/**
 * @brief If need it jumps a map
 * @param fp pointer to file containing information
 * @param wall_number number of wall a predefined map has
 * @return VOID
 * */
void jump_map(FILE *fp, int wall_number)
{
    unsigned int i;
    int p, q, r;
    for (i = 0; i < wall_number; i++)
    {
        if (fscanf(fp, "%d %d %d", &p, &q, &r) != 3)
            exit(0);
    }
    return;
}

/**
 * @brief Gets file name from argv 
 * @param argc argument count
 * @param argv argument vector
 * @return Pointer to string with the file name
 */
char *get_filename(int argc, char **argv)
{
    if (argc == 2)
        return argv[1];
    else if (argc == 3)
        return argv[2];
    else
        exit(0);
}

/**
 * @brief Opens a file 
 * @param filename Name of the file it will be opened
 * @return Pointer to file
 */
FILE *open_file(char *filename)
{
    if (file_checker(filename) == false)
        exit(0);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        exit(0);
    return fp;
}

/**
 * @brief Check if a file has the correct termination
 * @param filename Name of the file to be tested
 * @return true if file has right termination, false otherwise
 */
bool file_checker(char *filename)
{
    int len = strlen(filename);

    if (strcmp(&filename[len - 4], ".in1") == 0)
        return true;
    else
        return false;
}

/**
 * @brief Gets the header of a map
 * @param fp Pointer to the file containing the map
 * @param game_mode Pointer to a 'mode' variable that will contain the game mode 
 * @param i1 Pointer to a int variable that will cointain line of the first importante cell
 * @param j1 Pointer to a int variable that will cointain column of the first importante cell
 * @param i2 Pointer to a int variable that will cointain line of the second importante cell
 * @param j2 Pointer to a int variable that will cointain column of the seconf importante cell
 * @param wall_number Pointer to a int variable that will cointain the number of wall a map has
 * @return VOID
 */
void get_header(FILE *fp, mode *game_mode, int *i1, int *j1, int *i2, int *j2, int *wall_number)
{
    char mode_aux[3];

    if (fscanf(fp, "%d %d", i1, j1) != 2)
        exit(0);
    if (fscanf(fp, "%s", mode_aux) != 1)
        exit(0);
    (*game_mode) = atoi(&mode_aux[1]);
    if ((*game_mode) == A6)
        if (fscanf(fp, "%d %d", i2, j2) != 2)
            exit(0);
    if (fscanf(fp, "%d", wall_number) != 1)
        exit(0);
    // adapt coordinates to our matrix
    (*i1)--;
    (*j1)--;
    (*i2)--;
    (*j2)--;
    return;
}

void get_header_final(FILE *fp, int *i, int *j, int *wall_number)
{

    if (fscanf(fp, "%d %d", i, j) != 2)
        exit(0);
    
    if (fscanf(fp, "%d", wall_number) != 1)
        exit(0);
    // adapt coordinates to our matrix
    (*i)--;
    (*j)--;
    return;
}

/**
 * @brief Allocates a map, read wall from a file and stores their value in the map
 * @param fp Pointer to a file that has the information
 * @param row number of rows in the map 
 * @param column number of columns in the map
 * @param wall_number number of walls in the map 
 * @return array containing the map
 */
cell *build_board(FILE *fp, int row, int column, int wall_number)
{
    unsigned int p;
    int i, j, wall;

    cell *matrix = init_matrix(row, column);
    for (p = 0; p < wall_number; p++)
    {
        if (fscanf(fp, "%d %d %d", &i, &j, &wall) != 3)
            exit(0);
        matrix[get_index(column, i - 1, j - 1)].wall = wall;
    }
    return matrix;
}

/**
 * @brief allocate and inicializes all cells in board to have the expected values  
 * @param row number of rows in the map
 * @param column number of columns in the a map
 * @return array of cells with all the values iniciatialized
 */
cell *init_matrix(int row, int column)
{
    unsigned int i;

    cell *matrix = (cell *)calloc(row * column, sizeof(cell));

    for (i = 0; i < row * column; i++)
    {
        matrix[i].group = i;
        matrix[i].wall = 0;
        matrix[i].sz = 1;
    }
    return matrix;
}

/**
 * @brief With a matrix algebra return the position index of a array based of rows and column 
 * @param column number of columns in the map
 * @param i line the cell is in 
 * @param j column the cell is in
 * @return int number contain the index to access the array 
 */
int get_index(int column, int i, int j)
{
    return i * column + j;
}
