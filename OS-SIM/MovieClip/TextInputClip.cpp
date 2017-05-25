#include "TextInputClip.h"

TextInputClip* TextInputClip::focus = NULL;

TextInputClip::TextInputClip(int w, int h) : MouseClip(w, h, { 255,255,255,255 })
{
	text = "";
	textClip = new MovieClip(text, "Myriad Pro Regular", 18);
	addChild(textClip);
}

void TextInputClip::setFocus(MouseClip *x) {
	focus = (TextInputClip*)x;
}

void TextInputClip::backspace() {
	if (text.length()) {
		text.pop_back();
		updateTextClip();
	}
}

void TextInputClip::textInput(std::string newtext){
	text += newtext;
	updateTextClip();
}

void TextInputClip::processTextEvent(SDL_Event& e)
{
	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_BACKSPACE)
			backspace();
		else if (e.key.keysym.sym == SDLK_RETURN) {
			focus = NULL;
			onTextSubmit();
		}
		break;
	case SDL_TEXTINPUT:
		textInput(e.text.text);
		break;
	}
}

void TextInputClip::onMouseUp()
{
	setFocus(this);
}

void TextInputClip::updateTextClip() {
	removeChild(textClip);
	delete textClip;
	textClip = new MovieClip(text, "Myriad Pro Regular", 18);
	addChild(textClip);
}
