#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../game/game.h"

typedef struct{
    int min;
    int size;
    Vector2 offset;
    Vector2 center;
    Vector2 pos;
    SDL_Rect firstPosition;
} Offsets;

typedef struct{
    SDL_Color _2;
    SDL_Color _4;
    SDL_Color _8;
    SDL_Color _16;
    SDL_Color _32;
    SDL_Color _64;
    SDL_Color _128;
    SDL_Color _256;
    SDL_Color _512;
    SDL_Color _1024;
    SDL_Color _2048;
}Colors;

typedef struct{
    SDL_Texture *texture;
    Vector2 size;
}TileTexture;

typedef struct{
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *squareTexture;
    Vector2 resolution;
    Vector2 RC;
    Colors fontColors;
    Colors backgroundColors;
    Offsets offsets;
    float deltaTime;
    TileTexture *textures;
}App;
App *Init(int windowHeight, int windowWidth);
int resizingEventWatcher(void* app, SDL_Event* event);
void CleanUp(App *app);
