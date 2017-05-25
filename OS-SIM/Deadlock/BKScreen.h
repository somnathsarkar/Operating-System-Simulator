#pragma once
#include "../MovieClip/TextInputClip.h"
#include "../ScreenManagement/Screen.h"
#include "../ScreenManagement/WindowManager.h"
#include <sstream>

class NextButton : public MouseClip {
public:
	NextButton();
	void onMouseUp();
	bool *target;
private:
};

class LeftButton : public MouseClip {
public:
	bool *target;
	LeftButton();
	void onMouseUp();
};

class RightButton : public MouseClip {
public:
	bool *target;
	RightButton();
	void onMouseUp();
};

class ReqInput : public TextInputClip {
public:
	ReqInput();
	void onTextSubmit();
};

class BKScreen : public Screen {
public:
	BKScreen();
	void init();
	ScreenType mainLoop();
	void exit();
	void matrixInput();
	bool matrixInputTime;
	bool calcTime;
	void read();
	bool check_safe();
	bool check_request_allocate();
	void calc();
	void displayNeedMatrix();
	void displayResult();
	void moveLeft();
	void moveRight();
	void displaySafe(bool s);
	void displayRequestMenu();
	void processRequest();
	void displayGranted(bool s);

private:
	NextButton *nb;
	int res, pro;
	ScreenType destination;
	ESCMenu *em;
	MovieClip *container;
	TextInputClip *resInput, *proInput, *maxresInput, *pInput;
	ReqInput *resreqInput;
	TextInputClip **allocMatrix, **maxMatrix;
	MovieClip *safeseq,*avail, *safeLabel, *reqmenu, *grantedLabel;
	bool ml, mr;
	int focus;
	int ballocate[20][20], bmax[20][20], bneed[20][20], bavail[20][20], binstance[20], bav[100], bwork[20], btime[20], bfinish[20];
	int bk, bt, bct, bpos[20], brq[20], br, bpro, bp, bi, bj, bdisp[20][20], bq, bpcount;
};