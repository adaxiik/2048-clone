#include "../../include/render/animate.h"
#include <stdbool.h>
void AnimateTile(App* app,Game* game,int id){
    if(!game->animations[id].animating)
        return;
    switch (game->animations[id].type)
    {
    case NEWTILE:
        NewTileAnimation(app,game,id);
        break;
    case MOVETILE:
        MoveTileAnimation(app,game,id);
        break;
    default:
        break;
    }
}
void NewTileAnimation(App *app, Game *game,int id){
    game->animations[id].sizeModifier += 10*app->deltaTime;
    if(game->animations[id].sizeModifier>.99){
        game->animations[id].animating = false;
        game->animations[id].sizeModifier = 1;
        return;
    }
}
void MoveTileAnimation(App *app, Game *game,int id){
    int distance; 
    float speed = 5;
    switch (game->animations[id].move)
    {
    case UP:
        distance = game->tiles[id].y * app->offsets.size - game->animations[id].targetTile.y *app->offsets.size;
        game->animations[id].YposModifier -= (distance*speed)*app->deltaTime;
        break;
    case DOWN:
        distance = game->tiles[id].y * app->offsets.size - game->animations[id].targetTile.y *app->offsets.size;
        game->animations[id].YposModifier -= (distance*speed)*app->deltaTime;
        break;
    case RIGHT:
        distance = game->tiles[id].x * app->offsets.size - game->animations[id].targetTile.x * app->offsets.size;
        game->animations[id].XposModifier -= (distance*speed)*app->deltaTime;
        break;
    case LEFT:
        distance = game->tiles[id].x * app->offsets.size-game->animations[id].targetTile.x * app->offsets.size;    
        game->animations[id].XposModifier -= (distance*speed)*app->deltaTime;
        break;
    default:
        break;
    }
}