// This is the main file for the game logic and function
//
//
#include "game.h"
#include "objects.h"
#include "systems.h"
#include "Framework\console.h"
#include "render.h"
#include <iostream>   
#include <iomanip>
#include <sstream>

// Console size, width by height
COORD ConsoleSize = {80, 59};


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];


// Game specific variables here
COORD charLocation;

//Shannon : Jump function
enum jumpability
{
	ENABLED
};
int jump = ENABLED; //Shannon : Sets whether player can jump
int jumptime = 20; //Shannon : Number of frames player will float after jumping

void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;

    initConsole(ConsoleSize, "Fruit Bomb");

	// Sets Character's starting coordinates
    charLocation.X = (ConsoleSize.X - 10) / 2;
    charLocation.Y = ConsoleSize.Y - 2;
	
	//Shannon : Initializes Objects
    ImplementObjects();

	//Shannon : Initializes Life System
	ImplementLife();
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    shutDownConsole();
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	//keyPressed[K_UP] = isKeyPressed(65) => Pressing 'A' = Up
	//'A' ~ 'Z' = 65~90
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	// quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    

	//Shannon : Game will continue updating as long as the player has 1 Life
	if (Life.Value <= 0)
	{
		return;
	}

	// Updating the location of the character based on the key press

	//Shannon : If the player is on the ground (jump == 0 || ENABLED), jumping is enabled
    if (keyPressed[K_UP] && charLocation.Y > 0 && jump == ENABLED)
    {
		 Beep(1440, 30);
		 charLocation.Y -= 6; 
		 jump = jumptime;
    }
	//Shannon : Player will stay in the air for number of frames of jumptime
	if (jump > 0)
	{
		--jump;
	}
	//Shannon : Player will fall just before jumping is enabled again
	if (jump == 1)
	{
		charLocation.Y +=6;
	}

    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		charLocation.X--;
    }
    if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 1)
    {
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < ConsoleSize.X - 29)
    {
        charLocation.X++; 
    }
	
	//Shannon : Updates the level based on LevelCounter
	UpdateLevel();

	//Yi Yang : Updates the level difficulty based on difficultyEnum and Level
	updateDifficulty();

	//Shannon : Updates the objects & rats for coordinates and collision detection
	UpdateObjects();
	UpdateRat();

	//Shannon : Create Objects
	CreateObjects();

	//Shannon : Updates Level Timer
	UpdateLvTimer();   
}



void render()
{
    // Clears the buffer with this colour attribute
    clearBuffer(0x1F);

    // render time taken to calculate this frame
	COORD F_P_S = {66,0};
	std::string FPS_String = std::to_string(static_cast<long double>(1.0 / deltaTime)) + "fps";
	writeToBuffer(F_P_S,FPS_String);

	// elapsed running time of file
	COORD EL_TIME = {0,0};
	std::string TIME_String = std::to_string(static_cast<long double>(elapsedTime)) + "secs";
	writeToBuffer(EL_TIME,TIME_String);


    //Jenny : Render Character
	Render_Man();
	
	//Jeffrey : Render Score System
	displayscore();
	
	//Shannon : Render Objects & Rat
   	RenderObjects();
	
	//Shannon : Render Life System
	RenderLife();
	
	//Jenny: Render border
	RenderBorder();
	
	//Shannon : Render Level System
	RenderLevel();
	
	//Shannon : Render Level Timer
	RenderLvTimer();
	
	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
