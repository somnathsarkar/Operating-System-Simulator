#include "MovieClip/TextInputClip.h"
#include "MovieClip/Animation.h"
#include "Deadlock/BKScreen.h"
#include "DiskManagement/DSScreen.h"
#include "Paging/PGScreen.h"
#include "ProcessScheduling/PSScreen.h"
#include "ScreenManagement/MainScreen.h"
#include <stdio.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Uint32 deltaTime;
Uint32 lastFrame;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

ScreenType global_st;

bool init();
void close();
void changeScreen(ScreenType target);

int main(int argc, char **argv) {
	srand(time(NULL));
	bool quit = false;
	TextInputClip *lastClip = NULL;
	ScreenType current_screen = ScreenType::MAIN_SCREEN, screen_status = ScreenType::MAIN_SCREEN;
	global_st = ScreenType::MAIN_SCREEN;
	if (init()) {
		deltaTime = lastFrame = 0;
		MovieClip::renderer = gRenderer;
		Window.stage = new MovieClip();
		Window.animationList = new std::vector< Animation* >();
		changeScreen(ScreenType::MAIN_SCREEN);
		SDL_Event e;
		while (!quit) {
			deltaTime = SDL_GetTicks() - lastFrame;
			lastFrame = SDL_GetTicks();
			if (screen_status != current_screen) {
				changeScreen(screen_status);
				current_screen = screen_status;
				global_st = screen_status;
			}

			if (lastClip == NULL&&TextInputClip::focus != NULL) {
				SDL_StartTextInput();
				lastClip = TextInputClip::focus;
			}
			else if (lastClip != NULL&&TextInputClip::focus == NULL) {
				SDL_StopTextInput();
				lastClip = NULL;
			}
			else if (lastClip != TextInputClip::focus) {
				lastClip->onTextSubmit();
				lastClip = TextInputClip::focus;
			}

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT)
					quit = true;
				if (TextInputClip::focus != NULL)
					TextInputClip::focus->processTextEvent(e);
				Window.stage->processEvent(e);
			}
			for (auto &it : (*Window.animationList))
				it->moveForward(deltaTime);
			auto it = Window.animationList->begin();
			while (it != Window.animationList->end()) {
				if ((*it)->finished)
					it = Window.animationList->erase(it);
				else
					it++;
			}
			screen_status = Window.screen->mainLoop();
			SDL_RenderClear(gRenderer);
			Window.stage->render();
			SDL_RenderPresent(gRenderer);
		}
		close();
	}
	system("pause");
	return 0;
}

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed Init! Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("OS Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgflags = IMG_INIT_PNG;
				if (!(IMG_Init(imgflags)&imgflags)) {
					printf("SDL Image could not initialize! Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1) {
					printf("SDL Text could not initialize! Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void changeScreen(ScreenType target) {
	if (Window.screen != NULL) {
		Window.screen->exit();
		delete Window.screen;
	}
	if (target == ScreenType::MAIN_SCREEN) {
		printf("Now on MAIN_SCREEN\n");
		Window.screen = new MainScreen();
		Window.screen->init();
	}else if (target == ScreenType::PS_SCREEN) {
		printf("now on PS_SCREEN\n");
		Window.screen = new PSScreen();
		Window.screen->init();
	}
	else if (target == ScreenType::BK_SCREEN) {
		printf("now on BK_SCREEN\n");
		Window.screen = new BKScreen();
		Window.screen->init();
	}
	else if (target == ScreenType::DS_SCREEN) {
		printf("now on DS_SCREEN\n");
		Window.screen = new DSScreen();
		Window.screen->init();
	}
	else if (target == ScreenType::PG_SCREEN) {
		printf("now on PG_SCREEN\n");
		Window.screen = new PGScreen();
		Window.screen->init();
	}
}