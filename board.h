#ifndef BOARD_H
#define	BOARD_H

#include "domino.h"

typedef struct {
    int rows;
    int cols;
    Domino_t **b;
} Board_t;

Board_t* board_new(int rows, int cols);
void board_free(Board_t* board);
void board_print(Board_t *board);
int board_inside(Board_t *board, int r, int c);
int board_check_movement(Board_t *board, Domino_t player, int r, int c);
int board_check_all_movements(Board_t *board, Domino_t player);
int board_count_dominoes(Board_t *board, Domino_t player);
Domino_t board_check_end(Board_t *board);
int board_place(Board_t *board, Domino_t player, int r, int c);

#endif/* BOARD_H */

