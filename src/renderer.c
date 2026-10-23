#include "renderer.h"

#include "raylib.h"

#define TILE_SIZE 48
#define HUD_HEIGHT 56

int rendererScreenWidth()
{
    return MAZE_WIDTH * TILE_SIZE;
}

int rendererScreenHeight()
{
    return MAZE_HEIGHT * TILE_SIZE + HUD_HEIGHT;
}

static void drawMaze(const Maze* maze)
{
    for (int row = 0; row < MAZE_HEIGHT; ++row) {
        for (int col = 0; col < MAZE_WIDTH; ++col) {

            Tile tile = mazeGetTile(maze, row, col);

            int x = col * TILE_SIZE;
            int y = HUD_HEIGHT + row * TILE_SIZE;

            switch (tile)
            {
            case TILE_WALL:
                DrawRectangle(
                    x+1,
                    y+1,
                    TILE_SIZE - 2,
                    TILE_SIZE - 2,
                    DARKBLUE
                );
                break;
            
            case TILE_PELLET:
                DrawCircle(
                    x + TILE_SIZE / 2,
                    y + TILE_SIZE / 2,
                    4,
                    RAYWHITE
                );
                break;
            
            case TILE_POWER_PELLET:
                DrawCircle(
                    x + TILE_SIZE / 2,
                    y + TILE_SIZE / 2,
                    10,
                    RAYWHITE
                );
                break;
            
            default:
                break;
            }
        }
    }
}

static void drawPlayer(const Player* player)
{
    GridPosition current = player->cell;

    float x = (current.col + 0.5f) * TILE_SIZE;
    float y = (current.row + 0.5f) * TILE_SIZE + HUD_HEIGHT;

    if (player->progress > 0.0f) {
        
        GridPosition next = nextGridPosition(current, player->direction);

        x += (next.col - current.col) * player->progress * TILE_SIZE;

        y += (next.row - current.row) * player->progress * TILE_SIZE;
    }

    DrawCircleV(
        (Vector2){x, y}, 
        TILE_SIZE * 0.4f, 
        YELLOW
    );
}

static void drawHUD(const Game* game)
{
    DrawText(
        TextFormat("SCORE: %d", game->score),
        12,
        14,
        22,
        RAYWHITE
    );
}

void rendererDraw(const Game* game)
{
    drawMaze(&game->maze);
    drawPlayer(&game->player);
    drawHUD(game);
    
    if (game->phase == GAME_LEVEL_COMPLETE) {
        DrawText(
            "LEVEL COMPLETE!",
            90,
            rendererScreenHeight() / 2,
            24,
            GREEN
        );
    }
}