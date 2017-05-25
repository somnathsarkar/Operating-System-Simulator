#include "LTexture.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadImageFile(SDL_Renderer*& r, std::string path) {
	free();
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		printf("Could not load image at %s! Error: %s\n", path.c_str(), IMG_GetError());
	else {
		newTexture = SDL_CreateTextureFromSurface(r, loadedSurface);
		if (newTexture == NULL)
			printf("Could not generate texture from image at %s! Error: %s\n", path.c_str(), SDL_GetError());
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return (mTexture != NULL);
}

void LTexture::free()
{
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(SDL_Renderer*& r, int x, int y) {
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	SDL_RenderCopy(r, mTexture, NULL, &renderQuad);
}

void LTexture::drawRect(SDL_Renderer*& r, int w, int h, SDL_Color c) {
	mTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, w, h);
	if (mTexture == NULL)
		printf("Rectangle Draw Error! Error: %s\n", SDL_GetError());
	else {
		SDL_SetRenderTarget(r, mTexture);
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		SDL_Rect rect = { 0,0,w,h };
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(r, &rect);
		SDL_RenderPresent(r);
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_SetRenderTarget(r, NULL);
		mWidth = w;
		mHeight = h;
	}
}

bool LTexture::loadFromRenderedText(SDL_Renderer *& r, std::string text, TTF_Font * font, SDL_Color c)
{
	free();
	SDL_Surface *textSurface = NULL;
	if (text.length())
		textSurface = TTF_RenderText_Blended(font, text.c_str(), c);
	else
		textSurface = TTF_RenderText_Blended(font, " ", c);
	if (textSurface == NULL)
		printf("Unable to render text surface! TTF Error: %s\n", TTF_GetError());
	else
	{
		mTexture = SDL_CreateTextureFromSurface(r, textSurface);
		if (mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		else {
			if (text.length())
				TTF_SizeText(font, text.c_str(), &mWidth, &mHeight);
			else
				TTF_SizeText(font, " ", &mWidth, &mHeight);
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
	return false;
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}