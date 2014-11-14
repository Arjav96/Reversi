#include <stdio.h>

typedef enum {
    FICHA_VACIO = 0,
    FICHA_NEGRA,
    FICHA_BLANCA
} Ficha;

const char simbolo[3] = {'.', 'X', 'O'};

void inicializar(Ficha tablero[8][8]);
void imprimir(Ficha tablero[8][8]);
int dentro(int x, int y);
int comprobar_movimiento(Ficha tablero[8][8], Ficha jugador, int f, int c);

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

int dentro(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int comprobar_movimiento(Ficha tablero[8][8], Ficha jugador, int f, int c) {
    const int dir[8][2] = {
        {-1, 0},    //N
        {-1, 1},    //NE
        {0, 1},     //E
        {1, 1},     //SE
        {1, 0},     //S
        {1, -1},    //SW
        {-1, 0},    //W
        {-1, 1}     //NW
    };
    
    int d, x, y;
    int encontrado_enemigo;
    int posible;
    
    for(d = 0; d < 8; ++d) {
        encontrado_enemigo = 0;
        posible = 0;
        x = f;
        y = c;
        
        for(;;) { //bucle-avanzar
            x += dir[d][0];
            y += dir[d][1];
            
            if(dentro(x, y)) {
                if(encontrado_enemigo) {
                    if(tablero[x][y] == FICHA_VACIO) {
                        posible = 0;
                        break;
                    } else if(tablero[x][y] == jugador) {
                        posible = 1;
                        break;
                    }
                } else {
                    if(tablero[x][y] == jugador || tablero[x][y] == FICHA_VACIO) {
                        posible = 0;
                        break;
                    } else { //Ficha enemiga
                        encontrado_enemigo = 1;
                    }
                }
            } else {
                posible = 0;
                break;
            }
        } //end bucle-avanzar
        
        if(posible) {
            return 1;
        }
    }
    
    return 0;
}
