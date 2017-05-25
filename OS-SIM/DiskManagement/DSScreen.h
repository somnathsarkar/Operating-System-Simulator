#pragma once
#include "../Deadlock/BKScreen.h"
#include "../ScreenManagement/WindowManager.h"
#include "../MovieClip/TextInputClip.h"
#include <sstream>

class DInput : public TextInputClip{
public:
	bool *target;
	DInput(int w = 640, int h = 40);
	void onTextSubmit();
};

class DContext : public MovieClip {
public:
	bool visible;
	DContext(int x);
	void processEvent(SDL_Event& e);
	void render(int x = 0, int y = 0);
private:
	MovieClip * tmc;
	int loc;
};

class DUnit : public MouseClip {
public:
	DUnit(int x);
	~DUnit();
	void onMouseOver();
	void onMouseOut();
private:
	int loc;
	DContext *dc;
};

class DClip : public MovieClip {
public:
	std::vector<int> GD;
	DClip(int c);
	void display(int c);
private:
	int cyl;
};

class DSoln {
public:
	DSoln(std::string name, int cyl);
	std::string name;
	int seektime;
	DClip *dc;
};

class DSScreen : public Screen {
public:
	DSScreen();
	void init();
	ScreenType mainLoop();
	void exit();
	int fcfs(std::vector<int>& GD);
	int look(std::vector<int>& GD, int h, int pr, int c);
	int sstf(std::vector<int>& GD);
	int clook(std::vector<int>& GD, int h, int pr, int c);
	int cscan(std::vector<int>& GD, int h, int pr, int c);
	int scan(std::vector<int>& GD, int h, int pr, int c);
	void compute();
	void updateInputs();
	void updateDisplay();
private:
	int focus;
	int n,req[100],header,preq,cyl;
	bool reqsubmit;
	bool tl, tr;
	ScreenType destination;
	ESCMenu *em;
	MovieClip *container;
	MovieClip *dcc, *dtitle, *dseek;
	DInput *dri,*dhi,*dpi,*dci;
	DSoln *ds[6];
	LeftButton *l;
	RightButton *r;
};