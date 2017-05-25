#pragma once
#include "MovieClip.h"

class Animation {
public:
	bool finished;
	Animation();
	Animation(MovieClip* mc, int x, int y, Uint32 time);
	~Animation();
	void moveForward(Uint32 deltaTicks);

private:
	MovieClip* target;
	int x, y;
	double tx, ty;
	double velX, velY;
	long long timeLeft;
};