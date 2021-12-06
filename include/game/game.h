#pragma once
#include <stdbool.h>
typedef enum {NUL, UP, DOWN, RIGHT, LEFT} Move;
typedef enum {NEWTILE,MOVETILE,HIDE,STILL} AnimationType;

typedef struct{
    int x;
    int y;
}Vector2;

typedef struct{
    Vector2 resolution;
    Vector2 RC;
}Settings;

typedef struct{
    int startX;
    int endX;
    int stepX;
    int startY;
    int endY;
    int stepY;
}MoveData;



typedef struct{
    Move move;
    int pressedKey; //on to asi není vyloženě int, ale postačí to 
    Vector2 mouse;
}Input;

typedef struct{
    bool summed;
    int value;
    int x;
    int y;
}Tile;

typedef struct{
    bool animating;
    AnimationType type;
    Move move;
    float sizeModifier;
    float XposModifier;
    float YposModifier;
    int originalValue;
    Vector2 targetTile;    
}Animation;


typedef struct
{
    int score;
    Tile* tiles;
    int tileCount;
    int R;
    int C;
    Input input;
    bool ended;
    bool win;
    Animation * animations;
}Game;
void PlayGame(Game* game);
Game *GameConstructor(int R, int C);
void GameDeconstructor(Game* game);
void MakeMove(Game *game, MoveData data);
void NewGame(Game* game);
void GenerateNewTile(Game* game);
void AnimationSetter(Game *game,int id,AnimationType type, Vector2 targetTile);
void DisableAnimations(Game *game);