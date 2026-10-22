#include "maze.h"

#include <stdio.h>

// Layout:
//  # - wall
//  . - pellet
//  o - power pellet

static const char INITIAL_LAYOUT[MAZE_HEIGHT][MAZE_WIDTH+1] = { // +1 for '\0'
    "#########",
    "#...#...#",
    "#.#...#.#",
    "#o..#..o#",
    "#.#...#.#",
    "#.. ....#",
    "#########"
};

static bool mazeInBounds(
    int row,
    int col
)
{
    return row >= 0 && row < MAZE_HEIGHT &&
           col >= 0 && col < MAZE_WIDTH;
}

void mazeInit(Maze* maze)
{
    maze->pelletsRemaining = 0;

    for (int row = 0; row < MAZE_HEIGHT; ++row) {
        for (int col = 0; col < MAZE_WIDTH; ++col) {
            char symbol = INITIAL_LAYOUT[row][col];
            switch (symbol)
            {
            case '#':
                maze->cells[row][col] = TILE_WALL;
                break;
            case '.':
                maze->cells[row][col] = TILE_PELLET;
                ++maze->pelletsRemaining;
                break;
            case 'o':
                maze->cells[row][col] = TILE_POWER_PELLET;
                ++maze->pelletsRemaining;
                break;
            case ' ':
                maze->cells[row][col] = TILE_EMPTY;
                break;
            default:
                fprintf(stderr, "Incorrect input in INITIAL_LAYOUT, got %c\n", symbol);
                abort();
            }
        }
    }
}

bool mazeIsWalkable(
    const Maze* maze,
    int row,
    int col
)
{
    if (!mazeInBounds(row, col)) {
        return false;
    }
    return mazeGetTile(maze, row, col) != TILE_WALL;
}

Tile mazeGetTile(
    const Maze* maze,
    int row,
    int col
)
{
    if (!mazeInBounds(row, col)) {
        return TILE_WALL;
    }
    return maze->cells[row][col];
}

Tile mazeConsumePellet(
    Maze* maze,
    int row,
    int col
)
{
    if (!mazeInBounds(row, col)) {
        return TILE_EMPTY;
    }
    
    Tile consumedTile = maze->cells[row][col];
    if (consumedTile != TILE_PELLET &&
        consumedTile != TILE_POWER_PELLET) {
        return TILE_EMPTY;
    }

    maze->cells[row][col] = TILE_EMPTY;
    --maze->pelletsRemaining;
    
    return consumedTile;
}