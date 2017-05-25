#pragma once
#include "MovieClip.h"

class MouseClip : public MovieClip {
public:
	bool mouseInside;
	bool scrollable;
	int scrollspeed;
	void *imp;
	virtual void onMouseDown() {};
	virtual void onMouseUp() {};
	virtual void onMouseOver() {};
	virtual void onMouseOut() {};
	MouseClip();
	MouseClip(std::string path);
	MouseClip(int w, int h, SDL_Color c = { 255,0,0,255 });
	~MouseClip();
	void processEvent(SDL_Event& e);

private:
	bool checkMouseInside();
};