#pragma once
#include <SDL2/SDL.h>
#include "app.h"
#include <SDL2/SDL_image.h>

typedef enum{ABSOLUTE, RELATIVETOTILE, RELATIVETORESOLUTION}Scaling;

void DrawText(App* app,int x, int y,const char* text, int size , SDL_Color color,Scaling sizeScaling, SDL_bool center, SDL_bool lengthScaling);
void DrawSquare(App* app, SDL_Rect rect, SDL_Color color,SDL_bool center);
SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *file);
Colors SetBackgroundColors();
Colors SetFontColors();
SDL_Color GetColor(int r,int g, int b,int a);
SDL_Color GetColorForValue(Colors pallete,int value);
TileTexture GetTextureForValue(App* app, int value);
void DrawTextTile(App* app,int x, int y,int value);