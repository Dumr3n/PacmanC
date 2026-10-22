#include "game.h"

#include <math.h>

#define SCORE_PELLET            10
#define SCORE_POWER_PELLET      50

static void gameHandleCellEntry(Game* game)
{
    Tile consumed = mazeConsumePellet(
        &game->maze,
        game->player.cell.row,
        game->player.cell.col
    );
    switch (consumed)
    {
    case TILE_PELLET:
        game->score += SCORE_PELLET;
        break;
    case TILE_POWER_PELLET:
        game->score += SCORE_POWER_PELLET;
        break;
    default:
        break;
    }
}

bool gameInit(
    Game* game,
    GridPosition spawn,
    float playerSpeed
)
{
    Maze maze;
    mazeInit(&maze);

    if (mazeGetTile(&maze, spawn.row, spawn.col) != TILE_EMPTY) {
        return false;
    }
    
    Player player;
    if (!playerInit(&player, &maze, spawn, playerSpeed))
    {
        return false;
    }

    game->maze = maze;
    game->player = player;
    
    game->score = 0;
    game->phase = GAME_PLAYING;

    return true;
}

void gameRequestDirection(
    Game* game,
    Direction direction
)
{
    if (game->phase != GAME_PLAYING) {
        return;
    }

    playerRequestDirection(&game->player, direction);
}

void gameUpdate(
    Game* game,
    float deltaTime
)
{
    if (
        !isfinite(deltaTime) || 
        deltaTime <= 0.0f ||
        game->phase == GAME_LEVEL_COMPLETE
    ) {
        return;
    }
    const float maxStepTime = 0.5f / game->player.speed;
    float remainingTime = deltaTime;

    while (remainingTime > 0.0f) {
        
        const float stepTime = fminf(remainingTime, maxStepTime);

        GridPosition currentPosition = game->player.cell;
        
        playerUpdate(&game->player, &game->maze, stepTime);

        GridPosition afterUpdatePosition = game->player.cell;
        
        if (
            currentPosition.row != afterUpdatePosition.row || 
            currentPosition.col != afterUpdatePosition.col
        ) {
            gameHandleCellEntry(game);
            if (game->maze.pelletsRemaining == 0) {
                game->phase = GAME_LEVEL_COMPLETE;
                return;
            }
        }
        remainingTime -= stepTime;
    }
}