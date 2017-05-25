#include "BKScreen.h"

void BKScreen::read()
{
	bpcount = 0;
	bq = 0;
	for (bi = 0; bi<bp; bi++)
	{
		for (bj = 0; bj<br; bj++)
		{
			bavail[0][bj] = ballocate[bi][bj] + bavail[0][bj];
		}
		bpos[bi] = bi + 1;
	}
	for (bi = 0; bi<bp; bi++)
	{
		bfinish[bi] = -1;
	}
	for (bi = 0; bi<br; bi++)
	{
		bavail[0][bi] = binstance[bi] - bavail[0][bi];
		bav[bi] = bavail[0][bi];
		bwork[bi] = bavail[0][bi];
	}
	for (bi = 0; bi<bp; bi++)
	{
		for (bj = 0; bj<br; bj++)
		{
			bneed[bi][bj] = bmax[bi][bj] - ballocate[bi][bj];
		}
	}
}
bool BKScreen::check_safe()
{
	//cout << "\nAvailable  : \n";
	for (bi = 0; bi<bp; bi++)
	{
		bfinish[bi] = -1;
	}
	for (bk = 0; bk<bp; bk++)
	{
		for (bi = 0; bi<bp; bi++)
		{
			bct = 0;
			if (bfinish[bi] == -1)
			{
				for (bj = 0; bj<br; bj++)
				{
					if (bneed[bi][bj] <= bwork[bj])
						bct++;
					else
						break;
				}
				if (bct == br)
				{
					for (bj = 0; bj<br; bj++)
					{
						bwork[bj] = bwork[bj] + ballocate[bi][bj];
						bavail[bi][bj] = bwork[bj];
					}
					bfinish[bi] = 0;
					bpos[bpcount++] = bi;
					btime[bi] = bt++;

				}
			}
		}
	}
	for (bi = 0; bi<bp; bi++)
	{
		if (bfinish[bi] == -1)
		{
			//cout << "\n\n\tSystem is in UNSAFE state\n\n";
			//exit(0);
			return false;
		}
	}
	//cout << "\n\n\tSystem is in SAFE state\n\n";
	return true;
}

bool BKScreen::check_request_allocate()
{
	//bpro pro number 1..n, brq 0..r-1
	for (bj = 0; bj<br; bj++)
	{
		if (brq[bj]>bneed[bpro - 1][bj])
		{
			//cout << "Request NOT Granted!\n";
			//exit(0);
			return false;
		}
	}
	for (bj = 0; bj<br; bj++)
	{
		if (brq[bj]>bavail[bpro - 1][bj])
		{
			//cout << "\n\tRequest NOT Granted!\n";
			//exit(0);
			return false;
		}
		else
		{
			bav[bj] = bav[bj] - brq[bj];
			ballocate[bpro - 1][bj] = ballocate[bpro - 1][bj] + brq[bj];
		}
	}

}

BKScreen::BKScreen()
{
	avail = safeseq = safeLabel = reqmenu = NULL;
	destination = ScreenType::BK_SCREEN;
}

void BKScreen::init()
{
	ml = mr = false;
	matrixInputTime = false;
	calcTime = false;
	em = new ESCMenu(ScreenType::MAIN_SCREEN, &destination);
	Window.stage->addChild(em);
	container = new MovieClip(640, 480, {0,77,55,255});
	Window.stage->addChild(container);
	MovieClip *resInputLabel = new MovieClip("Enter Resources: ","Arial",18);
	MovieClip *proInputLabel = new MovieClip("Enter Processes: ", "Arial", 18);
	resInputLabel->x = 10;
	resInputLabel->y = 10;
	proInputLabel->x = 10;
	proInputLabel->y = resInputLabel->y + resInputLabel->h + 5;
	resInput = new TextInputClip(20, 20);
	resInput->x = resInputLabel->x + resInputLabel->w + 5;
	resInput->y = resInputLabel->y;
	proInput = new TextInputClip(20, 20);
	proInput->x = resInput->x;
	proInput->y = proInputLabel->y;
	container->addChild(resInputLabel);
	container->addChild(proInputLabel);
	container->addChild(resInput);
	container->addChild(proInput);
	MovieClip *maxresInputLabel = new MovieClip("Enter Max Resources: ", "Arial", 18);
	maxresInputLabel->x = 10;
	maxresInputLabel->y = proInputLabel->y + proInputLabel->h + 5;
	maxresInput = new TextInputClip(120, 20);
	maxresInput->x = maxresInputLabel->x + maxresInputLabel->w + 5;
	maxresInput->y = maxresInputLabel->y;
	container->addChild(maxresInputLabel);
	container->addChild(maxresInput);
	nb = new NextButton();
	nb->x = resInput->x + resInput->w + 15;
	nb->y = 10;
	nb->target = &matrixInputTime;
	container->addChild(nb);
}

ScreenType BKScreen::mainLoop()
{
	if (ml) {
		ml = false;
		moveLeft();
	}
	if (mr) {
		mr = false;
		moveRight();
	}
	if (matrixInputTime) {
		matrixInputTime = false;
		nb->target = &calcTime;
		matrixInput();
	}
	if (calcTime) {
		calcTime = false;
		calc();
	}
	return destination;
}

void BKScreen::exit()
{
	Window.stage->removeChild(em);
	Window.stage->removeChild(container);
	delete em;
	delete container;
}

void BKScreen::matrixInput()
{
	res = std::stoi(resInput->text);
	pro = std::stoi(proInput->text);
	std::istringstream maxresInputStr(maxresInput->text);
	for (int i = 0; i < res; i++)
		maxresInputStr >> binstance[i];
	MovieClip* nextcontainer = new MovieClip();
	nextcontainer->x = maxresInput->x + maxresInput->w + 5;
	container->addChild(nextcontainer);
	MovieClip *allocMatrixLabel = new MovieClip("Allocation Matrix", "Arial", 18);
	nextcontainer->addChild(allocMatrixLabel);
	allocMatrix = new TextInputClip*[pro];
	for (int i = 0; i < pro; i++) {
		allocMatrix[i] = new TextInputClip(120, 20);
		allocMatrix[i]->y = allocMatrixLabel->h + 5 + (i * 20);
		nextcontainer->addChild(allocMatrix[i]);
	}
	MovieClip *maxMatrixLabel = new MovieClip("Max Matrix", "Arial", 18);
	MovieClip *n2container = new MovieClip();
	container->addChild(n2container);
	n2container->x = nextcontainer->x + allocMatrixLabel->w + 5;
	n2container->addChild(maxMatrixLabel);
	maxMatrix = new TextInputClip*[pro];
	for (int i = 0; i < pro; i++) {
		maxMatrix[i] = new TextInputClip(120, 20);
		maxMatrix[i]->y = maxMatrixLabel->h + 5 + (i * 20);
		n2container->addChild(maxMatrix[i]);
	}
}

void BKScreen::calc() {
	bp = pro;
	br = res;
	for (int i = 0; i < pro; i++) {
		std::istringstream allocStr(allocMatrix[i]->text);
		std::istringstream maxStr(maxMatrix[i]->text);
		for (int j = 0; j < res; j++) {
			allocStr >> ballocate[i][j];
			maxStr >> bmax[i][j];
		}
	}
	read();
	displayNeedMatrix();
	bool s = check_safe();
	displaySafe(s);
	if (s)
		displayRequestMenu();
	displayResult();
}

void BKScreen::displayNeedMatrix()
{
	MovieClip *needcontainer = new MovieClip();
	needcontainer->x = 10;
	needcontainer->y = 100;
	MovieClip *needLabel = new MovieClip("Need Matrix", "Arial", 18);
	needcontainer->addChild(needLabel);
	for (int i = 0; i < pro; i++) {
		MovieClip *needMatrixRow = new MovieClip(120, 20, { 255,255,255,255 });
		std::stringstream needMatrixStr;
		for (int j = 0; j < res; j++) {
			needMatrixStr << bneed[i][j] << " ";
		}
		MovieClip *needMatrixText = new MovieClip(needMatrixStr.str(), "Arial", 18);
		needMatrixRow->addChild(needMatrixText);
		needMatrixRow->y = needLabel->h + 5 + (i * 20);
		needcontainer->addChild(needMatrixRow);
	}
	container->addChild(needcontainer);
}

void BKScreen::displayResult()
{
	if (avail != NULL || safeseq != NULL) {
		container->removeChild(avail);
		container->removeChild(safeseq);
		delete safeseq;
		delete avail;
	}
	focus = 0;
	MovieClip *safeseqLabel = new MovieClip("Safe Sequence", "Arial", 18);
	safeseqLabel->x = 0;
	safeseqLabel->y = 260;
	container->addChild(safeseqLabel);
	MovieClip *availLabel = new MovieClip("Availability", "Arial", 18);
	availLabel->x = 200;
	availLabel->y = 100;
	container->addChild(availLabel);
	avail = new MovieClip(120, 20, { 255,255,255,255 });
	avail->x = 200;
	avail->y = 130;
	MovieClip *ate = new MovieClip("", "Arial", 32);
	avail->addChild(ate);
	container->addChild(avail);
	safeseq = new MovieClip(240, 80, { 211,211,211,255 });
	safeseq->y = 290;
	MovieClip *textEntry = new MovieClip("", "Arial", 32);
	textEntry->y = (safeseq->h - textEntry->h) / 2;
	safeseq->addChild(textEntry);
	container->addChild(safeseq);
	LeftButton *l = new LeftButton();
	l->y = 200;
	l->target = &ml;
	RightButton *r = new RightButton();
	r->y = 200;
	r->x = 110;
	r->target = &mr;
	container->addChild(l);
	container->addChild(r);
}

void BKScreen::moveLeft()
{
	focus = std::max(focus - 1, 0);
	std::stringstream ssStr;
	for (int i = 0; i < focus; i++)
		ssStr << bpos[i] << " ";
	container->removeChild(safeseq);
	delete safeseq;
	safeseq = new MovieClip(240, 80, { 211,211,211,255 });
	safeseq->y = 290;
	MovieClip *textEntry = new MovieClip(ssStr.str(), "Arial", 32);
	textEntry->y = (safeseq->h - textEntry->h) / 2;
	safeseq->addChild(textEntry);
	container->addChild(safeseq);

	ssStr.clear();
	ssStr.str("");
	for (int i = 0; i<res; i++)
		ssStr << bavail[focus][i] << " ";
	container->removeChild(avail);
	avail = new MovieClip(120, 20, { 255,255,255,255 });
	avail->x = 200;
	avail->y = 130;
	MovieClip *ate = new MovieClip(ssStr.str(), "Arial", 18);
	avail->addChild(ate);
	container->addChild(avail);
}

void BKScreen::moveRight()
{
	focus = std::min(focus + 1, bpcount);
	std::stringstream ssStr;
	for (int i = 0; i < focus; i++)
		ssStr << bpos[i] << " ";
	container->removeChild(safeseq);
	delete safeseq;
	safeseq = new MovieClip(240, 80, { 211,211,211,255 });
	safeseq->y = 290;
	MovieClip *textEntry = new MovieClip(ssStr.str(), "Arial", 32);
	textEntry->y = (safeseq->h - textEntry->h) / 2;
	safeseq->addChild(textEntry);
	container->addChild(safeseq);

	ssStr.clear();
	ssStr.str("");
	for (int i = 0; i<res; i++)
		ssStr << bavail[focus][i] << " ";
	container->removeChild(avail);
	avail = new MovieClip(120, 20, { 255,255,255,255 });
	avail->x = 200;
	avail->y = 130;
	MovieClip *ate = new MovieClip(ssStr.str(), "Arial", 18);
	avail->addChild(ate);
	container->addChild(avail);
}

void BKScreen::displaySafe(bool s)
{
	if (safeLabel != NULL) {
		container->removeChild(safeLabel);
		delete safeLabel;
	}
	safeLabel = new MovieClip(s ? "System is safe" : "System is unsafe", "Arial", 24);
	safeLabel->x = 200;
	safeLabel->y = 260;
	container->addChild(safeLabel);
}

void BKScreen::displayRequestMenu()
{
	if (reqmenu != NULL) {
		container->removeChild(reqmenu);
		delete reqmenu;
	}
	reqmenu = new MovieClip();
	reqmenu->x = 640 - 200;
	reqmenu->y = 260;
	MovieClip *requestMenuLabel = new MovieClip("Process: ", "Arial", 18);
	reqmenu->addChild(requestMenuLabel);
	pInput = new TextInputClip(20, 20);
	pInput->x = requestMenuLabel->w + 5;
	reqmenu->addChild(pInput);
	MovieClip *resreqLabel = new MovieClip("Request: ", "Arial", 18);
	resreqInput = new ReqInput();
	resreqInput->x = pInput->x;
	resreqInput->y = requestMenuLabel->h + 5;
	resreqLabel->y = requestMenuLabel->h + 5;
	reqmenu->addChild(resreqLabel);
	reqmenu->addChild(resreqInput);
	container->addChild(reqmenu);
}

void BKScreen::processRequest()
{
	std::istringstream pStr(pInput->text);
	pStr >> bpro;
	bpro++;
	std::istringstream rrStr(resreqInput->text);
	for (int i = 0; i < res; i++)
		rrStr >> brq[i];
	bool s = check_request_allocate();
	displayGranted(s);
	if (s) {
		read();
		bool s2 = check_safe();
		displaySafe(s2);
		displayResult();
	}
}

void BKScreen::displayGranted(bool s)
{
	if (grantedLabel != NULL) {
		container->removeChild(grantedLabel);
		delete grantedLabel;
	}
	grantedLabel = new MovieClip(s ? "Request Granted" : "Request not Granted", "Arial", 24);
	grantedLabel->x = 640 - 200;
	grantedLabel->y = 310;
	container->addChild(grantedLabel);
}

NextButton::NextButton() : MouseClip(80,40,{211,211,211,255})
{
	MovieClip *nextText = new MovieClip("Next", "Myriad Pro Regular", 18);
	addChild(nextText);
}

void NextButton::onMouseUp()
{
	*target = true;
}

LeftButton::LeftButton() : MouseClip(50, 50, { 211,211,211,255 })
{
	MovieClip *label = new MovieClip("<", "Arial", 48);
	label->x = (w - label->w) / 2;
	label->y = (h - label->h) / 2;
	addChild(label);
}

void LeftButton::onMouseUp()
{
	*target = true;
}

RightButton::RightButton() : MouseClip(50, 50, { 211,211,211,255 })
{
	MovieClip *label = new MovieClip(">", "Arial", 48);
	label->x = (w - label->w) / 2;
	label->y = (h - label->h) / 2;
	addChild(label);
}

void RightButton::onMouseUp()
{
	*target = true;
}

ReqInput::ReqInput() : TextInputClip(120,20)
{

}

void ReqInput::onTextSubmit()
{
	((BKScreen*)Window.screen)->processRequest();
}
