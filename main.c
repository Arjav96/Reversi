#include <stdio.h>

typedef enum {
    FICHA_VACIO = 0,
    FICHA_NEGRA,
    FICHA_BLANCA
} Ficha;

const char simbolo[3] = {'.', 'X', 'O'};

void inicializar(Ficha tablero[8][8]);
void imprimir(Ficha tablero[8][8]);

int main() {
    Ficha tablero[8][8];
    
    printf("Reversi\n");
    inicializar(tablero);
    imprimir(tablero);
}

void inicializar(Ficha tablero[8][8]) {
    int x, y;
    
    for(x = 0; x < 8; ++x) {
        for(y = 0; y < 8; ++y) {
            tablero[x][y] = FICHA_VACIO;
        }
    }
    
    tablero[3][3] = tablero[4][4] = FICHA_BLANCA;
    tablero[3][4] = tablero[4][3] = FICHA_NEGRA;
}

void imprimir(Ficha tablero[8][8]) {
    int x, y;
    
    for(x = 0; x < 8; ++x) {
        for(y = 0; y < 8; ++y) {
            printf("%c", simbolo[tablero[x][y]]);
        }
        printf("\n");
    }
}