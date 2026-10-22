#ifndef PACMAN_GRID_H
#define PACMAN_GRID_H

typedef struct {
    int row;
    int col;
} GridPosition;

typedef enum {
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

#endif