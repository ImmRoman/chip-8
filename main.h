#define SCREEN_WIDTH 64 
#define SCREEN_HEIGHT 32 
#define SCALE 20
#define SPEED 10

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef struct{
    uint8* mem;
    uint16 dim;
} rom_s,*rom_t;


void FillBackground();
void drawSquare(int x,int y,int set);
void HALT();
void loadRom(char* rom,rom_t newROM);
void ASSERT(int phrase);