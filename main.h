
#define SCREEN_WIDTH 64 
#define SCREEN_HEIGHT 32 
#define SCALE 20
#define SPEED 5

typedef unsigned char uint8;
void FillBackground();
void drawSquare(int x,int y,int set);
void HALT();
uint8 keyboard[16];
//Timers, so basic they don't even need to be a thread
int delay_timer;
int sound_timer;
uint8 display[32][64];

