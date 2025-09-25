#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "gfx/gfx.h"
#include "cpu/cpu.h"
#include <SDL2/SDL.h>
uint8 keyboard[16];
//Timers, so basic they don't even need to be a thread
int delay_timer;
int sound_timer;

uint8 display[32][64];
char romToRead[20] = "../3-corax+.ch8";

SDL_Window *window;
SDL_Renderer *renderer;


int running;

int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    //Load Rom
    rom_t ROM = calloc(1,sizeof(rom_t));
    loadRom(romToRead,ROM);
    //Init CPU
    init_CPU(ROM);
    
    //Init gfx
    init_gfx();
    
    //Game Window
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH * SCALE , SCREEN_HEIGHT * SCALE,0,&window,&renderer);
    SDL_SetWindowPosition(window,200,200);
 
    running = 1;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
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
        }
        delay_timer--;
        sound_timer--;
        execute();
        draw();
    }

    return 0;
}

void ASSERT(int phrase){
    if(!phrase){
        printf("Error in assertion");
        exit(0);
    }
}
void loadRom(char* rom,rom_t newROM){
    FILE* f;
    f = fopen(rom,"rb");

    if(f == NULL){
        printf("Errore di lettura rom: %s",rom);
        exit(0);
    }
    
    fseek(f,0,SEEK_END);
    newROM -> dim = ftell(f);
    fseek(f,0,SEEK_SET);

    newROM->mem = calloc(sizeof(uint8), 4096); 

    fread(newROM->mem,sizeof(uint8),newROM->dim,f);
    
    fclose(f);
}

void HALT(){
    SDL_Quit();
}