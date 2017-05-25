#pragma once
#include "../MovieClip/Animation.h"
#include "../MovieClip/MouseClip.h"
#include "Screen.h"

struct WindowManager {
	MovieClip* stage;
	std::vector< Animation* >* animationList;
	Screen *screen;
};

extern WindowManager Window;