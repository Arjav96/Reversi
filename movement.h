#ifndef MOVEMENT_H
#define	MOVEMENT_H

#include "domino.h"

typedef struct {
   Domino_t player;
   int r, c;
} Movement_t;

void movement_print(Movement_t move);

#endif	/* MOVEMENT_H */

