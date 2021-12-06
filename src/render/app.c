#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../../include/render/app.h"
#include "../../include/render/drawUtils.h"
#include "../../include/render/draw.h"

App *Init(int windowHeight, int windowWidth){
    App* app = malloc(sizeof(App));
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    if (TTF_Init()) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        exit(1);
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        exit(1);
    }
    SDL_Window* window = SDL_CreateWindow("2048 Game - Jantula Adam", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    app->window = window;


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    app->renderer = renderer;

    //ikona
    SDL_Surface* s = IMG_Load("assets/icon.png");
    if(!s){
        fprintf(stderr, "SDL_IMG_Load: %s\n", SDL_GetError());
       exit(1);
    }
    SDL_SetWindowIcon(app->window,s);
    SDL_FreeSurface(s);
    app->textures = malloc(sizeof(TileTexture)*11);
    for (int i = 0; i < 11; i++)
    {
        app->textures[i].texture=0;
    }
    
    app->resolution.y = windowHeight;
    app->resolution.x = windowWidth;
    app->squareTexture = LoadTexture(app->renderer,"assets/square.png");
    app->backgroundColors = SetBackgroundColors();
    app->fontColors = SetFontColors();
    
    return app;
}

//https://stackoverflow.com/questions/32294913/getting-contiunous-window-resize-event-in-sdl-2
int resizingEventWatcher(void* data, SDL_Event* event) {
    App *app = (App*)data;
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
        if (win == app->window) {
            app->resolution.x=event->window.data1;
            app->resolution.y=event->window.data2;
            CalculateOffsets(app);
            BakeFonts(app);
        }
    }
    return 0;
}

void CleanUp(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_DestroyTexture(app->squareTexture);
    SDL_VideoQuit();
    for (int i = 0; i < 11; i++)
    {
        SDL_DestroyTexture(app->textures[i].texture);
    }
    
    SDL_Quit();
    TTF_Quit();
    free(app->textures);
    free(app);
}