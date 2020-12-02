#include <gl_core_4_4.h>
#include "App.h"


int main() 
{
	App* app = new App();

	app->run();

	delete app;
}
