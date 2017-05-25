#pragma once
#include "LTexture.h"
#include <vector>
#include <algorithm>
#include <map>

class MovieClip {
public:
	//upper-left coordinates
	int x, y;
	//arbitrary height and width values (Does not affect render)
	int h, w;
	//offset of the texture
	int tx, ty;
	//SDL Renderer passed from main program (Set this at beginning of program)
	static SDL_Renderer* renderer;
	//Map of all fonts and sizes
	static std::map<std::pair<std::string, int>, TTF_Font*> fontmap;
	//vector containing children
	std::vector<MovieClip*> children;

	//blank initialization
	MovieClip();
	//create from image
	MovieClip(std::string path);
	//create from texture
	MovieClip(LTexture*& t);
	//create rectangle
	MovieClip(int w, int h, SDL_Color c = { 255,0,0,255 });
	//create textbox
	MovieClip(std::string text, std::string font, int fontsize, SDL_Color c = { 0,0,0,255 });
	//destructor
	~MovieClip();
	//render the MC and all its children (x,y specifies an offset)
	virtual void render(int x=0, int y = 0);
	//destroy the MC and all its children
	void destroy();
	//add a child
	void addChild(MovieClip*);
	//remove a child O(N)
	void removeChild(MovieClip*);
	//get child at index
	MovieClip* getChildAt(int x);
	//process events
	virtual void processEvent(SDL_Event& e);
	//get methods for absX and absY
	int getabsX();
	int getabsY();

protected:
	int absX, absY;
	LTexture *texture;

private:
	int numChildren;
};