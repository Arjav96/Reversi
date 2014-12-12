#ifndef GAME_H
#define	GAME_H

#include "movement.h"

typedef struct {
    Board_t* board;
    int move_num;
    int move_max;
    Movement_t* move_arr;
} Game_t;

#endif	/* GAME_H */

