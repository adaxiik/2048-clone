#include "../../include/render/draw.h"
#include "../../include/render/drawUtils.h"
#include "../../include/render/animate.h"
void RenderGame(App* app,Game* game){

    DrawBackGround(app);

    for (int i = 0; i < game->tileCount; i++)
        if(game->animations[i].animating&&(game->animations[i].type==MOVETILE||game->animations[i].type==STILL))
            DrawMovingTile(app,game,i);

    for (int i = 0; i < game->tileCount; i++)
    {   
        if(game->animations[i].animating && game->animations[i].type!=NEWTILE)
            continue;
            
        AnimateTile(app,game,i);
        DrawTile(app,game,i);
    }
 
    DrawScore(app,game);

    if(game->ended)
        DrawRetry(app,game);
    if(game->win)
        DrawWin(app,game);

    SDL_RenderPresent(app->renderer);
}

void DrawBackGround(App *app){    
    //bg
    SDL_SetRenderDrawColor(app->renderer, 186, 171, 158, 255); //barva pozadí
    SDL_RenderClear(app->renderer);

    SDL_Color c = {.r=202,.g=190,.b=178,.a=255}; //barva prázdného čtverce
    
    SDL_Rect t = {.h=app->offsets.firstPosition.h,.w=app->offsets.firstPosition.w,.x=app->offsets.firstPosition.x,.y=app->offsets.firstPosition.y};
    for (int i = 0; i < app->RC.x; i++)
    {
        for (int j = 0; j < app->RC.y; j++)
        {
            DrawSquare(app,t,c,SDL_TRUE);
            t.x+=app->offsets.size;
        } 
        t.x = (app->offsets.center.x-app->offsets.min/2)+app->offsets.size/2; 
        t.y+=app->offsets.size;
    }
}
void BakeFonts(App *app){
    int values[] = {2,4,8,16,32,64,128,256,512,1024,2048};
    int size = (50*app->offsets.size)/100;

    for (int i = 0; i < 11; i++)
    {
        if(app->textures[i].texture!=NULL)
            SDL_DestroyTexture(app->textures[i].texture);

        char text[16]={0};
        sprintf(text,"%d",values[i]);
        switch (strlen(text))
        {
        case 1:
            size = size;
            break;
        case 2:
            size = size*0.95;
            break;
        case 3:
            size = size*0.90;
            break;
        case 4:
            size = size*0.7;
            break;    
        default:
            size = size*0.6;
            break;
        }
        //https://github.com/intel/clear-sans
        TTF_Font* font = TTF_OpenFont("assets/fonts/ClearSans-Bold.ttf", size);
        if(!font) {
            printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
            exit(1);
        }
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, GetColorForValue(app->fontColors,values[i])); //smoother
        if(!surfaceMessage){
            fprintf(stderr, "[ERROR] Surface: %s\n", SDL_GetError());
            exit(1);
        }
        app->textures[i].texture = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);
        
        int w,h;
        TTF_SizeText(font, text, &w, &h);
        app->textures[i].size.x=w;
        app->textures[i].size.y=h;
        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(font);
    }   
}
void CalculateOffsets(App *app){
    int R = app->RC.x;
    int C = app->RC.y;
    int perSizeR = app->resolution.y/R;
    int perSizeC = app->resolution.x/C;
    if(R>C)   //hledá se menší strana, podle které se to bude centrovat
        app->offsets.min = app->resolution.y-(app->resolution.y*0.1) < perSizeC*R ?app->resolution.y-(app->resolution.y*0.1):app->resolution.x+perSizeC;
    else if (C>R)
        app->offsets.min = app->resolution.x < perSizeR*C? app->resolution.x : app->resolution.y+perSizeR*2;
    else
        app->offsets.min = app->resolution.x>app->resolution.y-(app->resolution.y*0.05)?app->resolution.y-(app->resolution.y*0.05):app->resolution.x;
    //mess
    app->offsets.min = app->offsets.min - (app->offsets.min*0.05); //offset od kraje okna
    app->offsets.size = app->offsets.min/(R>C?R:C); //velikost čtverce
    //offset pro vycentrování hracího pole různé velikosti R C
    app->offsets.offset.x = R>C?(R-C)*(app->offsets.size/2):0 ;
    app->offsets.offset.y =(C>R?(C-R)*( app->offsets.size/2):0)+(app->resolution.y*0.03);
    
    //střed ze které se počítá první pozice
    app->offsets.center.x = (app->resolution.x/2)+app->offsets.offset.x;
    app->offsets.center.y = (app->resolution.y/2)+app->offsets.offset.y;

    //první pozice
    app->offsets.pos.x = app->offsets.center.x-app->offsets.min/2;
    app->offsets.pos.y = app->offsets.center.y-app->offsets.min/2;

    app->offsets.firstPosition.h = app->offsets.size*0.95;
    app->offsets.firstPosition.w = app->offsets.size*0.95;
    app->offsets.firstPosition.x = app->offsets.pos.x+app->offsets.size/2;
    app->offsets.firstPosition.y = app->offsets.pos.y+app->offsets.size/2;
}
void DrawTile(App *app,Game *game, int id){
    if(game->tiles[id].value==0)
        return;

    SDL_Rect t = {.h=app->offsets.firstPosition.h,.w=app->offsets.firstPosition.w,.x=app->offsets.firstPosition.x,.y=app->offsets.firstPosition.y};
    t.x = t.x + app->offsets.size*game->tiles[id].x;
    t.y = t.y + app->offsets.size*game->tiles[id].y;
    if(game->animations[id].animating){
        t.h = t.h * game->animations[id].sizeModifier;
        t.w = t.w * game->animations[id].sizeModifier;
    }    
    DrawSquare(app,t,GetColorForValue(app->backgroundColors,game->tiles[id].value),SDL_TRUE);

    DrawTextTile(app,t.x,t.y,game->tiles[id].value);
               
}

void DrawMovingTile(App *app, Game *game, int id){
    AnimateTile(app,game,id);
    SDL_Rect o = {.h=app->offsets.firstPosition.h,.w=app->offsets.firstPosition.w,.x=app->offsets.firstPosition.x,.y=app->offsets.firstPosition.y};
    SDL_Rect t = {.h=app->offsets.firstPosition.h,.w=app->offsets.firstPosition.w,.x=app->offsets.firstPosition.x,.y=app->offsets.firstPosition.y};
    
    o.x = o.x + app->offsets.size*game->tiles[id].x;
    o.y = o.y + app->offsets.size*game->tiles[id].y;

    t.x = t.x + app->offsets.size*game->animations[id].targetTile.x;
    t.y = t.y + app->offsets.size*game->animations[id].targetTile.y;

    o.x = o.x + game->animations[id].XposModifier;
    o.y = o.y + game->animations[id].YposModifier;
    
    if(game->animations[id].type==MOVETILE)  
        switch (game->animations[id].move)
        {
        case UP:
            if(o.y<t.y){
                DisableAnimations(game);
                o.y=t.y;
            }
            break;
        case DOWN:
            if(o.y>t.y){
                DisableAnimations(game);
                o.y=t.y;
            }
            break;
        case RIGHT:
            if(o.x>t.x){
                DisableAnimations(game);
                o.x=t.x;
            }
            break;
        case LEFT:
            if(o.x<t.x){
                DisableAnimations(game);
                o.x=t.x;
            }
            break;
        default:
            break;
        } 
    
    DrawSquare(app,o,GetColorForValue(app->backgroundColors,game->animations[id].originalValue),SDL_TRUE);
    if(game->animations[id].originalValue!=0){
        DrawTextTile(app,o.x,o.y,game->animations[id].originalValue);
    }
}
void DrawScore(App *app, Game *game){
    char txt[128]={0};
    sprintf(txt,"Score: %d",game->score);
    DrawText(app,app->resolution.x/2,app->resolution.y*0.035,txt,25,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE); 
}

void DrawRetry(App *app, Game *game){
    SDL_Color c =  {.r=255,.g=255,.b=255,.a=185};
    SDL_Rect r = {.x=-50,.y=-50,.w=app->resolution.x+100,.h=app->resolution.y+100};
    DrawSquare(app,r,c,SDL_FALSE);

    DrawText(app,app->resolution.x/2,app->resolution.y*0.3,"Game over!",80,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE);

    char score[64]={0};
    sprintf(score,"%d",game->score);
    DrawText(app,app->resolution.x/2,app->resolution.y/2,score,70,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE);

    DrawText(app,app->resolution.x/2,app->resolution.y*0.8,"Press R to restart!",50,app->fontColors._2,RELATIVETORESOLUTION, SDL_TRUE,SDL_FALSE);

}

void DrawWin(App *app, Game *game){
    SDL_Color c =  {.r=237,.g=194,.b=46,.a=180};
    SDL_Rect r = {.x=-50,.y=-50,.w=app->resolution.x+100,.h=app->resolution.y+100};
    DrawSquare(app,r,c,SDL_FALSE);

    DrawText(app,app->resolution.x/2,app->resolution.y*0.3,"You Win!",80,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE);

    char score[64]={0};
    sprintf(score,"%d",game->score);
    DrawText(app,app->resolution.x/2,app->resolution.y/2,score,70,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE);

    DrawText(app,app->resolution.x/2,app->resolution.y*0.8,"Press R to restart!",50,app->fontColors._2,RELATIVETORESOLUTION,SDL_TRUE,SDL_FALSE);

}