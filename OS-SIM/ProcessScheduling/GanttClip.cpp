#include "GanttClip.h"

GanttClip::GanttClip()
{
	l = r = NULL;
}

GanttClip::GanttClip(std::string name)
{
	this->name = name;
	l = r = NULL;
}

GanttClip::~GanttClip()
{
	this->name = "";
	delete l;
	delete r;
	l = r = NULL;
}

void GanttClip::display()
{
	ganttroot = new MovieClip();
	SDL_Color sc[] = { { 255,0,0,255 },{ 0,255,0,255 },{ 0,0,255,255 },{ 255,255,0,255 },{ 255,0,255,255 },{ 0,255,255,255 } };
	addChild(ganttroot);
	int maxh = 0;
	for (auto &it : GC) {
		ProcessClip *g = new ProcessClip(it.pno, it.st, it.et, it.readyqueue, sc[it.pno]);
		ganttroot->addChild(g);
		g->x = ProcessClip::WIDTH*it.st;
		maxh = std::max(maxh, g->h);
		ganttroot->w = g->x+g->w;
	}
	MovieClip *titletext = new MovieClip(name, "Myriad Pro Regular", 32);
	addChild(titletext);
	ganttroot->y = titletext->h+5;
	h = ganttroot->y + maxh + 5;
	w = std::max(640, ganttroot->w);
	l = new HoverMove(1);
	r = new HoverMove(-1);
	l->w = 40;
	l->h = h;
	r->w = 40;
	r->h = h;
	r->x = 640 - 40;
	addChild(l);
	addChild(r);
}

HoverMove::HoverMove()
{
	val = 0;
	off = 0;
}

HoverMove::HoverMove(int off)
{
	val = 0;
	this->off = off;
}

void HoverMove::onMouseOver()
{
	val = off;
}

void HoverMove::onMouseOut()
{
	val = 0;
}
