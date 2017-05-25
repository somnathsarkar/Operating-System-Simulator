#include "MovieClip.h"

SDL_Renderer *MovieClip::renderer = NULL;
std::map< std::pair<std::string, int>, TTF_Font* > MovieClip::fontmap;

MovieClip::MovieClip()
{
	x = y = h = w = tx = ty = absX = absY = 0;
	numChildren = 0;
	texture = new LTexture();
}

MovieClip::MovieClip(std::string path) {
	x = y = tx = ty = absX = absY = 0;
	numChildren = 0;
	texture = new LTexture();
	texture->loadImageFile(renderer, path);
	w = texture->getWidth();
	h = texture->getHeight();
}

MovieClip::MovieClip(LTexture *& t)
{
	x = y = tx = ty = absX = absY = 0;
	numChildren = 0;
	texture = t;
	w = texture->getWidth();
	h = texture->getHeight();
}

MovieClip::MovieClip(int w, int h, SDL_Color c) {
	x = y = tx = ty = absX = absY = 0;
	numChildren = 0;
	texture = new LTexture();
	texture->drawRect(renderer, w, h, c);
	this->w = w;
	this->h = h;
}

MovieClip::MovieClip(std::string text, std::string font, int fontsize, SDL_Color c)
{
	x = y = tx = ty = absX = absY = 0;
	numChildren = 0;
	texture = new LTexture();
	TTF_Font* found_font = NULL;
	if (fontmap.find(make_pair(font, fontsize)) != fontmap.end())
		found_font = fontmap[make_pair(font, fontsize)];
	else
	{
		found_font = TTF_OpenFont(("Resources/Fonts/"+font+".ttf").c_str(), fontsize);
		if (found_font == NULL)
			printf("Failed to load font %s! TTF Error: %s\n", font.c_str(), TTF_GetError());
		else
			fontmap[make_pair(font, fontsize)] = found_font;
	}
	texture->loadFromRenderedText(renderer, text, found_font, c);
	w = texture->getWidth();
	h = texture->getHeight();
}

MovieClip::~MovieClip() {
	destroy();
}

void MovieClip::render(int x, int y) {
	int nx = (this->x) + x, ny = (this->y) + y;
	absX = nx;
	absY = ny;
	texture->render(renderer, nx+tx, ny+ty);
	for (auto &it : children)
		it->render(nx,ny);
}

void MovieClip::destroy() {
	for (auto &it : children)
		it->destroy();
	for (auto &it : children)
		delete it;
	texture->free();
	x = y = h = w = tx = ty = 0;
	children.clear();
	numChildren = 0;
}

void MovieClip::addChild(MovieClip* mc) {
	children.push_back(mc);
	numChildren++;
}

void MovieClip::removeChild(MovieClip *mc)
{
	auto it = std::remove(children.begin(), children.end(), mc);
	children.erase(it, children.end());
}

MovieClip * MovieClip::getChildAt(int x)
{
	return children[x];
}

void MovieClip::processEvent(SDL_Event & e)
{
	for (auto &it : children)
		it->processEvent(e);
}

int MovieClip::getabsX()
{
	return absX;
}

int MovieClip::getabsY()
{
	return absY;
}
