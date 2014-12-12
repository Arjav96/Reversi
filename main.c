#include "common.h"
#include "main.h"

int main() {
    Board_t *board;
    
    printf("+++++++\nReversi\n+++++++\n\n");
    board = board_new(8, 8);
    if(board == NULL) {
        return 1;
    }
    
    Domino_t state;
    Domino_t turn = DOMINO_WHITE;
    int r, c;
    char cc;
    for(state = board_check_end(board); !state; state = board_check_end(board)) {
        board_print(board);
        if(turn == DOMINO_WHITE) {
            printf("White O turn\n");
        } else {
            printf("Black X turn\n");
        }
        
        if(board_check_all_movements(board, turn)) {
            printf("Posible movements: ");
            for(r = 0; r < board->rows; ++r) {
                for(c = 0; c < board->cols; ++c) {
                    if(board_check_movement(board, turn, r, c)) {
                        printf("%i%c ", r+1, 'A'+((char)c));
                    }
                }
            }
            printf("\n");
            
            r = -1;
            do {
                if(r != -1) {
                    printf("Can't place on %i%c\n", r, cc);
                }
                printf("Choose position: ");
                scanf("%i%c", &r, &cc);
                getchar();

                c = (int)(cc-'A');
            } while(!board_place(board, turn, r-1, c));
        } else {
            printf("No movements available. TURN LOST\n");
        }
        
        if(turn == DOMINO_WHITE) {
            turn = DOMINO_BLACK;
        } else {
            turn = DOMINO_WHITE;
        }
    }
    
    board_print(board);
    
    switch(state) {
        case DOMINO_BLACK:
            printf("Black X WIN %i vs %i\n", board_count_dominoes(board, DOMINO_BLACK), board_count_dominoes(board, DOMINO_WHITE));
            break;
        case DOMINO_WHITE:
            printf("White O WIN %i vs %i\n", board_count_dominoes(board, DOMINO_WHITE), board_count_dominoes(board, DOMINO_BLACK));
            break;
        default:
            printf("STALEMATE\n");
    }
    
    board_free(board);
            
    return 0;
}
