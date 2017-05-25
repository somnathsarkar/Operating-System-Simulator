#pragma once
#include "MouseClip.h"

class TextInputClip : public MouseClip{
private:
	MovieClip *textClip;
	MouseClip *textbg;
	void updateTextClip();
public:
	static TextInputClip *focus;
	std::string text;
	TextInputClip(int w, int h);
	void setFocus(MouseClip *x);
	void backspace();
	void textInput(std::string newtext);
	void processTextEvent(SDL_Event& e);
	void onMouseUp();
	virtual void onTextSubmit() {};
};