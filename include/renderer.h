#ifndef PACMAN_RENDERER_H
#define PACMAN_RENDERER_H

#include "game.h"

int rendererScreenWidth();
int rendererScreenHeight();

void rendererDraw(const Game* game);

#endif