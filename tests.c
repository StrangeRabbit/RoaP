#include <stdio.h>
#include <stdlib.h>

int index1(int column, int i, int j);
int index2(int row, int i, int j);

int main(int argc, char** argv)
{
    char *aux = argv[1] + 1;
    int i = atoi(aux);
    printf("%d", i);
    return 0;
}

int index1(int column, int i, int j)
{
    return i * column + j;
}

int index2(int row, int i, int j)
{
    return i + row * j;
}