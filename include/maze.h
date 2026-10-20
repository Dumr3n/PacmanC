#ifndef PACMAN_HAZE_H
#define PACMAN_HAZE_H

#include <stdbool.h>

#define MAZE_WIDTH  9
#define MAZE_HEIGHT 7

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_PELLET,
    TILE_POWER_PELLET
} Tile;

typedef struct {
    Tile cells[MAZE_HEIGHT][MAZE_WIDTH];
    int pelletsRemaining;
} Maze;

void mazeInit(Maze* maze);

bool mazeIsWalkable(
    const Maze* maze,
    int row,
    int col
);

Tile mazeGetTile(
    const Maze* maze,
    int row,
    int col
);

Tile mazeConsumePellet(
    Maze* maze,
    int row,
    int col
);

#endif