#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <stdbool.h>

#include "maze.h"
#include "player.h"

typedef enum {
    GAME_PLAYING,
    GAME_LEVEL_COMPLETE
} GamePhase;

typedef struct {
    Maze maze;
    Player player;

    int score;
    GamePhase phase;
} Game;

bool gameInit(
    Game* game,
    GridPosition spawn,
    float playerSpeed
);

void gameRequestDirection(
    Game* game,
    Direction direction
);

void gameUpdate(
    Game* game,
    float deltaTime
);

#endif