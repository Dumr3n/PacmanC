#ifdef NDEBUG
#error  "Gane tests require assertions to be enabled"
#endif

#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "game.h"

static void testInit()
{
    Game game;

    // Pellet cannot be spawn point
    assert(!gameInit(&game, (GridPosition){5, 2}, 0.4f));

    // Wall cannot be spawn point
    assert(!gameInit(&game, (GridPosition){5, 0}, 0.4f));

    // Incorrect speed cannot init game
    assert(!gameInit(&game, (GridPosition){5, 3}, -0.4f));
    assert(!gameInit(&game, (GridPosition){5, 3}, 0.0f));

    assert(gameInit(&game, (GridPosition){5, 3}, 0.4f));
    
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 0);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 3);
    assert(game.player.progress == 0.0f);
    assert(game.player.direction == DIR_NONE);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);
}

static void pelletIncreasingScore()
{
    Game game;
    
    assert(gameInit(&game, (GridPosition){5, 3}, 0.4f));
    
    assert(game.maze.pelletsRemaining == 28);
    gameRequestDirection(&game, DIR_RIGHT);
    gameUpdate(&game, 1.5f);

    assert(game.maze.pelletsRemaining == 28);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 0);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 3);
    assert(game.player.progress == 0.6f);
    assert(game.player.direction == DIR_RIGHT);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);

    gameRequestDirection(&game, DIR_RIGHT);

    gameUpdate(&game, 1.5f);

    assert(game.maze.pelletsRemaining == 27);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 10);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 4);
    
    assert(fabsf(game.player.progress - 0.2f) < 1e-5f);
    assert(game.player.direction == DIR_RIGHT);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);

    gameUpdate(&game, 7);

    assert(game.maze.pelletsRemaining == 24);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 40);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 7);
    
    assert(game.player.progress == 0.0f);
    assert(game.player.direction == DIR_NONE);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);

    gameRequestDirection(&game, DIR_UP);
    assert(game.player.requestedDirection == DIR_UP);
    gameUpdate(&game, 6);

    assert(game.maze.pelletsRemaining == 22);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 100);
    assert(game.player.cell.row == 3);
    assert(game.player.cell.col == 7);
    assert(fabsf(game.player.progress - 0.4f) < 1e-5f);
    assert(game.player.direction == DIR_UP);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);
}

static void testNoRepeatingPellet()
{
    Game game;
    
    assert(gameInit(&game, (GridPosition){5, 3}, 0.4f));
    assert(game.maze.pelletsRemaining == 28);
    gameRequestDirection(&game, DIR_RIGHT);
    gameUpdate(&game, 2.5);
    
    assert(game.maze.pelletsRemaining == 27);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 10);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 4);
    assert(game.player.progress == 0.0f);
    assert(game.player.direction == DIR_RIGHT);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);

    gameRequestDirection(&game, DIR_LEFT);
    assert(game.player.requestedDirection == DIR_LEFT);

    gameUpdate(&game, 2.5);
    assert(game.maze.pelletsRemaining == 27);
    assert(game.phase == GAME_PLAYING);
    assert(game.score == 10);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 3);
    assert(game.player.progress == 0.0f);
    assert(game.player.direction == DIR_LEFT);
    assert(game.player.requestedDirection == DIR_NONE);
    assert(game.player.speed == 0.4f);

}

static void testEndGame()
{
    Game game;
    assert(gameInit(&game, (GridPosition){5, 3}, 0.4f));
    assert(game.maze.pelletsRemaining == 28);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 3);

    for (int row = 0; row < MAZE_HEIGHT; ++row) {
        for (int col = 0; col < MAZE_WIDTH; ++col) {
            if (row == 5 && col == 4) {
                continue;
            }
            mazeConsumePellet(&game.maze, row, col);
        }
    }
    assert(game.phase == GAME_PLAYING);
    assert(game.maze.pelletsRemaining == 1);
    gameRequestDirection(&game, DIR_RIGHT);
    gameUpdate(&game, 2.5);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 4);
    assert(game.phase == GAME_LEVEL_COMPLETE);
    assert(game.score == 10);
    gameUpdate(&game, 2.5);
    assert(game.player.cell.row == 5);
    assert(game.player.cell.col == 4);
}

int main()
{
    testInit();
    pelletIncreasingScore();
    testNoRepeatingPellet();
    testEndGame();
    return 0;
}