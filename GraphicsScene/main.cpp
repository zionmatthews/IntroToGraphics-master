#include <gl_core_4_4.h>
#include "Game.h"


int main() 
{
	Game* app = new Game();

	app->run();

	delete app;
}
