#pragma once
#include "app.h"
#include "../../include/game/game.h"
void RenderGame(App *app,Game *game);
void DrawBackGround(App *app);
void DrawTile(App *app,Game *game, int id);
void CalculateOffsets(App *app);
void DrawScore(App *app, Game *game);
void DrawRetry(App *app, Game *game);
void DrawWin(App *app, Game *game);
void DrawMovingTile(App *app, Game *game, int id);
void BakeFonts(App *app);