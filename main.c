#include "main.h"
#include <SDL2/SDL.h>
#include <stdio.h>



int sbuffo=0;

SDL_Window *window;
SDL_Renderer *renderer;
int running,speed = SPEED;
void draw();

int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    //Game Window
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH*SCALE , SCREEN_HEIGHT*SCALE,0,&window,&renderer);
    SDL_SetWindowPosition(window,200,200);
    draw();
 

    running = 1;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEMOTION:
                    //printf("We got a motion event.\n");
                    //printf("Current mouse position is: (%d, %d)\n", event.motion.x, event.motion.y);
      
                    break;

                case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_1) keyboard[0x1]=0;
                if(event.key.keysym.sym == SDLK_2) keyboard[0x2]=0;
                if(event.key.keysym.sym == SDLK_3) keyboard[0x3]=0;
                if(event.key.keysym.sym == SDLK_4) keyboard[0xC]=0;
                if(event.key.keysym.sym == SDLK_q) keyboard[0x4]=0;
                if(event.key.keysym.sym == SDLK_w) keyboard[0x5]=0;
                if(event.key.keysym.sym == SDLK_e) keyboard[0x6]=0;
                if(event.key.keysym.sym == SDLK_r) keyboard[0xD]=0;
                if(event.key.keysym.sym == SDLK_a) keyboard[0x7]=0;
                if(event.key.keysym.sym == SDLK_s) keyboard[0x8]=0;
                if(event.key.keysym.sym == SDLK_d) keyboard[0x9]=0;
                if(event.key.keysym.sym == SDLK_f) keyboard[0xE]=0;
                if(event.key.keysym.sym == SDLK_z) keyboard[0xA]=0;
                if(event.key.keysym.sym == SDLK_x) keyboard[0x0]=0;
                if(event.key.keysym.sym == SDLK_c) keyboard[0xB]=0;
                if(event.key.keysym.sym == SDLK_v) keyboard[0xF]=0;
                break;


                case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_1) keyboard[0x1]=1;
                if(event.key.keysym.sym == SDLK_2) keyboard[0x2]=1;
                if(event.key.keysym.sym == SDLK_3) keyboard[0x3]=1;
                if(event.key.keysym.sym == SDLK_4) keyboard[0xC]=1;
                if(event.key.keysym.sym == SDLK_q) keyboard[0x4]=1;
                if(event.key.keysym.sym == SDLK_w) keyboard[0x5]=1;
                if(event.key.keysym.sym == SDLK_e) keyboard[0x6]=1;
                if(event.key.keysym.sym == SDLK_r) keyboard[0xD]=1;
                if(event.key.keysym.sym == SDLK_a) keyboard[0x7]=1;
                if(event.key.keysym.sym == SDLK_s) keyboard[0x8]=1;
                if(event.key.keysym.sym == SDLK_d) keyboard[0x9]=1;
                if(event.key.keysym.sym == SDLK_f) keyboard[0xE]=1;
                if(event.key.keysym.sym == SDLK_z) keyboard[0xA]=1;
                if(event.key.keysym.sym == SDLK_x) keyboard[0x0]=1;
                if(event.key.keysym.sym == SDLK_c) keyboard[0xB]=1;
                if(event.key.keysym.sym == SDLK_v) keyboard[0xF]=1;

                break;
                default:

                    break;
            }
            SDL_Delay(speed);
            delay_timer--;
            sound_timer--;
            // execute(PC)
            //PC+=2
            draw();
        }
    }

    return 0;
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

void HALT(){
    SDL_Quit();
}