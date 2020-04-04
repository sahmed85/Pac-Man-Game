#include "speech.h"

#include "globals.h"
#include "hardware.h"
int scrollButton=0;
/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0,100,127,127,WHITE);
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(0,100,127,127, BLACK);
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
    uLCD.line(0, 9, 127, 9, GREEN);
}

void draw_speech_line(const char* line, int which)
{
    if(which==TOP){
        uLCD.locate(1,13);
        uLCD.printf(line);   
    }
    else if(which==BOTTOM){
        uLCD.locate(1,14);
        uLCD.printf(line);
    }
}

int speech_bubble_wait(GameInputs inputs)
{
    if(inputs.b2 == 0 && scrollButton == 0)
    {
        scrollButton = 1;
        return 0;
    }
    else if(inputs.b2 == 1 && scrollButton == 1)
    {
        scrollButton = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

void speech(const char* line1, const char* line2)
{
    int waitfor = 1;
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    //speech_bubble_wait();
    while(waitfor==1){
        if(speech_bubble_wait(read_inputs()))
        {
            waitfor = 0;
        }   
    }
    erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
}
