#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H

#include <stdbool.h>
#include "grid.h"
#include "maze.h"

typedef struct {
    GridPosition cell;

    Direction direction;
    Direction requestedDirection;

    float progress;
    float speed;
} Player;

bool playerInit(
    Player* player,
    const Maze* maze,
    GridPosition spawn,
    float speed
);

void playerRequestDirection(
    Player* player,
    Direction direction
);

void playerUpdate(
    Player* player,
    const Maze* maze,
    float deltaTime
);

GridPosition nextGridPosition(
    GridPosition current,
    Direction direction
);

#endif