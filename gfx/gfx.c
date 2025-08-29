#include "../main.h"
#include <SDL2/SDL.h>
#include <stdio.h>

extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern uint8 display[32][64];
int dFlag;

void init_gfx(){
    dFlag=0;
}
void set_DrawFlag(){
    dFlag=1;
}
void clear_DrawFlag()
{
    dFlag = 0;
}
int get_DrawFlag()
{
   return dFlag;
}
void FillBackground(){
    SDL_SetRenderDrawColor(renderer, 112, 44, 255, 0);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderPresent(renderer);
}
void drawSquare(int x,int y,int set){
    SDL_Rect rect={x,y,SCALE,SCALE};
    if (set)
        SDL_SetRenderDrawColor(renderer,255, 255, 255,0);
    else 
    SDL_SetRenderDrawColor(renderer,0, 0, 0 ,0);
    
    SDL_RenderFillRect(renderer,&rect);
}

void draw(){
    // Do I have to draw?
    if(!dFlag)
        return;
    drawSquare(11, 11, 1);

    // 8 pixel wide sprites
    for(int x=0;x<64;x++){
        for(int y=0;y<32;y++){
            drawSquare(x,y,display[y][x]);
            }
        }
    SDL_RenderPresent(renderer);
    clear_DrawFlag();
}