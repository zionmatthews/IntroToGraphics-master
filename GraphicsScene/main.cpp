#include <gl_core_4_4.h>
#include "Game.h"
/**
* Where the game loop starts
*/

int main() 
{
	Game* app = new Game();

	app->run();

	delete app;
}
