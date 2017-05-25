#include "Animation.h"

Animation::Animation()
{
	target = NULL;
	x = y = 0;
	tx = ty = 0;
	velX = velY = 0;
	timeLeft = 0;
	finished = true;
}

Animation::Animation(MovieClip* mc, int x, int y, Uint32 time) {
	target = mc;
	this->x = x;
	this->y = y;
	tx = target->x;
	ty = target->y;
	double deltaX = (double)(x - target->x);
	double deltaY = (double)(y - target->y);
	double dtime = (double)time;
	velX = deltaX / dtime;
	velY = deltaY / dtime;
	timeLeft = time;
	finished = false;
}

Animation::~Animation()
{
	target = NULL;
	x = y = 0;
	tx = ty = 0;
	velX = velY = 0;
	timeLeft = 0;
	finished = true;
}

void Animation::moveForward(Uint32 deltaTicks)
{
	tx += (velX*deltaTicks);
	ty += (velY*deltaTicks);
	target->x = (int)tx;
	target->y = (int)ty;
	timeLeft -= deltaTicks;
	if (timeLeft <= 0) {
		//completed animation
		finished = true;
		target->x = x;
		target->y = y;
	}
}
