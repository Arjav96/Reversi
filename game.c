#include "common.h"
#include "game.h"

Game_t* game_new(int r, int c) {
    Game_t* game = (Game_t*)malloc(sizeof(Game_t));
    
    game->board = board_new(r, c);
    game->move_num = 0;
    game->move_max = GAME_RESERVE_SIZE;
    game->move_arr = (Movement_t*)malloc(sizeof(Movement_t)*GAME_RESERVE_SIZE);
    
    return game;
}

Game_t* game_from_file(FILE* fh) {
    Game_t* game = (Game_t*)malloc(sizeof(Game_t));
    int rows, cols, moves, m, p, r, c;
    
    fscanf(fh, "%i %i %i", &rows, &cols, &moves);
    
    game->board = board_new(rows, cols);
    game->move_num = moves;
    game->move_max = moves;
    game->move_arr = (Movement_t*)malloc(sizeof(Movement_t)*moves);
    
    for(m = 0; m < moves; ++m) {
        fscanf(fh, "%i %i %i", &p, &r, &c);
        game->move_arr[m] = (Movement_t){(Domino_t)p, r, c};
        if(!board_place(game->board, game->move_arr[m])) {
            return 0;
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
    
    fprintf(fh, "%i %i %i\n", game->board->rows, game->board->cols, game->move_num);
    
    for (m = 0; m < game->move_num; ++m) {
        fprintf(fh, "%i %i %i\n", game->move_arr[m].player, game->move_arr[m].r, game->move_arr[m].c);
    }     
}

int game_place(Game_t *game, Movement_t move) {
    if(!board_place(game->board, move)) {
        return 0;
    }
    
    if(game->move_num >= game->move_max) {
        game->move_max += GAME_RESERVE_SIZE;
        game->move_arr = (Movement_t*)realloc(game->move_arr, game->move_max);
    }
    
    game->move_arr[game->move_num] = move;
    game->move_num++;
    
    return 1;
}
