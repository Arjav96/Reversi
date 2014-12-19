#include "common.h"
#include "main.h"

typedef enum {
    NEW = 1,
    LOAD = 2,
    QUIT = 3
} MenuOption_t;

int main() {
    Game_t* current_game;
    MenuOption_t option;
    
    int rows, cols;
    char filename[256];
    
    Domino_t turn;
    
    printf("+++++++\nReversi\n+++++++\n\n");
    
    do {
        printf(
                "1. New\n"
                "2. Load from file\n"
                "3. Quit\n"
        );
        
        do {
            printf("Choose an option: ");
            scanf("%i", &option);
        } while(option < NEW || option > QUIT);
        
        switch(option) {
            case NEW:
                printf("Introduce dimensions of the board[rows cols]: ");
                scanf("%i %i", &rows, &cols);
                current_game = game_new(rows, cols);
                if(current_game == NULL) {
                    printf("Couldn't create game\n");
                    return 1;
                }
                break;
            case LOAD:
                printf("Test: Reading from stdin\n");
                current_game = game_from_file(stdin);
                if(current_game == NULL) {
                    printf("Couldn't create game\n");
                    return 1;
                }
                break;
            case QUIT:
                return 0;
                break;
        }
        
        while(!game_check_end(current_game)) {
            board_print(current_game->board);
            
            turn = game_get_turn(current_game);
            
            if(turn == DOMINO_WHITE) {
                printf("White O turn\n");
            } else {
                printf("Black X turn\n");
            }
            
            int r, c;
            if(board_check_all_movements(current_game->board, turn)) {
                printf("Posible movements: ");
                for(r = 0; r < current_game->board->rows; ++r) {
                    for(c = 0; c < current_game->board->cols; ++c) {
                        if(board_check_movement(current_game->board, (Movement_t){turn, r, c})) {
                            printf("%i%c ", r+1, 'A'+((char)c));
                        }
                    }
                }
                printf("\n");

                char cc;
                r = -1;
                do {
                    if(r != -1) {
                        printf("Can't place on %i%c\n", r, cc);
                    }
                    printf("Choose position: ");
                    scanf("%i%c", &r, &cc);
                    getchar();

                    c = (int)(cc-'A');
                } while(!game_place(current_game, (Movement_t){turn, r-1, c}));
            } else {
                printf("No movements available. TURN LOST\n");
            }
        }
        
        board_print(current_game->board);
        
        game_print_movements(current_game);
        
        switch(game_check_end(current_game)) {
            case DOMINO_BLACK:
                printf("Black X WIN %i vs %i\n", board_count_dominoes(current_game->board, DOMINO_BLACK), board_count_dominoes(current_game->board, DOMINO_WHITE));
                break;
            case DOMINO_WHITE:
                printf("White O WIN %i vs %i\n", board_count_dominoes(current_game->board, DOMINO_WHITE), board_count_dominoes(current_game->board, DOMINO_BLACK));
                break;
            default:
                printf("STALEMATE\n");
        }
        
    } while(option != QUIT);
    
    game_free(current_game);
    
    return 0;
    /*
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
                    if(board_check_movement(board, (Movement_t){turn, r, c})) {
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
            } while(!board_place(board, (Movement_t){turn, r-1, c}));
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
     */
}
