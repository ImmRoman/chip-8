#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "../main.h"
#include "../gfx/gfx.h"

extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern int sound_timer;
extern int delay_timer;
extern int keyboard[16];
extern uint8 display[32][64];

uint8 memory[0xFFF],memSize;
uint8 stack[0xFFF];
uint16 SP;
uint8 registers[0xF];
uint16 PC;

uint16 I, N, NN;
uint8 drawMask, drawFlag;

void init_CPU(rom_t rom)
{
    PC = 0x200;
    for(int i = 0x0 ; i<=0xF; i++){
        registers[i] = 0;
    }
    memcpy(&memory[0x200],rom->mem,rom->dim);
    memSize = 0x200 + rom->dim;
}

void execute(){
    uint8 X,Y,O;
    uint16 cmd = (memory[PC]<<8) | (memory[PC+1]);

    printf("\r%x - ADDR: %x   ",cmd,PC);
    fflush(stdout);

    switch (cmd>>12)
    {
    case 0x0:
        //I will ignore 0x0NNN
        if(cmd==0x00E0){
            //Clear screen
            FillBackground();
        }
        else{
            //return from subroutine
            SP -= 2;
            PC = stack[SP] << 8 + stack[SP+1]; //Big Eldian
        }
        break;

    case 0x1:
        //Jump to address 1NNN
        PC=cmd & 0xFFF;
        return;
    break;
    case 0x2:
        //Call subroutine at 2NNN
        PC+=2;          //I store the address of the next instruction
        stack[SP] = PC >> 8;
        stack[SP+1] = PC & 0xFF;
        SP += 2;
        PC = (cmd & 0xFFF);
        // We don't want to increment PC after a jump
        return; 
    break;
    case 0x3:
        //3XNN	Cond	if (Vx == NN)
        X = (cmd & 0xF00)>>8;
        if(registers[X]==(cmd&0xFF)){
            PC+=2; //Since at the end of the instructions I stil have to increase the PC
        }
    break;
    case 0x4:
        //4XNN	Cond	if (Vx != NN)
        X = (cmd & 0xF00)>>8;
        if(registers[X]!=(cmd&0xFF)){
            PC+=2; //Since at the end of the instructions I stil have to increase the PC
        }
    break;
    case 0x5:
        //5XY0	Cond	if (Vx == Vy)
        X = (cmd & 0xF00)>>8;
        Y = (cmd & 0xF0)>>4;
        if(registers[X]==registers[Y]){
            PC+=2;
        }
    case 0x6:
        //6XNN	Const	Vx = NN
        X = (cmd & 0xF00)>>8;
        registers[X]=cmd & 0xFF;
    break;
    case 0x7:
        //7XNN	Const	Vx += NN
        X = (cmd & 0xF00)>>8;
        registers[X]+=cmd & 0xFF;
    break;
    case 0x8:
        //8XYO
        X = (cmd & 0xF00)>>8;
        Y = (cmd & 0xF0)>>4;
        O = (cmd & 0xF);

        switch (O)
        {
        case 0:
            registers[X] = registers[Y];
            break;

        case 1:
            registers[X] = registers[X] | registers[Y];
        break;

        case 2:
        registers[X] = registers[X] & registers[Y];
        break;

        case 3:
            registers[X] = registers[X] ^ registers[Y];
        break;
        
        case 4:
            registers[X] = registers[X] + registers[Y];
        break;

        case 5:
            registers[X] = registers[X] - registers[Y];
        break;

        case 6:
            registers[0xF]=registers[X] & 0x1;
            registers[X] = registers[X] >> 1;
        break;

        case 7:
            registers[0xF] = registers[Y] >= registers[X] ? (registers[0xF] = 1) : (registers[0xF] = 0);
            registers[X] = registers[Y] - registers[X];
        break;

        case 0xE:
            registers[0xF]=(registers[X] & 0x80) >> 7;
            registers[X] = registers[X] << 1;
        break;

        default:
            printf("ERROR: OP CODE %X NOT RECOGNIZED",cmd);
            HALT();
            break;
        }
    break;

    case 0x9:
        if(registers[X]!=registers[Y])
            PC+=2;
    break;

    case 0xA:
        I = cmd & 0xFFF;
    break;

    case 0xB:
        PC=registers[0]+ (cmd & 0xFFF);
    break;
    
    case 0xC:
        X = (cmd >> 8) & 0xF;
        NN = cmd & 0xFF;
        registers[X] = (rand() % 256) & NN;
    break;

    case 0xD:
        X = (cmd >> 8) & 0xF;
        Y = (cmd >> 4) & 0xF;
        N = cmd & 0xF;
        //Display draw(Vx, Vy, N rows) 
        int flip = 0;
        uint8 oldPixel = 0, sprite = 0, value = 0;

        for (int i = 0; i < N; i++){
            //memory[I + i] = 0xFF; //testa lo switch completo dei colori
            sprite = memory[I + i];
            for (int j = 0; j < 8; j++)
            {
                oldPixel = display[(registers[Y] + i)%32][registers[X + j] % 64];
                value = (0x80>>j) & sprite;
                if(value){
                    display[(registers[Y] + i) % 32][(registers[X] + j) % 64] ^= 1;
                    flip = 1;
                    if(oldPixel){
                        registers[0xF] = 1;
                    }
                }
                else
                    display[(registers[Y] + i) % 32][(registers[X] + j) % 64] ^= 0;
            }
        }
        if(!flip) 
            registers[0xF] = 0;
        else set_DrawFlag();
    
    break;

    case 0xE:
        X = (cmd & 0xF00)>>8;

        if(cmd & 0xFF == 0x9E){
            if(keyboard[X])
                PC+=2;
            break;
        }

        if(cmd & 0xFF == 0x9E){
            if(!keyboard[X])
                PC+=2;
            break;
        }
        printf("ERROR: OP CODE %X NOT RECOGNIZED",cmd);
    break;

    case 0xF:
        X = (cmd & 0xF00)>>8;
        NN = (cmd & 0xFF);

        switch (NN)
        {
        case 0x07:
            X = (cmd >> 8) & 0xF;
            registers[X]=delay_timer;
            break;
        
        case 0x0A:
            for(int i=0;i<16;i++){
                if(keyboard[i])
                    registers[X]=i;
            }
        break;

        case 0x15:
            X = (cmd >> 8) & 0xF;
            delay_timer=registers[X];
        break;

        case 0x18:
            X = (cmd >> 8) & 0xF;
            sound_timer=registers[X];
        break;

        case 0x1E:
            I+=registers[X];
        break;

        case 0x29:
            X = (cmd >> 8) & 0xF;
            I = X * 5;
        break;

        case 0x33:
            //TODO: BCD
            X = (cmd >> 8) & 0xF;
            memory[I] = registers[X] / 100;
            memory[I+1] = (registers[X] % 100) / 10;
            memory[I+2] = registers[X] % 10;

        break;

        case 0x55:
            X = (cmd >> 8) & 0xF;
            for(int i=0x0; i<=X; i++){
                memory[I+i] = registers[i];
            }
        break;

        case 0x65:
            X = (cmd >> 8) & 0xF;
            for(int i=0x0; i<=X; i++){
                registers[i] = memory[I+i];
            }

        break;
        default:
            break;
        }
    

    break;
    default:
        printf("ERROR: OP CODE %X NOT RECOGNIZED",cmd);
        HALT();
        break;
    }
    //Go to next Instruction
    PC+=2;
}