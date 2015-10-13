# ifndef DEF_FUNCTION_H
# define DEF_FUNCTION_H
# include "Object.h"
//ïœçXÇµÇƒê∏ìxïœçX
# define TIMES 150

int EvaFunc(AREA*, STONE*, int x, int y, int turn, bool First);

MAX_SPOT SpotFunc(AREA*, STONE*, bool First);

void SetZuku(AREA*, STONE*, int num);

void ThreadFunc(AREA*, STONE*, int Size, int* MaxPoint);

# endif