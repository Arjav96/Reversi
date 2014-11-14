#include <stdio.h>

typedef enum {
    FICHA_VACIO = 0,
    FICHA_NEGRA,
    FICHA_BLANCA
} Ficha;

Ficha tablero[8][8];

const char simbolo[3] = {'.', 'X', 'O'};

void inicializar();
void imprimir();

int main() {
    printf("Reversi\n");
    inicializar();
    imprimir();
}

void inicializar() {
    int x, y;
    
    for(x = 0; x < 8; ++x) {
        for(y = 0; y < 8; ++y) {
            tablero[x][y] = FICHA_VACIO;
        }
    }
    
    tablero[3][3] = tablero[4][4] = FICHA_BLANCA;
    tablero[3][4] = tablero[4][3] = FICHA_NEGRA;
}

void imprimir() {
    int x, y;
    
    for(x = 0; x < 8; ++x) {
        for(y = 0; y < 8; ++y) {
            printf("%c", simbolo[tablero[x][y]]);
        }
        printf("\n");
    }
}