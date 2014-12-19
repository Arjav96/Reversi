#ifndef GAME_H
#define	GAME_H

#include "movement.h"
#include "board.h"

#define GAME_RESERVE_SIZE 5

typedef struct {
    Board_t* board;
    int move_num;
    int move_max;
    Movement_t* move_arr;
} Game_t;

Game_t* game_new(int r, int c);
Game_t* game_from_file(FILE* fh);
void game_free(Game_t* game);
void game_to_file(Game_t* game, FILE* fh);
int game_place(Game_t *game, Movement_t move);

#endif	/* GAME_H */

