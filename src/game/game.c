#include "../../include/game/game.h"
#include "../../include/game/gameUtils.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
Game *GameConstructor(int R, int C){
    Game* game = malloc(sizeof(Game));
    game->C = C;
    game->R = R;
    game->score=0;
    game->tileCount = R*C;
    game->tiles = malloc(sizeof(Tile)*game->tileCount);
    game->animations = malloc(sizeof(Animation)*game->tileCount);
    for (int i = 0; i < game->tileCount; i++)
    {
        game->animations[i].animating=false;
    }
    
    game->input.move=NUL;
    game->input.pressedKey=0;
    game->win=false;
    game->ended=false;
    srand(time(NULL));
    NewGame(game);
    
    return game;
}
void PlayGame(Game* game){
    if(game->ended||game->win)
        return;

    MoveData m;
    switch (game->input.move)
    {
    case UP:
    case LEFT:
        m.startX = 0;
        m.startY = 0;
        m.endX = game->C-1;
        m.endY = game->R-1;
        m.stepX = 1;
        m.stepY = 1;
        MakeMove(game,m);
        game->input.move=NUL;
        break;
    case DOWN:
    case RIGHT:
        m.startX = game->C-1;
        m.startY = game->R-1;
        m.endX = 0;
        m.endY = 0;
        m.stepX = -1;
        m.stepY = -1;
        MakeMove(game,m);
        game->input.move=NUL;
        break;
        break;
    default:
        break;
    }

}

void MakeMove(Game *game, MoveData data){
    bool moved = false;
    for (int i = 0; i < game->tileCount; i++)
    {
        game->tiles[i].summed=0;
        game->animations[i].animating=false;
    }
    
    for (int y = data.startY; Compares(game,y,data.endY); y=y+data.stepY)
    {
        for (int x = data.startX; Compares(game,x,data.endX); x=x+data.stepX)
        {
            Vector2 current = {.x = x, .y=y};
            if(game->tiles[IdFromVector(game,current)].value==0)
                continue;
            Vector2 max = PositionMax(game,current);
            if(max.x!=current.x||max.y!=current.y){
                if(game->tiles[IdFromVector(game,current)].value==game->tiles[IdFromVector(game,max)].value){
                    game->tiles[IdFromVector(game,max)].summed = true;
                    game->score += (game->tiles[IdFromVector(game,max)].value)*2;
                }
                AnimationSetter(game,IdFromVector(game,max),HIDE,max);
                AnimationSetter(game,IdFromVector(game,current),MOVETILE,max);
                
                game->tiles[IdFromVector(game,max)].value += game->tiles[IdFromVector(game,current)].value;
                
                game->tiles[IdFromVector(game,current)].value = 0; 
                moved = true;       
            }
            
        }
    }
    if(moved)
        GenerateNewTile(game);
}
void DisableAnimations(Game *game){
    for (int i = 0; i < game->tileCount; i++)
    {
        if(game->animations[i].type!=NEWTILE)
            game->animations[i].animating=false;
    }
    
}
void NewGame(Game* game){
    game->ended = false;
    game->win=false;
    game->score=0;
    game->input.move=NUL;
    for (int i = 0; i < game->R; i++)
    {
       for (int j = 0; j < game->C; j++)
        {
           Vector2 v = {.x=j,.y=i};
           game->tiles[IdFromVector(game,v)].value=0;
           game->tiles[IdFromVector(game,v)].x=j;
           game->tiles[IdFromVector(game,v)].y=i;
           game->animations[IdFromVector(game,v)].animating=false;
        }       
    } 
    int fst = rand()%game->tileCount;
    int snd;
    do
    {
        snd = rand()%game->tileCount;
    } while (fst==snd);
    
    game->tiles[fst].value=rand()%2==0?2:4;
    game->tiles[snd].value=rand()%2==0?2:4;
}

void GenerateNewTile(Game* game){
    if(CheckWin(game)){
        game->win=true;
        return;
    } 
    Vector2 empty; //placeholder
    //asi to není nelepší, ale nah..
    int free=0;
    for (int i = 0; i < game->tileCount; i++)
    {
        free+=game->tiles[i].value==0?1:0;
    }
    
    int selected = rand() % free;
    for (int i = 0; i < game->tileCount; i++)
    {
        if(selected==0&&game->tiles[i].value==0){
            game->tiles[i].value=rand()%2==0?2:4;
            AnimationSetter(game,i,NEWTILE,empty);
            break;
        }
        if(game->tiles[i].value==0)
            selected--;
    }
    if(free==1)
        if(!AvaiableMove(game)){
            game->ended=true;
            //printf("Konec hry\n");
            //NewGame(game);
        }
    
}
void AnimationSetter(Game *game,int id,AnimationType type, Vector2 targetTile){
    
    if(game->animations[id].animating)
        return;
    if(type!=NEWTILE&&type!=MOVETILE&& game->tiles[id].summed&&game->tiles[id].value!=0)
        game->animations[id].type = STILL;
    else
        game->animations[id].type = type;

    game->animations[id].animating = true;
    game->animations[id].targetTile = targetTile;
    game->animations[id].move = game->input.move;
    game->animations[id].originalValue = game->tiles[id].value;
    game->animations[id].XposModifier=0;
    game->animations[id].YposModifier=0;

    switch (type)
    {
    case NEWTILE:
        game->animations[id].sizeModifier=0;
        break;
    default:
        game->animations[id].sizeModifier=1;
        break;
    }     
}

void GameDeconstructor(Game* game){
    free(game->animations);
    free(game->tiles);
    free(game);
}