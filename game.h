#ifndef GAME_H
#define	GAME_H

#include "domino.h"
#include "movement.h"
#include "board.h"

#define GAME_RESERVE_SIZE 5

typedef struct {
    Domino_t turn;
    Board_t* board;
    int move_num;
    int move_max;
    Movement_t* move_arr;
} Game_t;

Game_t* game_new(int r, int c);
Game_t* game_from_file(FILE* fh);
void game_free(Game_t* game);
void game_to_file(Game_t* game, FILE* fh);
void game_change_turn(Game_t* game);
int game_place(Game_t* game, Movement_t move);
Domino_t game_check_end(Game_t* game);
Domino_t game_get_turn(Game_t* game);
void game_print_movements(Game_t* game);

#endif	/* GAME_H */

