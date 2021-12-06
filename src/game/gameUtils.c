#include "../../include/game/gameUtils.h"
#include <stdlib.h>

bool AvaiableMove(Game* game){
    Vector2 dirs[] = {{.x=0,.y=1},{.x=0,.y=-1},{.x=1,.y=0},{.x=-1,.y=0}};

        for (int k = 0; k < 4; k++)
            for (int i = 0; i < game->R; i++)
                for (int j = 0; j < game->C; j++)
                {
                    Vector2 current = {.x=j,.y=i};
                    Vector2 other = {.x=j+dirs[k].x,.y=i+dirs[k].y};
                    if(PositionExist(game,other))
                        if(game->tiles[IdFromVector(game,current)].value==game->tiles[IdFromVector(game,other)].value)
                            return true;
                }

        return false;
}

bool Compares(Game *game,int start, int end){
    switch (game->input.move)
    {
    case UP:
        return (start <= end);
        break;
    case DOWN:
        return (start >= end);
        break;
    case RIGHT:
        return (start >= end);
        break;
    case LEFT:
        return (start <= end);
        break;
    default:
        break;
    }
    exit(1);
}
bool PositionExist(Game* game, Vector2 position){
    if(position.x<game->C&&position.x>=0)
        if(position.y<game->R&&position.y>=0)
            return true;
    return false;
}
Vector2 PositionMax(Game* game, Vector2 current){
    //vypadá to dobře ? .. asi ne .. funguje to ? Celkem Jo!
    Vector2 last = current;
    switch (game->input.move)
    {    
    case UP:    
        for (int i = current.y; i >= 0; i--)
        {
            Vector2 v = {.x = current.x, .y=i-1};
            if(PositionExist(game,v)&&game->tiles[IdFromVector(game,v)].summed==0){
                if(game->tiles[IdFromVector(game,v)].value == game->tiles[IdFromVector(game,current)].value||game->tiles[IdFromVector(game,v)].value == 0)
                    last = v;
                else
                    break;
            }
                
        }
        return last;
        break;
    case DOWN:
        for (int i = current.y; i < game->R; i++)
        {
            Vector2 v = {.x = current.x, .y=i+1};
            if(PositionExist(game,v)&&game->tiles[IdFromVector(game,v)].summed==0){
                if(game->tiles[IdFromVector(game,v)].value == game->tiles[IdFromVector(game,current)].value||game->tiles[IdFromVector(game,v)].value == 0)
                    last = v;
                else
                    break; 
            }
                   
        }
        return last;
        break;
    case RIGHT:
        for (int i = current.x;i < game->C; i++)
        {
            Vector2 v = {.x = i+1, .y=current.y};
            if(PositionExist(game,v)&&game->tiles[IdFromVector(game,v)].summed==0){
                if(game->tiles[IdFromVector(game,v)].value == game->tiles[IdFromVector(game,current)].value||game->tiles[IdFromVector(game,v)].value == 0)
                    last = v;
                else
                    break;
            }
                
        }
        return last;
        break;
    case LEFT:
        for (int i = current.x;i >= 0; i--)
        {
            Vector2 v = {.x = i-1, .y=current.y};
            if(PositionExist(game,v)&&game->tiles[IdFromVector(game,v)].summed==0){
                if(game->tiles[IdFromVector(game,v)].value == game->tiles[IdFromVector(game,current)].value||game->tiles[IdFromVector(game,v)].value == 0)
                    last = v;
                else
                    break;
            }
                
        }
        return last;
        break;
    default:
        exit(1);
        break;
    }
    exit(1);
}
int IdFromVector(Game *game, Vector2 v){
    return game->C*v.y+v.x;
}
bool CheckWin(Game *game){
    for (int i = 0; i < game->tileCount; i++)
    {
        if(game->tiles[i].value==2048)
            return true;
    }
    return false;
}
