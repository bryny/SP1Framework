// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h" 
#include "score.h"


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 100; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
    mainLoop();  // main loop
	scoreboard();
    shutdown();  // do clean up, if any. free memory.
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}    
}

void scoreboard()
{
	playerScore = score;

	std :: ifstream input;
	string background;
	input.open("leaderboard.txt");
	while(!input.eof())
	{
		input>>background;
		std :: cout << background;
	}
	input.close();

	board HS[5];
	Read("highscore.txt", HS);
	if (playerScore > HS[4].highScore)
	{
		std :: cout << "Enter your name: ";
		std :: cin >> enteredName;
	}

	for (int i = 0; i < 5; i++)
	{
		if (playerScore > HS[i].highScore)
		{
			board temp[5];
			for (int j = 0; j < 5; j++)
			{
				temp[j].highScore = HS[j].highScore;
				temp[j].name = HS[j].name;
			}

			HS[i].highScore = playerScore;
			HS[i].name = enteredName;
			
			for (int k = 0; k < 5; k++, i++)
			{
			HS[i+1].highScore = temp[k].highScore;
			HS[i+1].name = temp[k].name;
			}
		break;
		}
	}


	for (int c = 0; c < 5; c++)
	{
		std :: cout << HS[c].name << " " << HS[c].highScore << std :: endl;
	}

	Write("highscore.txt",HS);


}
