#include "graphics.h"

#include "globals.h"

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
#define VIOLT 0x8080FF
#define WHITE 0xFFFFFF
#define LIGHTPURPLE 0xBA68C8
#define DARKPURPLE 0x9C27B0
#define RED_R         0xE91E63
int changer=0;
//sprites as const chars
const char pacman [121] = {
    'B','B','B','Y','Y','Y','B','B','B','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','Y','Y','Y','Y','B','Y','Y','B','B','B',
    'Y','Y','Y','Y','Y','Y','Y','B','B','B','B',
    'Y','Y','Y','Y','Y','Y','Y','B','B','B','B',
    'Y','Y','Y','Y','Y','Y','Y','B','B','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','B','B','Y','Y','Y','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    };
   
const char pacmanother [121] ={
    'B','B','B','Y','Y','Y','B','B','B','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','Y','Y','Y','Y','B','Y','Y','B','B','B',
    'Y','Y','Y','Y','Y','Y','Y','Y','Y','B','B',
    'Y','Y','Y','Y','Y','Y','Y','Y','Y','B','B',
    'Y','Y','Y','Y','Y','Y','Y','Y','Y','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','Y','Y','Y','Y','Y','Y','Y','B','B','B',
    'B','B','B','Y','Y','Y','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    };   
const char honeydrop[121] = {
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','Y','Y','B','B','B','B','B','B',
     'B','B','Y','Y','Y','Y','Y','B','B','B','B',
     'B','B','Y','Y','Y','Y','Y','B','B','B','B',
     'B','B','Y','Y','Y','Y','Y','B','B','B','B',
     'B','B','Y','Y','Y','Y','Y','B','B','B','B',
     'B','B','B','Y','Y','Y','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     };
const char poisondrop[121]={
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','R','R','B','B','B','B','B','B',
     'B','B','R','R','R','R','R','B','B','B','B',
     'B','B','R','R','R','R','R','B','B','B','B',
     'B','B','R','R','R','R','R','B','B','B','B',
     'B','B','R','R','R','R','R','B','B','B','B',
     'B','B','B','R','R','R','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
     'B','B','B','B','B','B','B','B','B','B','B',
    };
const char ghost[121] ={
    'B','B','B','V','V','V','B','B','B','B','B',
    'B','V','V','V','V','V','V','V','B','B','B',
    'B','V','B','W','V','B','W','V','B','B','B',
    'B','V','W','W','V','W','W','V','V','B','B',
    'B','V','V','V','V','V','V','V','V','B','B',
    'V','V','V','V','V','V','V','V','V','B','B',
    'V','V','V','V','V','V','V','V','V','B','B',
    'V','V','V','V','V','V','V','V','V','B','B',   
    'V','B','B','B','V','B','B','B','V','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    };  
const char plant [121] = {
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','G','B','G','B','G','G','B','B',
    'B','B','G','G','G','G','G','G','G','G','B',
    'B','G','G','G','G','G','G','G','G','G','B',
    'G','G','G','G','G','G','G','G','G','B','B',
    'B','G','G','G','G','G','G','G','G','G','B',
    'G','G','G','G','G','G','G','G','G','G','B',
    'G','G','G','G','G','G','G','G','G','G','G',
    };    
const char portal [121] = {
    'P','P','P','P','P','P','Z','Z','Z','Z','Z',
    'P','P','P','P','P','P','Z','Z','Z','Z','Z',
    'P','P','P','P','P','P','P','P','Z','Z','Z',
    'P','P','P','P','P','P','P','P','Z','Z','Z',
    'Z','Z','P','P','P','P','Z','Z','Z','Z','Z',
    'Z','Z','P','P','P','P','Z','Z','Z','Z','Z',
    'Z','Z','P','P','Z','Z','Z','Z','Z','Z','Z',
    'Z','Z','P','P','Z','Z','Z','Z','Z','Z','Z',
    'P','P','P','P','P','Z','Z','P','P','P','Z',
    'P','P','P','P','P','Z','Z','P','P','P','Z',
    'P','P','P','P','P','P','P','P','P','P','Z',
    };    
const char key [121] ={
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','Y','Y','Y','Y','B',
    'B','Y','Y','Y','Y','Y','Y','W','W','Y','B',
    'B','Y','Y','Y','Y','Y','Y','W','W','Y','B',
    'B','Y','B','Y','B','B','Y','Y','Y','Y','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    'B','B','B','B','B','B','B','B','B','B','B',
    }; 
const char door [121] ={
    'D','D','D','D','D','D','D','D','D','D','D',
    'D','D','D','D','D','D','D','D','D','D','D',
    'D','D','D','D','D','D','D','D','D','D','D',
    'D','D','D','D','D','D','D','D','D','B','D',
    'D','D','D','D','D','D','D','D','D','B','D',
    'D','D','D','D','D','D','D','D','D','B','D',
    'D','D','D','D','D','D','D','D','D','B','D',
    'D','D','D','D','D','D','D','D','D','B','D',
    'D','D','D','D','D','D','D','D','D','D','D',
    'D','D','D','D','D','D','D','D','D','D','D',
    'D','D','D','D','D','D','D','D','D','D','D',
    };  
//draw functions
    
void draw_player(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    if(changer==0){
        changer=1;
        draw_img(u,v, pacman);
    }
    else if(changer==1){
        changer=0;
        draw_img(u,v, pacmanother);
    }    
}


void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'V') colors[i] = VIOLT;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == 'P') colors[i] = LIGHTPURPLE;
        else if (img[i] == 'Z') colors [i] = DARKPURPLE;
        else if (img[i] == 'R') colors[i]= RED_R;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    draw_img(u, v, plant);
}
void draw_ghost(int u, int v){
    draw_img(u, v, ghost);
}
void draw_portal(int u, int v){
    draw_img(u, v, portal);
}
void draw_honey(int u, int v){
    draw_img(u, v, honeydrop);
}
void draw_poison(int u, int v){
    draw_img(u, v, poisondrop);
}
void draw_door(int u, int v){
    draw_img(u, v, door);
}
void draw_key(int u, int v){
    draw_img(u,v, key);
}
void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);
    
    // Add other status info drawing code here
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}
void draw_gameover()
{   
    uLCD.filled_rectangle(0,0, 127,  127, BLACK); // Top
    uLCD.text_bold(ON);
    uLCD.text_string("Game Over!", 4, 1, FONT_7X8, WHITE);
    uLCD.text_string("Shadman Ahmed",2, 7, FONT_7X8, WHITE);
}
void draw_gamestart()
{
    uLCD.filled_rectangle(0,0,127,127,BLACK);
    uLCD.text_bold(ON);
    uLCD.text_string("Lost Pacman",3,1,FONT_7X8,WHITE);
    uLCD.text_string("HELP PACMAN!",2,7,FONT_7X8,WHITE);
    uLCD.text_string("GET HOME",5,9,FONT_7X8,WHITE);
    uLCD.text_string("Press any button",1,14,FONT_7X8,WHITE);
    uLCD.text_string("to begin.",1,15,FONT_7X8,WHITE);
}
