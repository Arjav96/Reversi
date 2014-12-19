#include "common.h"
#include "movement.h"

void movement_print(Movement_t move) {
    printf("%s moves to %i%c\n",
    (move.player == DOMINO_WHITE) ? "White O" : "Black X",
    move.r,
    'A' + (char)move.c);
}
