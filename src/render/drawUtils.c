#include <SDL2/SDL_ttf.h>
#include "../../include/render/drawUtils.h"

//je to neoptimalitované, ale už se to používá jen pro vykreslování ostatního textu, tak to nechám tak
void DrawText(App* app,int x, int y,const char* text, int size , SDL_Color color,Scaling sizeScaling, SDL_bool center,SDL_bool lengthScaling){
    switch (sizeScaling)
    {
    case RELATIVETOTILE:
        size = (size*app->offsets.size)/100; //relative scaling
        break;
    case RELATIVETORESOLUTION:
        size = (size*app->offsets.min)/500;
        break;
    case ABSOLUTE:
        break;
    default:
        break;
    }
    
    if(lengthScaling)
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
    
    //SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color); 
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, color); //smoother

    SDL_Texture* message = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);
    SDL_Rect messRect;
    messRect.x = x;
    messRect.y = y;

    if(center){
        int w,h;
        TTF_SizeText(font, text, &w, &h);

        messRect.x = messRect.x-(w/2);
        messRect.y = messRect.y-(h/2);
    }

    SDL_QueryTexture(message, NULL, NULL, &messRect.w, &messRect.h);

    SDL_RenderCopy(app->renderer, message, NULL, &messRect);
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void DrawTextTile(App* app,int x, int y,int value){
    TileTexture t = GetTextureForValue(app,value);
    SDL_Rect messRect;
    messRect.x = x-(t.size.x/2);
    messRect.y = y-(t.size.y/2);
    SDL_QueryTexture(t.texture, NULL, NULL, &messRect.w, &messRect.h);

    SDL_RenderCopy(app->renderer, t.texture, NULL, &messRect);
}


SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *file)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
       fprintf(stderr, "SDL_IMG_Load: %s\n", SDL_GetError());
       exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


SDL_Color GetColor(int r,int g, int b,int a){
    SDL_Color c = {.r=r,.g=g,.b=b,.a=a};
    return c;
}
void DrawSquare(App* app, SDL_Rect rect, SDL_Color color,SDL_bool center){
    
    if(center){
        rect.x=rect.x-rect.w/2;
        rect.y=rect.y-rect.h/2;
    }
    //SDL_SetRenderDrawColor(app->renderer, color.r,color.g,color.b,color.a);;
    //SDL_RenderFillRect(app->renderer, &rect);
    SDL_SetTextureColorMod(app->squareTexture,color.r,color.g,color.b); //přebarvuje texturu
    SDL_SetTextureAlphaMod(app->squareTexture,color.a);
    SDL_RenderCopy(app->renderer,app->squareTexture,NULL,&rect);
        
}
Colors SetBackgroundColors(){
    Colors c;
    c._2 = GetColor(238, 228, 218, 255);
    c._4 = GetColor(237, 224, 200, 255);
    c._8 = GetColor(242, 177, 121, 255);
    c._16 = GetColor(245, 149, 99, 255);
    c._32 = GetColor(246, 124, 95, 255);
    c._64 = GetColor(246, 94, 59, 255);
    c._128 = GetColor(237, 207, 114, 255);
    c._256 = GetColor(237, 204, 97, 255);
    c._512 = GetColor(237, 200, 80, 255);
    c._1024 = GetColor(237, 197, 63, 255);
    c._2048 = GetColor(237, 194, 46, 255);
    return c;
}
Colors SetFontColors(){
    Colors c;
    c._2 = GetColor(119, 110, 101, 255);
    c._4 = GetColor(119, 110, 101, 255);
    c._8 = GetColor(249, 246, 242, 255);
    c._16 = GetColor(249, 246, 242, 255);
    c._32 = GetColor(249, 246, 242, 255);
    c._64 = GetColor(249, 246, 242, 255);
    c._128 = GetColor(249, 246, 242, 255);
    c._256 = GetColor(249, 246, 242, 255);
    c._512 = GetColor(249, 246, 242, 255);
    c._1024 = GetColor(249, 246, 242, 255);
    c._2048 = GetColor(249, 246, 242, 255);
    return c;
}
SDL_Color GetColorForValue(Colors pallete,int value){
    switch (value)
    {
    case 2:
        return pallete._2;
        break;
    case 4:
        return pallete._4;
        break;
    case 8:
        return pallete._8;
        break;
    case 16:
        return pallete._16;
        break;
    case 32:
        return pallete._32;
        break;
    case 64:
        return pallete._64;
        break;
    case 128:
        return pallete._128;
        break;
    case 256:
        return pallete._256;
        break;
    case 512:
        return pallete._512;
        break;
    case 1024:
        return pallete._1024;
        break;
    case 2048:
        return pallete._2048;
        break;
    default:
        return GetColor(69, 69, 69, 255); //debug color
        break;
    }
}

TileTexture GetTextureForValue(App* app, int value){
    switch (value)
    {
    case 2:
        return app->textures[0];
        break;
    case 4:
        return app->textures[1];
        break;
    case 8:
        return app->textures[2];
        break;
    case 16:
        return app->textures[3];
        break;
    case 32:
        return app->textures[4];
        break;
    case 64:
        return app->textures[5];
        break;
    case 128:
        return app->textures[6];
        break;
    case 256:
        return app->textures[7];
        break;
    case 512:
        return app->textures[8];
        break;
    case 1024:
        return app->textures[9];
        break;
    case 2048:
        return app->textures[10];
        break;
    default:
        break;
    }
    exit(1);
}