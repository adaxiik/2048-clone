#include <stdbool.h>
#include "../include/render/app.h"
#include "../include/render/draw.h"
#include "../include/game/game.h"
#include "../include/game/input.h"
#include "../include/game/argsParse.h"
#define WIDTH 800
#define HEIGHT 800
    
int main(int argc, char *argv[])
{   
    Settings settings = {.RC.x = 4,.RC.y = 4,.resolution.x = 800,.resolution.y = 800};
    ParseArgs(&settings,argc,(char **)argv);
    App *app = Init(settings.resolution.y,settings.resolution.x);      //vykreslování
    Game *game = GameConstructor(settings.RC.x,settings.RC.y);  //hra

    app->RC.x = game->R;
    app->RC.y = game->C;

    CalculateOffsets(app);      //offsety pro výpočet pozic atd..
    BakeFonts(app);             //bakene fonty do textur
    SDL_AddEventWatch(resizingEventWatcher,app);    //resizing

    bool quit = false;
    Uint32 lastUpdate = SDL_GetTicks();
    Uint32 current;

    while (!quit)
    {
        current = SDL_GetTicks();
        app->deltaTime = (current - lastUpdate)/1000.0; //pro scaling animací při různých fps
        quit = InputHandle(game,app->event);        
        PlayGame(game);
        RenderGame(app,game);
        lastUpdate = current;
    }
    
    CleanUp(app);
    GameDeconstructor(game);
    return 0;
}