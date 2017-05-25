#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class LTexture {
public:
	LTexture();
	~LTexture();
	bool loadImageFile(SDL_Renderer*& r, std::string path);
	void free();
	void render(SDL_Renderer*& r, int x, int y);
	void drawRect(SDL_Renderer *& r, int w, int h, SDL_Color c = { 255,0,0,255 });
	bool loadFromRenderedText(SDL_Renderer*& r, std::string text, TTF_Font* font, SDL_Color c = { 0,0,0,255 });
	int getWidth();
	int getHeight();

private:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
};