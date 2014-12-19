#include "common.h"
#include "game.h"

Game_t* game_new(int r, int c) {
    Game_t* game = (Game_t*)malloc(sizeof(Game_t));
    
    game->turn = DOMINO_WHITE;
    game->board = board_new(r, c);
    game->move_num = 0;
    game->move_max = GAME_RESERVE_SIZE;
    game->move_arr = (Movement_t*)malloc(sizeof(Movement_t)*GAME_RESERVE_SIZE);
    
    return game;
}

Game_t* game_from_file(FILE* fh) {
    Game_t* game = (Game_t*)malloc(sizeof(Game_t));
    int rows, cols, moves, m, p, r, c;
    
    fscanf(fh, "%i", &game->turn);
    fscanf(fh, "%i %i %i", &rows, &cols, &moves);
    
    game->board = board_new(rows, cols);
    
    if(!game->board) {
        free(game);
        return NULL;
    }
    
    game->move_num = moves;
    game->move_max = moves;
    game->move_arr = (Movement_t*)malloc(sizeof(Movement_t)*moves);
    
    for(m = 0; m < moves; ++m) {
        fscanf(fh, "%i %i %i", &p, &r, &c);
        game->move_arr[m] = (Movement_t){(Domino_t)p, r, c};
        if(!board_place(game->board, game->move_arr[m])) {
            free(game->move_arr);
            free(game);
            return NULL;
        }
    }
    
    return game;
}

void game_free(Game_t* game) {
    free(game->move_arr);
    board_free(game->board);
    free(game);
}

void game_to_file(Game_t* game, FILE* fh) {
    int m;
    
    fprintf(fh, "%i\n", game->turn);
    fprintf(fh, "%i %i %i\n", game->board->rows, game->board->cols, game->move_num);
    
    for (m = 0; m < game->move_num; ++m) {
        fprintf(fh, "%i %i %i\n", game->move_arr[m].player, game->move_arr[m].r, game->move_arr[m].c);
    }     
}

int game_place(Game_t* game, Movement_t move) {
    if(move.player != game->turn || !board_place(game->board, move)) {
        return 0;
    }
    
    if(game->move_num >= game->move_max) {
        game->move_max += GAME_RESERVE_SIZE;
        game->move_arr = (Movement_t*)realloc(game->move_arr, game->move_max*sizeof(Movement_t));
    }
    
    game->move_arr[game->move_num] = move;
    game->move_num++;
    
    game_change_turn(game);
    return 1;
}

void game_change_turn(Game_t* game) {
    if(game->turn == DOMINO_WHITE) {
        game->turn = DOMINO_BLACK;
    } else {
        game->turn = DOMINO_WHITE;
    }
}


Domino_t game_check_end(Game_t* game) {
    return board_check_end(game->board);
}

Domino_t game_get_turn(Game_t* game) {
    return game->turn;
}

void game_print_movements(Game_t* game) {
    int m;
    
    for(m = 0; m < game->move_num; ++m) {
        movement_print(game->move_arr[m]);
    }
}
