#ifdef NDEBUG
#error  "Maze tests require assertions to be enabled"
#endif

#include <assert.h>

#include "maze.h"

static void testPelletConsumption()
{
    Maze maze;
    mazeInit(&maze);

    int initialCount = maze.pelletsRemaining;

    assert(mazeGetTile(&maze, 1, 1) == TILE_PELLET);

    Tile consumed = mazeConsumePellet(&maze,1,1);
    assert(consumed == TILE_PELLET);
    assert(mazeGetTile(&maze, 1, 1) == TILE_EMPTY);
    assert(maze.pelletsRemaining == initialCount - 1);

    consumed = mazeConsumePellet(&maze, 1, 1);
    assert(consumed == TILE_EMPTY);
    assert(maze.pelletsRemaining == initialCount - 1);
}

static void testOutOfBounds()
{
    Maze maze;
    mazeInit(&maze);

    assert(!mazeIsWalkable(&maze, -1, 0));
    assert(!mazeIsWalkable(&maze, 0, -1));
    assert(!mazeIsWalkable(&maze, MAZE_HEIGHT, 0));
    assert(!mazeIsWalkable(&maze, 0, MAZE_WIDTH));

    assert(mazeGetTile(&maze, -1, 0) == TILE_WALL);
    assert(mazeGetTile(&maze, 0, -1) == TILE_WALL);
    assert(mazeGetTile(&maze, MAZE_HEIGHT, 0) == TILE_WALL);
    assert(mazeGetTile(&maze, 0, MAZE_WIDTH) == TILE_WALL);
}

static void testPowerPellets()
{
    Maze maze;
    mazeInit(&maze);

    assert(mazeGetTile(&maze,3,1) == TILE_POWER_PELLET);
    assert(mazeGetTile(&maze,3,7) == TILE_POWER_PELLET);
    
    int initialPellets = maze.pelletsRemaining;

    assert(mazeConsumePellet(&maze,3,1) == TILE_POWER_PELLET);
    assert(initialPellets - 1 == maze.pelletsRemaining);

    assert(mazeConsumePellet(&maze,3,7) == TILE_POWER_PELLET);
    assert(initialPellets - 2 == maze.pelletsRemaining);

    assert(mazeGetTile(&maze,3,1) == TILE_EMPTY);
    assert(mazeGetTile(&maze,3,7) == TILE_EMPTY);
    assert(initialPellets - 2 == maze.pelletsRemaining);
}

static void testWallsNotWalkable()
{
    Maze maze;
    mazeInit(&maze);

    assert(!mazeIsWalkable(&maze, 1, 0));
    assert(!mazeIsWalkable(&maze, 0, 1));
}

static void testPelletsAreWalkable()
{
    Maze maze;
    mazeInit(&maze);

    assert(mazeIsWalkable(&maze,1,1));
    assert(mazeIsWalkable(&maze,3,1));
}

static void testWallIsNotConsumable()
{
    Maze maze;
    mazeInit(&maze);

    int initialCount = maze.pelletsRemaining;
    assert(mazeConsumePellet(&maze, 0, 1) == TILE_EMPTY);
    assert(initialCount == maze.pelletsRemaining);
}

static void testRestoreMazeWithInit()
{
    Maze maze;
    mazeInit(&maze);

    int initialPellets = maze.pelletsRemaining;
    assert(mazeConsumePellet(&maze,1,1) == TILE_PELLET);
    assert(initialPellets - 1 == maze.pelletsRemaining);

    mazeInit(&maze);
    assert(mazeGetTile(&maze,1,1) == TILE_PELLET);
    assert(initialPellets == maze.pelletsRemaining);
}

int main()
{
    testOutOfBounds();
    testPelletConsumption();
    testPowerPellets();
    testRestoreMazeWithInit();
    testWallIsNotConsumable();
    testPelletsAreWalkable();
    testWallsNotWalkable();
    return 0;
}