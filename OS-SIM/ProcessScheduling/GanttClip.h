#pragma once

#include "ProcessClip.h"
#include "../MovieClip/Animation.h"
#include "../ScreenManagement/WindowManager.h"

class HoverMove : public MouseClip {
public:
	int val;
	HoverMove();
	HoverMove(int off);
	void onMouseOver();
	void onMouseOut();
private:
	int off;
};

struct pro {
	int at, bt, ct, tat, wt, pno, id, priority;
};

struct Gantt {
	int pno, st, et;
	std::vector< std::pair<int,int> > readyqueue;
};

class GanttClip : public MovieClip{
public:
	std::vector<Gantt> GC;
	GanttClip();
	GanttClip(std::string name);
	~GanttClip();
	void display();
	MovieClip *ganttroot;
	HoverMove *l, *r;
private:
	std::string name;
};
