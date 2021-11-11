#ifndef __AUX__
#define __AUX__

bool white(int V, int *graph);
int I(int idx, int C);
int J(int idx, int C);
int idx(int i, int j, int C);
bool breakable(int *graph, int v, int C, int L);
bool in_board(int v, int L, int C);
void jump_map(FILE *fp, int P);

#endif