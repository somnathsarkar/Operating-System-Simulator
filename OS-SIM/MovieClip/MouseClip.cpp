#include "MouseClip.h"
#include "../ScreenManagement/WindowManager.h"

MouseClip::MouseClip()
{
	mouseInside = checkMouseInside();
	scrollable = false;
	scrollspeed = 0;
}

MouseClip::MouseClip(std::string path) : MovieClip(path)
{
}

MouseClip::MouseClip(int w, int h, SDL_Color c) : MovieClip(w, h, c) {
	mouseInside = checkMouseInside();
	scrollable = false;
	scrollspeed = 0;
}

MouseClip::~MouseClip()
{
	mouseInside = false;
	scrollable = false;
	scrollspeed = 0;

}

void MouseClip::processEvent(SDL_Event& e) {
	bool inside = checkMouseInside();
	if (inside) {
		if (!mouseInside) {
			onMouseOver();
		}
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			onMouseDown();
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseUp();
			break;
		case SDL_MOUSEWHEEL:
			if (scrollable)
				this->y += e.wheel.y*scrollspeed;
			break;
		}
	}
	else {
		if (mouseInside) {
			onMouseOut();
		}
	}
	mouseInside = inside;
	for (auto &it : children)
		it->processEvent(e);
}

bool MouseClip::checkMouseInside()
{
	bool inside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);
	int ax = getabsX(), ay = getabsY();
	if (x < ax)
		inside = false;
	if (x>ax+w)
		inside = false;
	if (y < ay)
		inside = false;
	if (y > ay + h)
		inside = false;
	return inside;
}
