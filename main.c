#include "common.h"
#include "main.h"

typedef enum {
    NEW = 1,
    LOAD = 2,
    QUIT = 3
} MenuOption_t;

int main() {
    Game_t* current_game = NULL;
    MenuOption_t option;
    
    int playing;
    int rows, cols;
    FILE* fh;
    char buffer[256];
    
    Domino_t turn;
    
    do {
        printf("\n\n\n");
        printf("+++++++\nReversi\n+++++++\n\n");
        printf(
                "1. New\n"
                "2. Load from file\n"
                "3. Quit\n"
        );
        
        do {
            printf("Choose an option: ");
            scanf("%i", (int*)&option);
        } while(option < NEW || option > QUIT);
        
        switch(option) {
            case NEW:
                printf("Introduce dimensions of the board[rows cols]: ");
                scanf("%i %i", &rows, &cols);
                current_game = game_new(rows, cols);
                if(current_game == NULL) {
                    printf("Couldn't create game\n");
                }
                break;
            case LOAD:
                printf("Introduce filename: ");
                getchar();
                fgets(buffer, 255, stdin);
                
                buffer[strlen(buffer) - 1] = '\0';
                
                fh = fopen(buffer, "r");
                if(!fh) {
                    printf("Couldn't open file\n");
                } else {
                    current_game = game_from_file(fh);
                    if(current_game == NULL) {
                        printf("Couldn't create game\n");
                    }
                    fclose(fh);
                }
                break;
            case QUIT:
                break;
        }
        
        if(current_game) {
            playing = 1;
            while(!game_check_end(current_game) && playing) {
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
                        printf("Choose position[Type SAVE for saving and quiting]: ");
                        scanf("%s", buffer);
                        
                        if(strcmp(buffer, "SAVE") == 0) {
                            printf("Type filename for saving[no spaces allowed]: ");
                            scanf("%s", buffer);
                            fh = fopen(buffer, "w");
                            game_to_file(current_game, fh);
                            fclose(fh);
                            playing = 0;
                            break;
                        }
                        
                        sscanf(buffer, "%i%c", &r, &cc);

                        c = (int)(cc-'A');
                    } while(!game_place(current_game, (Movement_t){turn, r-1, c}));
                } else {
                    printf("No movements available. TURN LOST\n");
                    game_change_turn(current_game);
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
                case DOMINO_VOID:
                    break;
                default:
                    printf("STALEMATE\n");
            }
        
            game_free(current_game);
            current_game = NULL;
        }
    } while(option != QUIT);
    
    return 0;
}
