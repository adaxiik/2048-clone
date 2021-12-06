#include "../../include/game/input.h"

int InputHandle(Game *game, SDL_Event e){
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                return 1;
                break;
            case SDL_KEYDOWN:
                 switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        game->input.move=LEFT;
                        game->input.pressedKey = SDLK_LEFT;
                        break;
                    case SDLK_RIGHT:
                        game->input.move=RIGHT;
                        game->input.pressedKey = SDLK_RIGHT;
                        break;
                    case SDLK_UP:
                        game->input.move=UP;
                        game->input.pressedKey = SDLK_UP;
                        break;
                    case SDLK_DOWN:
                        game->input.move=DOWN;
                        game->input.pressedKey = SDLK_DOWN;
                        break;
                    case SDLK_a:
                        game->input.move=LEFT;
                        game->input.pressedKey = SDLK_a;
                        break;
                    case SDLK_d:
                        game->input.move=RIGHT;
                        game->input.pressedKey = SDLK_d;
                        break;
                    case SDLK_w:
                        game->input.move=UP;
                        game->input.pressedKey = SDLK_w;
                        break;
                    case SDLK_s:
                        game->input.move=DOWN;
                        game->input.pressedKey = SDLK_s;
                        break;
                    case SDLK_r:
                        game->input.pressedKey = SDLK_r;
                        NewGame(game);
                        break;
                    case SDLK_m:
                        game->input.pressedKey = SDLK_m;
                        if(!game->win)
                            game->ended=true;
                        break;
                    case SDLK_n:
                        game->input.pressedKey = SDLK_n;
                        if(!game->ended)
                            game->win=true;
                        break;
                    case SDLK_ESCAPE:
                        return 1;   
                        break;
                    default:
                        game->input.pressedKey = e.key.keysym.sym;
                        break;
                }
                break;

            case SDL_KEYUP:
                break;

            default:
                break;
        }
  }
  return 0;
}
