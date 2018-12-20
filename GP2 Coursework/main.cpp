#include "MainGame.h"
#undef main	//Fix: error LNK2019: unresolved external symbol _SDL_main referenced in function _main_utf8


int main()
{
	MainGame mainGame;
	mainGame.Run();

	return 0;
}
