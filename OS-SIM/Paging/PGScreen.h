#pragma once
#include "../Deadlock/BKScreen.h"
#include "../ScreenManagement/WindowManager.h"
#include "../MovieClip/TextInputClip.h"
#include <iostream>
#include <sstream>

class PageButton : public MouseClip {
public:
	bool *target;
	int *targetchoice;
	PageButton(int x, std::string name);
	void onMouseUp();
private:
	int chval;
};

class FrameBlock : public MovieClip {
public:
	FrameBlock();
	void changeValue(int x);
private:
	int value;
	MovieClip *numval;
};

class FrameInput : public TextInputClip {
public:
	bool *target;
	FrameInput();
	void onTextSubmit();
};

class PageInput : public TextInputClip {
public:
	bool *target;
	PageInput();
	void onTextSubmit();
};

class PGScreen : public Screen{
public:
	bool frameUpdate;
	bool pageUpdate;

	PGScreen();
	void init();
	ScreenType mainLoop();
	void exit();
	void pagemain();
	void lru(int arr[], int pages[], int curr, int size, int num_of_frames);
	void optimal(int arr[], int pages[], int curr, int size, int num_of_frames, int num_of_pages);
	void fifo(int arr[], int page, int size);
	int max(int arr[], int size);
	int min(int arr[], int size);
	int nextuse(int arr[], int frame, int size, int k);
	int lastuse(int arr[], int frame, int k);
	int check(int arr[], int page, int size);
	int display(int arr[], int size, int cnt, int outputmat[][100], int index);
	void lfu(int arr[], int pages[], int curr, int size, int num_of_frames);
	void mfu(int arr[], int pages[], int curr, int size, int num_of_frames);
	int frequency(int arr[], int frame, int k);
	void updateFrames();
	void updatePages();
	void compute();
	void displayControls();
	void updateDisplay();
	void updateLabels();
private:
	int ch;
	bool ml, mr, choicechange;
	int num_of_pages, num_of_frames, num_of_faults, outputmat[100][100], index, choice, num_of_hits, i, pages[100], frames[100], j, size, focus;
	ESCMenu *em;
	ScreenType destination;
	MovieClip *container,*numFaults,*numHits;
	FrameInput *fi;
	FrameBlock **fb;
	PageInput *pi;
	LeftButton *l;
	RightButton *r;
};