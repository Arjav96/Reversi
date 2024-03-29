#include "common.h"
#include "board.h"

Board_t* board_new(int rows, int cols) {
    if(rows < 2 || cols < 2) {
        return NULL;
    }
    
    void* mem = malloc(
    sizeof(Board_t)+
    rows*sizeof(Domino_t*)+
    rows*cols*sizeof(Domino_t)
    );
    
    if(!mem) {
        return NULL;
    }
    
    Board_t* ret = (Board_t*)mem;
    ret->rows = rows;
    ret->cols = cols;
    ret->b = (Domino_t**)(ret+1);
    
    int r;
    Domino_t* p = (Domino_t*)((ret->b)+rows);
    for(r = 0; r < rows; ++r) {
        ret->b[r] = p;
        p = p + cols;
    }
    
    int x, y;
    
    for(x = 0; x < rows; ++x) {
        for(y = 0; y < cols; ++y) {
            ret->b[x][y] = DOMINO_VOID;
        }
    }
    
    int rm = rows/2,
        cm = cols/2;
    
    ret->b[rm-1][cm-1] = ret->b[rm][cm] = DOMINO_WHITE;
    ret->b[rm-1][cm] = ret->b[rm][cm-1] = DOMINO_BLACK;
    
    return ret;
}

void board_free(Board_t* board) {
    free(board);
}

void board_print(Board_t *board) {
    int x, y;
    char c;
    
    printf("/ ");
    
    for(y = 0, c = 'A'; y < board->cols; ++y, ++c) {
        printf("%2c", c);
    }
    
    printf("  \\\n");
    for(x = 0; x < board->rows; ++x) {
        printf("%-2i", x+1);
        for(y = 0; y < board->cols; ++y) {
            printf("%2c", symbol[board->b[x][y]]);
        }
        printf("%3i", x+1);
        printf("\n");
    }
    printf("\\ ");
    
    for(y = 0, c = 'A'; y < board->cols; ++y, ++c) {
        printf("%2c", c);
    }
    
    printf("  /\n");
    
    printf("Black: %i, White: %i\n", board_count_dominoes(board, DOMINO_BLACK), board_count_dominoes(board, DOMINO_WHITE));
    
}

int board_inside(Board_t *board, int r, int c) {
    return r >= 0 && r < board->rows && c >= 0 && c < board->cols;
}

int board_check_movement(Board_t *board, Movement_t move) {
    const int dir[8][2] = {
        {-1, 0},    /*N*/
        {-1, 1},    /*NE*/
        {0, 1},     /*E*/
        {1, 1},     /*SE*/
        {1, 0},     /*S*/
        {1, -1},    /*SW*/
        {0, -1},    /*W*/
        {-1, -1}     /*NW*/
    };
    
    int d, x, y;
    int enemy_found;
    int posible = 0;
    
    if(!board_inside(board, move.r, move.c) || board->b[move.r][move.c]) {
        return 0;
    }
    
    for(d = 0; d < 8; ++d) {
        enemy_found = 0;
        posible = 0;
        x = move.r;
        y = move.c;
        
        for(;;) { /*go-forward loop*/
            x += dir[d][0];
            y += dir[d][1];
            
            if(board_inside(board, x, y)) {
                if(enemy_found) {
                    if(board->b[x][y] == DOMINO_VOID) {
                        posible = 0;
                        break;
                    } else if(board->b[x][y] == move.player) {
                        posible = 1;
                        break;
                    }
                } else {
                    if(board->b[x][y] == move.player || board->b[x][y] == DOMINO_VOID) {
                        posible = 0;
                        break;
                    } else {
                        enemy_found = 1;
                    }
                }
            } else {
                posible = 0;
                break;
            }
        } /*end of go-forward loop*/
        
        if(posible) {
            return 1;
        }
    }
    
    return 0;
}

int board_check_all_movements(Board_t *board, Domino_t player) {
    int r, c;
    
    for(r = 0; r < board->rows; ++r) {
        for(c = 0; c < board->cols; ++c) {
            if(board_check_movement(board, (Movement_t){player, r, c})) {
                return 1;
            }
        }
    }
    
    return 0;
}

int board_count_dominoes(Board_t *board, Domino_t player) {
    int cant = 0;
    int r, c;
    
    for(r = 0; r < board->rows; ++r) {
        for(c = 0; c < board->cols; ++c) {
            if(board->b[r][c] == player) {
                ++cant;
            }
        }
    }
    return cant;
}

Domino_t board_check_end(Board_t *board) {
    if(!board_check_all_movements(board, DOMINO_WHITE) && !board_check_all_movements(board, DOMINO_BLACK)) {
        int whites = board_count_dominoes(board, DOMINO_WHITE),
            blacks = board_count_dominoes(board, DOMINO_BLACK);
        
        if(blacks > whites) {
            return DOMINO_BLACK;
        } else if(whites > blacks) {
            return DOMINO_WHITE; 
        } else {
            return DOMINO_BOTH; /*Stalemate*/
        }
    } else {
        return DOMINO_VOID;/*0, false*/
    }
}

int board_place(Board_t *board, Movement_t move) {
    const int dir[8][2] = {
        {-1, 0},    /*N*/
        {-1, 1},    /*NE*/
        {0, 1},     /*E*/
        {1, 1},     /*SE*/
        {1, 0},     /*S*/
        {1, -1},    /*SW*/
        {0, -1},    /*W*/
        {-1, -1}     /*NW*/
    };
    
    int d, x, y;
    int enemy_found;
    int posible;
    
    if(!board_inside(board, move.r, move.c) || board->b[move.r][move.c]) {
        return 0;
    }
    
    for(d = 0; d < 8; ++d) {
        enemy_found = 0;
        posible = posible || 0;
        x = move.r;
        y = move.c;
        
        for(;;) { /*go-forward loop*/
            x += dir[d][0];
            y += dir[d][1];
            
            if(board_inside(board, x, y)) {
                if(enemy_found) {
                    if(board->b[x][y] == DOMINO_VOID) {
                        posible = posible || 0;
                        break;
                    } else if(board->b[x][y] == move.player) {
                        posible = 1;
                        
                        do {
                            x -= dir[d][0];
                            y -= dir[d][1];
                            board->b[x][y] = move.player;
                        } while(!(x==move.r && y==move.c));
                        
                        break;
                    }
                } else {
                    if(board->b[x][y] == move.player || board->b[x][y] == DOMINO_VOID) {
                        posible = posible || 0;
                        break;
                    } else { /*Enemy Domino_t*/
                        enemy_found = 1;
                    }
                }
            } else {
                posible = posible || 0;
                break;
            }
        } /*end go-forward loop*/
    }
    
    return posible;
}
