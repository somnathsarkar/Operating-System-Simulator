#include "ProcessClip.h"

int ProcessClip::HEIGHT = 40;
int ProcessClip::WIDTH = 40;

void pno_display(MouseClip* x) {
	printf("%d\n", ((ProcessClip*)(x->imp))->pno);
}

ProcessClip::ProcessClip(int no, int st, int et, std::vector<std::pair<int,int>> rq, SDL_Color c) : MouseClip(WIDTH*(et - st + 1), HEIGHT, c)
{
	readyqueue = rq;
	pc = new ProcessContext(readyqueue);
	Window.stage->addChild(pc);
	pno = no;
	imp = this;
	std::stringstream Pstring;
	Pstring << "P" << pno;
	MovieClip *textClip = new MovieClip(Pstring.str(),"Myriad Pro Regular",18);
	textClip->x = (w - textClip->w) / 2;
	textClip->y = ((h - textClip->h) / 2)+2;
	Pstring.str("");
	Pstring << st;
	MovieClip *stText = new MovieClip(Pstring.str(), "Myriad Pro Regular", 18);
	stText->x = (WIDTH - textClip->w) / 2;
	stText->y = (HEIGHT + 2);
	if (st != et) {
		Pstring.str("");
		Pstring << et;
		MovieClip *etText = new MovieClip(Pstring.str(), "Myriad Pro Regular", 18);
		etText->x = WIDTH*(et - st) + ((WIDTH - textClip->w) / 2);
		etText->y = (HEIGHT + 2);
		addChild(etText);
	}
	addChild(textClip);
	addChild(stText);
	h += stText->h;
}

ProcessClip::~ProcessClip()
{
	Window.stage->removeChild(pc);
	delete pc;
	pc = NULL;
}

void ProcessClip::onMouseOver()
{
	pc->visible = true;
}

void ProcessClip::onMouseOut()
{
	pc->visible = false;
}

ProcessContext::ProcessContext(std::vector<std::pair<int, int>> rq) : MovieClip(80,(rq.size()*20)+10,{211,211,211})
{
	visible = false;
	int i = 0;
	for (auto &it : rq) {
		std::stringstream str;
		str << "P" << it.first;
		MovieClip *pmc = new MovieClip(str.str(), "Myriad Pro Regular", 18);
		addChild(pmc);
		pmc->y = 5 + (20 * i);
		pmc->x = 5;
		str.str("");
		str.clear();
		str << it.second;
		MovieClip *nmc = new MovieClip(str.str(), "Myriad Pro Regular", 18);
		nmc->y = 5 + (20 * i);
		nmc->x = w - (pmc->w) - 5;
		addChild(nmc);
		i++;
	}
}

void ProcessContext::processEvent(SDL_Event & e)
{
	if (visible) {
		int mx, my;
		switch (e.type) {
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mx, &my);
			x = mx;
			y = my - h;
		}
	}
}

void ProcessContext::render(int x, int y)
{
	if (visible) {
		int nx = (this->x) + x, ny = (this->y) + y;
		absX = nx;
		absY = ny;
		texture->render(renderer, nx + tx, ny + ty);
		for (auto &it : children)
			it->render(nx, ny);
	}
}
