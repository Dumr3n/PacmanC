#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

static bool canMove(
    const Maze* maze,
    GridPosition position,
    Direction direction
)
{
    if (direction == DIR_NONE) {
        return false;
    }

    GridPosition next = nextGridPosition(position, direction);
    
    return mazeIsWalkable(maze, next.row, next.col);
}


static Direction chooseDirection(
    const Player* player,
    const Maze* maze
)
{
    if (canMove(maze, player->cell, player->requestedDirection)) {
        return player->requestedDirection;
    }

    if (canMove(maze, player->cell, player->direction)) {
        return player->direction;
    }

    return DIR_NONE;
}

GridPosition nextGridPosition(
    GridPosition current,
    Direction direction
)
{
    switch (direction)
    {
    case DIR_LEFT:
        --current.col;
        break;
    case DIR_RIGHT:
        ++current.col;
        break;
    case DIR_UP:
        --current.row;
        break;
    case DIR_DOWN:
        ++current.row;
        break;
    case DIR_NONE:
        break;
    default:
        fprintf(stderr, "Unrecognized direction, got %d\n", direction);
        abort();
    }

    return current;
}

bool playerInit(
    Player* player,
    const Maze* maze,
    GridPosition spawn,
    float speed
)
{
    if (!isfinite(speed) || speed <= 0.0f || !mazeIsWalkable(maze, spawn.row, spawn.col)) {
        return false;
    }
    player->cell.row = spawn.row;
    player->cell.col = spawn.col;
    player->progress = 0.0f;
    player->speed = speed;
    player->direction = DIR_NONE;
    player->requestedDirection = DIR_NONE;
    return true;
}

void playerRequestDirection(
    Player* player,
    Direction direction
)
{
    if (direction != DIR_NONE) {
        player->requestedDirection = direction;
    }
}

void playerUpdate(
    Player* player,
    const Maze* maze,
    float deltaTime
)
{
    if (!isfinite(deltaTime) || deltaTime <= 0.0f) {
        return;
    }
    
    float distanceRemaining = player->speed * deltaTime;

    while (distanceRemaining > 0.0f) {
        if (player->progress == 0.0f) {
            
            player->direction = chooseDirection(player, maze);

            if (player->direction == DIR_NONE)  {
                return;
            }

            if (player->direction == player->requestedDirection) {
                player->requestedDirection = DIR_NONE;
            }
        }

        float distanceToNextCell = 1.0f - player->progress;

        if (distanceRemaining < distanceToNextCell) {
            player->progress += distanceRemaining;
            return;
        }

        player->cell = nextGridPosition(
            player->cell,
            player->direction
        );

        player->progress = 0.0f;
        distanceRemaining -= distanceToNextCell;
    }

}