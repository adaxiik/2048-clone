#pragma once
#include "game.h"

bool AvaiableMove(Game* game);
bool Compares(Game *game,int start, int end);
bool PositionExist(Game* game, Vector2 position);
int IdFromVector(Game *game, Vector2 v);
Vector2 PositionMax(Game* game, Vector2 current);
bool CheckWin(Game *game);