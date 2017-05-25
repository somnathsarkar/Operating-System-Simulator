#include "Screen.h"

ESCMenu::ESCMenu(ScreenType target, ScreenType * destination)
{
	this->target = target;
	this->destination = destination;
}

void ESCMenu::processEvent(SDL_Event & e)
{
	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*destination = target;
		break;
	}
}
