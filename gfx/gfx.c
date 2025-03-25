#include "../main.h"
#include <SDL2/SDL.h>
#include <stdio.h>

extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern uint8 display[32][64];

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
    SDL_RenderPresent(renderer);

}
void draw(){
    //My display is organized as a bit array
    uint8 drawMask;
    for(int x=0;x<8;x++){
        for(int y=0;y<32;y++){
            drawMask=0x80;
            for (int b=0;b<8;b++){
                if(display[y][x]&drawMask)
                    drawSquare(x*SCALE + b * SCALE,y*SCALE,1);
                else drawSquare(x*SCALE + b * SCALE,y*SCALE,0);
                drawMask=drawMask>>1;
            }
        }
    }
}