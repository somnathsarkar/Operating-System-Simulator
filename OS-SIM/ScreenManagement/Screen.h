#pragma once
#include "../MovieClip/MouseClip.h"
#include "../ScreenManagement/ScreenType.h"

class ESCMenu : public MovieClip {
public:
	ESCMenu(ScreenType target, ScreenType *destination);
	void processEvent(SDL_Event& e);
private:
	ScreenType target;
	ScreenType *destination;
};

class Screen {
public:
	virtual void init() = 0;
	virtual ScreenType mainLoop() = 0;
	virtual void exit() = 0;
};