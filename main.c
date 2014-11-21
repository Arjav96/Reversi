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
int comprobar_todos_movimientos(Ficha tablero[8][8], Ficha jugador);
Ficha fin(Ficha tablero[8][8]);
int colocar(Ficha tablero[8][8], Ficha jugador, int f, int c);

int main() {
    Ficha tablero[8][8];
    
    printf("Reversi\n");
    inicializar(tablero);
    
    Ficha estado;
    Ficha turno = FICHA_BLANCA;
    int f, c;
    char cf, cc;
    for(estado = fin(tablero); !estado; estado = fin(tablero)) {
        imprimir(tablero);
        if(turno == FICHA_BLANCA) {
            printf("Es el turno de las blancas\n");
        } else {
            printf("Es el turno de las negras\n");
        }
        
        if(comprobar_todos_movimientos(tablero, turno)) {
            printf("Movimientos posibles: ");
            for(f = 0; f < 8; ++f) {
                for(c = 0; c < 8; ++c) {
                    if(comprobar_movimiento(tablero, turno, f, c)) {
                        printf("%c%c ", '1'+((char)f), 'A'+((char)c));
                    }
                }
            }
            printf("\n");
            
            cf = '\0';
            do {
                if(cf != '\0') {
                    printf("No se puede poner en %c%c\n", cf, cc);
                }
                printf("Elija movimiento: ");
                scanf("%c%c", &cf, &cc);
                getchar();

                f = (int)(cf-'1');
                c = (int)(cc-'A');
            } while(!colocar(tablero, turno, f, c));
        } else {
            printf("No hay movimientos posibles. Pierde turno\n");
        }
        
        if(turno == FICHA_BLANCA) {
            turno = FICHA_NEGRA;
        } else {
            turno = FICHA_BLANCA;
        }
    }
    
    switch(estado) {
        case FICHA_NEGRA:
            printf("Ganan las negras\n");
            break;
        case FICHA_BLANCA:
            printf("Ganan las blancas\n");
            break;
        default:
            printf("Empate\n");
    }
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
    
    printf(" ABCDEFGH\n");
    for(x = 0; x < 8; ++x) {
        printf("%i", x+1);
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
        {0, -1},    //W
        {-1, -1}     //NW
    };
    
    int d, x, y;
    int encontrado_enemigo;
    int posible;
    
    if(!dentro(f, c) || tablero[f][c]) { //Ya existe una ficha en ese posición
        return 0;
    }
    
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

int comprobar_todos_movimientos(Ficha tablero[8][8], Ficha jugador) {
    int f, c;
    
    for(f = 0; f < 8; ++f) {
        for(c = 0; c < 8; ++c) {
            if(comprobar_movimiento(tablero, jugador, f, c)) {
                return 1;
            }
        }
    }
    
    return 0;
}

Ficha fin(Ficha tablero[8][8]) {
    if(!comprobar_todos_movimientos(tablero, FICHA_BLANCA) && !comprobar_todos_movimientos(tablero, FICHA_NEGRA)) {
        int blancas = 0, negras = 0;
        int f, c;
        
        for(f = 0; f < 8; ++f) {
            for(c = 0; c < 8; ++c) {
                switch(tablero[f][c]) {
                    case FICHA_BLANCA:
                        ++blancas;
                        break;
                    case FICHA_NEGRA:
                        ++negras;
                        break;
                }
            }
        }
        
        if(negras > blancas) {
            return FICHA_NEGRA;
        } else if(blancas > negras) {
            return FICHA_BLANCA; 
        } else {
            return -1; //Empate
        }
    } else {
        return FICHA_VACIO;//0, false
    }
}

int colocar(Ficha tablero[8][8], Ficha jugador, int f, int c) {
    const int dir[8][2] = {
        {-1, 0},    //N
        {-1, 1},    //NE
        {0, 1},     //E
        {1, 1},     //SE
        {1, 0},     //S
        {1, -1},    //SW
        {0, -1},    //W
        {-1, -1}     //NW
    };
    
    int d, x, y;
    int encontrado_enemigo;
    int posible;
    
    if(!dentro(f, c) || tablero[f][c]) { //Ya existe una ficha en ese posición
        return 0;
    }
    
    for(d = 0; d < 8; ++d) {
        encontrado_enemigo = 0;
        posible = posible || 0;
        x = f;
        y = c;
        
        for(;;) { //bucle-avanzar
            x += dir[d][0];
            y += dir[d][1];
            
            if(dentro(x, y)) {
                if(encontrado_enemigo) {
                    if(tablero[x][y] == FICHA_VACIO) {
                        posible = posible || 0;
                        break;
                    } else if(tablero[x][y] == jugador) {
                        posible = 1;
                        
                        do {
                            x -= dir[d][0];
                            y -= dir[d][1];
                            tablero[x][y] = jugador;
                        } while(!(x==f && y==c));
                        
                        break;
                    }
                } else {
                    if(tablero[x][y] == jugador || tablero[x][y] == FICHA_VACIO) {
                        posible = posible || 0;
                        break;
                    } else { //Ficha enemiga
                        encontrado_enemigo = 1;
                    }
                }
            } else {
                posible = posible || 0;
                break;
            }
        } //end bucle-avanzar
    }
    
    return posible;
}
