#pragma once
#include "../MovieClip/Animation.h"
#include "../MovieClip/TextInputClip.h"
#include "../ScreenManagement/Screen.h"
#include "../ScreenManagement/WindowManager.h"
#include "GanttClip.h"
#include <algorithm>
#include <ctime>

class PSInputText : public TextInputClip {
public:
	PSInputText(int w, int h);
	void onTextSubmit();
};

class PSInput : public MovieClip{
public:
	PSInput();
	void addProcess();
	void removeProcess(int x);
	std::vector<MovieClip*> processInputs;
};

class PSScreen : public Screen{
public:
	PSScreen();
	void init();
	ScreenType mainLoop();
	void exit();
	void processUpdate();
private:
	ScreenType destination;
	ESCMenu *em;
	MouseClip *container;
	MovieClip *gcContainer;
	PSInput *psi;
};