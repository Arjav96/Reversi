#ifndef DOMINO_H
#define	DOMINO_H

typedef enum {
    DOMINO_VOID = 0,
    DOMINO_BLACK,
    DOMINO_WHITE,
    DOMINO_BOTH
} Domino_t;

extern const char symbol[3];

#endif/* DOMINO_H */
