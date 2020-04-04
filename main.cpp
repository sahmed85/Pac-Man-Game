// NAME: SHADMAN AHMED
// ECE 2035
// 04/17/19
// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include "Speaker.h"

//Global Variables
GameInputs in;
int action;
int update;
int bt1=0;
int bt2=0;
int bt3=0;
int talked=0;
int goPortal=0;
int mapswitch=0;

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
int main ();
//speaker code
Speaker gSpeakerOut(p26);
void Sample_timer_interrupt(void)
{
    // Call speaker function to play next value
    gSpeakerOut.PlayNextValue();
}

//
/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    int drop;
    int health;
    int gamestate;
    int om;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_ 1
#define MENU_ 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define TALK_NPC 7
#define NEAR_PORTAL 8
#define NEAR_DOOR 9
int get_action(GameInputs inputs)
{   //check and see if a move in that compass using NSEW in map.h direction is possible
    MapItem* getNorth = get_north(Player.x,Player.y);
    MapItem* getSouth = get_south(Player.x,Player.y);
    MapItem* getEast = get_east(Player.x,Player.y);
    MapItem* getWest = get_west(Player.x,Player.y);
    
    if((inputs.ay <= -0.5) && (getNorth->walkable || Player.om==1)){
        return GO_UP;   
    }
    else if((inputs.ay >= 0.5)&&(getSouth->walkable || Player.om==1)){
        return GO_DOWN;
    }
    else if((inputs.ax <= -0.5)&& (getWest->walkable || Player.om==1)){
        return GO_LEFT;
    }
    else if((inputs.ax >= 0.5)&& (getEast->walkable || Player.om==1)){
        return GO_RIGHT;
    }
    else if((getNorth->type==NPC || getSouth->type==NPC || getEast->type==NPC || getWest->type==NPC) && inputs.b2==0){
        return TALK_NPC;   
    }
    else if((getNorth->type==PORTAL || getSouth->type==PORTAL || getEast->type==PORTAL || getWest->type==PORTAL)&& inputs.b2==0 && goPortal==1){
        return NEAR_PORTAL;   
    }
    else if((getNorth->type==DOOR || getSouth->type==DOOR || getEast->type==DOOR || getWest->type==DOOR)&& inputs.b2==0){
        return NEAR_DOOR;
    } 
    return NO_ACTION;
}
//button function for making it work properly p21,p22,p23
//where b1 is omnipotent, b2 is action button and b3 is extra button that can be aserted for others 
int button_checker(GameInputs inputs){
    if(inputs.b1==0 && bt1==0){
    
        bt1=1;
    }
    if(inputs.b1==1 && bt1==1){
        Player.om= !Player.om;
        pc.printf("Om Value: %d\t",Player.om);
        bt1=0;
        return 1;
    }
    if(inputs.b2==0 && bt2==0){
    
        bt2=1;
    }
    if(inputs.b2==1 && bt2==1){
        bt2=0;
        return 1;
    }
    if(inputs.b3==0 && bt3==0){
    
        bt3=1;
    }
    if(inputs.b3==1 && bt3==1){
        bt3=0;
        return 1;
    }
}

void cleanup(){
    MapItem* this_location = get_here(Player.x,Player.y);
    if(this_location->type==HONEY){
        deleteDrop(Player.x,Player.y);
        Player.drop++;
    }
    else if(this_location->type==POISON){
        deleteDrop(Player.x,Player.y);
        Player.health--; 
    }
    else if(this_location->type==KEY){
        deleteDrop(Player.x,Player.y);
        Player.has_key=1;
    }      
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP: 
            Player.y = Player.y+1;
            return FULL_DRAW;
            //break;
        
        case GO_LEFT:   
            Player.x = Player.x-1;
            return FULL_DRAW;
            //break;            
        
        case GO_DOWN:   
            Player.y = Player.y-1;
            return FULL_DRAW;
            //break;
        
        case GO_RIGHT:  
            Player.x = Player.x+1;
            return FULL_DRAW;
            //break;
        
        case TALK_NPC: 
            if(talked==0){
            speech("Hello PacMan","You are lost!");
            speech("I am THE ghost","I will help!");
            speech("To return home", "you need to");
            speech("collect 5 honey","drops for me!");
            speech("Beaware of the", "poisonous drop.");
            speech("Enter the portal","below me to get");
            speech("the drops!","Return to me with");
            speech("all the drops","in the portal.");
            speech("","And I will give");
            speech("you the key to", "return to");
            speech("PacWorld","Good Luck!");
            talked = 1;
            goPortal=1;
            }
            else if(talked==1 && Player.drop<5){//&&honeydrop<5 then: you dont have all the honeydrops?
            speech("You still don't have","enough HoneyDrops!");
            }
            else if(talked==1 && Player.drop>=5){//&&honeydrop>=5 then: you get the key
            speech("Well done!","I have the key to the");
            speech("door to return to ","PacWorld!");
            speech("Till we meet again"," on the maze Pacman!");
            //add key code
            add_key(43,2);
            }
            break;
        
        case NEAR_PORTAL: 
            if(mapswitch==0){
            mapswitch=1;
            map_erase(48,1,VERTICAL,1); //erase ghost 
            deleteDrop(27,11);//erase door
            //add all new map stuff
            //maze wall boundary
            add_wall(6,30,HORIZONTAL,28);
            add_wall(37,30,HORIZONTAL,7);
            add_wall(6,31,VERTICAL,13);
            add_wall(7,43,HORIZONTAL,1);
            add_wall(11,43,HORIZONTAL,33);
            add_wall(43,31,VERTICAL,12);
            //inner maze walls
            add_wall(10,34,HORIZONTAL,14);
            add_wall(10,35,HORIZONTAL,14);
            
            add_wall(10,38,VERTICAL,4);
            add_wall(11,38,VERTICAL,4);
            add_wall(12,38,VERTICAL,4);
            add_wall(13,38,VERTICAL,4);
            
            add_wall(17,37,VERTICAL,6);
            
            add_wall(21,38,HORIZONTAL,10);
            add_wall(21,39,HORIZONTAL,10);
            
            add_wall(29,32,HORIZONTAL,8);
            add_wall(29,33,HORIZONTAL,8);
            
            add_wall(34,34,VERTICAL,6);
            add_wall(35,34,VERTICAL,6);
            add_wall(36,34,VERTICAL,6);
            //maze honeydrops
            add_honey(10,33);
            add_honey(15,33);
            add_honey(20,33);
            add_honey(8,38);
            add_honey(8,41);
            add_honey(21,37);
            add_honey(30,37);
            add_honey(39,35);
            add_honey(39,37);
            add_honey(39,39);
            //maze poisondrops
            for(int j=10; j<=22;j+=2){
                add_poison(j,31);
            }
            for(int j=20;j<=36;j+=2){
                add_poison(j,42);
            }
            //portal shift;move to redraw
            uLCD.filled_rectangle(0,0,127,127, BLACK);
            wait(.1);
            uLCD.filled_rectangle(0,0,127,127, LIGHTPURPLE);
            wait(.1);
            uLCD.filled_rectangle(0,0,127,127, RED);
            wait(.1);           
            }
            else if(mapswitch==1){
            pc.printf("how"); 
            mapswitch=0;
            //map_erase(45,20);//erase the honey drop added
            //delete all the other map stuff
            uLCD.filled_rectangle(0,0,127,127, BLACK);
            wait(.1);
            uLCD.filled_rectangle(0,0,127,127, LIGHTPURPLE);
            wait(.1);
            uLCD.filled_rectangle(0,0,127,127, BLACK);
            wait(.1);
            add_ghost(48,1);
            add_door(27,11);
            //delete
            ////////////
            map_erase(6,30,HORIZONTAL,28);
            map_erase(37,30,HORIZONTAL,7);
            map_erase(6,31,VERTICAL,13);
            map_erase(7,43,HORIZONTAL,1);
            map_erase(11,43,HORIZONTAL,33);
            map_erase(43,31,VERTICAL,12);
            //inner maze walls
            map_erase(10,34,HORIZONTAL,14);
            map_erase(10,35,HORIZONTAL,14);
            
            map_erase(10,38,VERTICAL,4);
            map_erase(11,38,VERTICAL,4);
            map_erase(12,38,VERTICAL,4);
            map_erase(13,38,VERTICAL,4);
            
            map_erase(17,37,VERTICAL,6);
            
            map_erase(21,38,HORIZONTAL,10);
            map_erase(21,39,HORIZONTAL,10);
            
            map_erase(29,32,HORIZONTAL,8);
            map_erase(29,33,HORIZONTAL,8);
            
            map_erase(34,34,VERTICAL,6);
            map_erase(35,34,VERTICAL,6);
            map_erase(36,34,VERTICAL,6);
            //maze honeydrops
            deleteDrop(10,33);
            deleteDrop(15,33);
            deleteDrop(20,33);
            deleteDrop(8,38);
            deleteDrop(8,41);
            deleteDrop(21,37);
            deleteDrop(30,37);
            deleteDrop(39,35);
            deleteDrop(39,37);
            deleteDrop(39,39);
            //maze poisondrops
            for(int j=10; j<=22;j+=2){
                deleteDrop(j,31);
            }
            for(int j=20;j<=36;j+=2){
                deleteDrop(j,42);
            }
            }
           break; 
        case NEAR_DOOR:
                   if(Player.has_key==0){
                        speech("Can't open door!","No key!");               
                    }    
                   else if(Player.has_key==1){
                        speech("Welcome back home!","");
                        deleteDrop(27,11);
                        wait(1);
                        Player.gamestate=0;
                        //end game signal    
                  }
                break;
        default:break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles   
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    pc.printf("plants\r\n");
    //Small Set of Plants
    for(int i=10;i<15;i++){
        add_plant(i,1,VERTICAL,20);   
    } 
    //couple of walls bordering the plants 
    add_wall(15,1,VERTICAL,20); 
    add_wall(16,20,HORIZONTAL,5);
    add_wall(40,1,VERTICAL,20); 
    add_wall(35,20,HORIZONTAL,5); 
    //another set of plants
    for(int i= 6; i<=42;i+=3){//5,15
            add_plant(i,23,HORIZONTAL,1);
    }
    for(int i= 6; i<=42;i+=3){//5,15
            add_plant(i,26,HORIZONTAL,1);
    }
//    //add another set of plants
//    for(int i= 35; i<45;i++){//5,15
//        for(int j=30;j<40;j++){//35,45
//            add_plant(i,j,VERTICAL,5);
//        }
//    }
    //add my NPC/GHOST
    add_ghost(48,1);  
    add_portal(48,10); 
    add_door(27,11);     
    ////borders
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    //pc.printf("Im Here");
    //code that keeps the start screen in a loop
    //speaker init
    gSpeakerOut.period(1.0/200000.0); 
    Ticker Sample_Period; 
    Sample_Period.attach(&Sample_timer_interrupt, 1.0/(20000.0));
    gSpeakerOut.SwitchSound(Speaker::BEGIN);
    /////////
    draw_gamestart();
    int start=1;
    while(start){
          wait(.1);
          start= !button_checker(read_inputs());
    }
    // Initialize the maps
    maps_init();
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x =5;
    Player.y = 5;
    Player.has_key=0;
    Player.drop=0;
    Player.health=5;
    Player.gamestate=1;
    Player.om=0;
    pc.printf("plants\r\n");
    // Initial drawing
    draw_game(true);
    // Main game loop
    while(Player.gamestate)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs
        in = read_inputs();        
        // 2. Determine action (get_action)
        action = get_action(in);        
        // 3. Update game based on the action (update_game)
        update = update_game(action);
        // 3b. Check for game over
        uLCD.locate(1,15);
        uLCD.printf("Health %d",Player.health);
        uLCD.locate(1,0);
        if(Player.x < 10)
            uLCD.printf("X 0%d",Player.x);    
        else
            uLCD.printf("X %d",Player.x);
        uLCD.locate(7,0);
        if (Player.y < 10)
            uLCD.printf("Y 0%d",Player.y);
        else
            uLCD.printf("Y %d",Player.y);
        uLCD.locate(9,15);
        uLCD.printf(" Honey: %d",Player.drop);
        cleanup();
        button_checker(read_inputs());
        if(Player.health <=0)
        {
            Player.gamestate = 0;    
        }
        // 4. Draw frame based on the update, whether we need to update all frames (draw_game)
        draw_game(update);
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    //game over screen
    draw_gameover();
}
