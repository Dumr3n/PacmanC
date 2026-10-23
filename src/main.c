#include <stdio.h>

#include "raylib.h"

#include "game.h"
#include "renderer.h"

int main()
{
    Game game;

    if (!gameInit(
        &game,
        (GridPosition){5, 3},
        4.0f
    )) {
        fprintf(stderr, "Failed to initialize game!\n");
    }

    InitWindow(
        rendererScreenWidth(),
        rendererScreenHeight(),
        "Pac-Man C"
    );

    SetTargetFPS(60);

    const double fixedDt = 1.0 / 60.0;
    double accumulator = 0.0;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            gameRequestDirection(&game, DIR_UP);
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            gameRequestDirection(&game, DIR_DOWN);
        } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            gameRequestDirection(&game, DIR_RIGHT);
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            gameRequestDirection(&game, DIR_LEFT);
        }

        // Update
        double frameTime = GetFrameTime();

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        accumulator += frameTime;

        while (accumulator >= fixedDt) {

            gameUpdate(&game, (float)fixedDt);

            accumulator -= fixedDt;
        }

        // Render
        BeginDrawing();

        ClearBackground(BLACK);

        rendererDraw(&game);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}