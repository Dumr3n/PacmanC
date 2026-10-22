#ifdef NDEBUG
#error  "Player tests require assertions to be enabled"
#endif

#include <assert.h>

#include "player.h"
#include "maze.h"

static void testPlayerMovement()
{
    Maze maze;
    mazeInit(&maze);

    Player player;

    assert(playerInit(
        &player,
        &maze,
        (GridPosition){5,3},
        4.0f
    ));

    playerRequestDirection(&player, DIR_RIGHT);

    playerUpdate(&player, &maze, 0.125f);

    assert(player.cell.row == 5);
    assert(player.cell.col == 3);
    assert(player.direction == DIR_RIGHT);
    assert(player.progress == 0.5f);

    playerUpdate(&player, &maze, 0.125f);

    assert(player.cell.row == 5);
    assert(player.cell.col == 4);
    assert(player.progress == 0.0f);
}

static void testMultipleTileCrossings()
{
    Maze maze;
    mazeInit(&maze);

    Player player;

    assert(playerInit(
        &player,
        &maze,
        (GridPosition){5,3},
        4.0f
    ));

    playerRequestDirection(&player, DIR_RIGHT);

    playerUpdate(&player, &maze, 0.625f);

    assert(player.cell.row == 5);
    assert(player.cell.col == 5);
    assert(player.direction == DIR_RIGHT);
    assert(player.progress == 0.5f);
}

static void testChangeDirectionAtWall()
{
    Maze maze;
    mazeInit(&maze);

    Player player;
    assert(playerInit(
        &player,
        &maze,
        (GridPosition){1,1},
        4.0f
    ));
    playerRequestDirection(&player, DIR_LEFT);
    playerUpdate(&player, &maze, 0.225f);
    assert(player.cell.row == 1);
    assert(player.cell.col == 1);
    assert(player.direction == DIR_NONE);
    assert(player.progress == 0.0f);

    playerRequestDirection(&player, DIR_RIGHT);
    playerUpdate(&player, &maze, 0.25f);
    assert(player.cell.row == 1);
    assert(player.cell.col == 2);
    assert(player.direction == DIR_RIGHT);
    assert(player.progress == 0.0f);
}

static void testBufferedTurning()
{
    Maze maze;
    mazeInit(&maze);

    Player player;
    assert(playerInit(
        &player,
        &maze,
        (GridPosition){5,2},
        4.0f
    ));

    playerRequestDirection(&player, DIR_RIGHT);
    playerUpdate(&player, &maze, 0.125f);
    assert(player.progress == 0.5f);
    playerRequestDirection(&player, DIR_UP);
    playerUpdate(&player, &maze, 0.25f);

    assert(player.cell.row == 5);
    assert(player.cell.col == 3);
    assert(player.direction == DIR_UP);
    assert(player.progress == 0.5f);
}

static void testMultipleCrossingAndStopAtWall()
{
    Maze maze;
    mazeInit(&maze);

    Player player;
    assert(playerInit(
        &player,
        &maze,
        (GridPosition){1,1},
        10.0f
    ));

    playerRequestDirection(&player, DIR_RIGHT);
    playerUpdate(&player, &maze, 0.4f);

    assert(player.cell.row == 1);
    assert(player.cell.col == 3);
    assert(player.direction == DIR_NONE);
    assert(player.progress == 0.0f);
}

static void testNonMoveWithoutDirection()
{
    Maze maze;
    mazeInit(&maze);

    Player player;
    assert(playerInit(
        &player,
        &maze,
        (GridPosition){1,1},
        10.0f
    ));

    playerUpdate(&player, &maze, 0.4f);

    assert(player.cell.row == 1);
    assert(player.cell.col == 1);
    assert(player.direction == DIR_NONE);
    assert(player.progress == 0.0f);
}
int main()
{
    testPlayerMovement();
    testMultipleTileCrossings();
    testChangeDirectionAtWall();
    testBufferedTurning();
    testMultipleCrossingAndStopAtWall();
    testNonMoveWithoutDirection();
    return 0;
}