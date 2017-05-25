#include "MainScreen.h"

MainScreen::MainScreen()
{
	destination = ScreenType::MAIN_SCREEN;
}

void MainScreen::init()
{
	buttonContainer = new MovieClip(640, 480, { 0,34,49,255 });
	Window.stage->addChild(buttonContainer);
	ScreenChangeButton *pscb = new ScreenChangeButton("Resources/Graphics/PS.png",ScreenType::PS_SCREEN, &destination);
	pscb->x = ((640 / 2) - (pscb->w)) / 2;
	pscb->y = ((480 / 2) - (pscb->w)) / 2 + (pscb->h);
	buttonContainer->addChild(pscb);
	ScreenChangeButton *bkscb = new ScreenChangeButton("Resources/Graphics/BK.png",ScreenType::BK_SCREEN, &destination);
	bkscb->x = pscb->x + (640 / 2);
	bkscb->y = pscb->y;
	buttonContainer->addChild(bkscb);
	ScreenChangeButton *dscb = new ScreenChangeButton("Resources/Graphics/DS.png", ScreenType::DS_SCREEN, &destination);
	dscb->x = pscb->x;
	dscb->y = pscb->y + (480 / 2);
	buttonContainer->addChild(dscb);
	ScreenChangeButton *pgscb = new ScreenChangeButton("Resources/Graphics/PG.png", ScreenType::PG_SCREEN, &destination);
	pgscb->x = dscb->x + (640 / 2);
	pgscb->y = dscb->y;
	buttonContainer->addChild(pgscb);
}

ScreenType MainScreen::mainLoop()
{
	return destination;
}

void MainScreen::exit()
{
	Window.stage->removeChild(buttonContainer);
	delete buttonContainer;
	buttonContainer = NULL;
}

ScreenChangeButton::ScreenChangeButton(std::string pathname, ScreenType target, ScreenType * destination) : MouseClip(pathname)
{
	this->target = target;
	this->destination = destination;
}

void ScreenChangeButton::onMouseUp()
{
	*destination = target;
}
