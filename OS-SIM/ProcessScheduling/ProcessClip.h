#pragma once
#include "../MovieClip/MouseClip.h"
#include "../ScreenManagement/WindowManager.h"
#include <sstream>

class ProcessContext : public MovieClip {
public:
	ProcessContext(std::vector<std::pair<int, int>> rq);
	void processEvent(SDL_Event& e);
	void render(int x = 0, int y = 0);
	bool visible;
};

class ProcessClip : public MouseClip{
public:
	static int HEIGHT;
	static int WIDTH;
	int pno;
	ProcessClip(int no, int st, int et, std::vector<std::pair<int,int>> rq, SDL_Color c = { 255,0,0,255 });
	~ProcessClip();
	void onMouseOver();
	void onMouseOut();
private:
	std::vector<std::pair<int, int>> readyqueue;
	ProcessContext *pc;
};
