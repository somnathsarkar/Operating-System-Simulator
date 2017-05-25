#pragma once
#include "Screen.h"
#include "WindowManager.h"

class ScreenChangeButton : public MouseClip {
public:
	ScreenChangeButton(std::string pathname, ScreenType target, ScreenType* destination);
	void onMouseUp();
private:
	ScreenType target;
	ScreenType *destination;
};

class MainScreen : public Screen {
public:
	MainScreen();
	void init();
	ScreenType mainLoop();
	void exit();
private:
	MovieClip *buttonContainer;
	ScreenType destination;
};