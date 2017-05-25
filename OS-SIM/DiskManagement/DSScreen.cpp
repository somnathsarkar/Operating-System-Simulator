#include "DSScreen.h"

int DSScreen::fcfs(std::vector<int>& GD) {
	GD.clear();
	int ans = 0;
	GD.push_back(header);
	if (n) {
		ans += abs(header - req[0]);
		int curr = req[0];
		GD.push_back(curr);
		for (int i = 1; i < n; i++) {
			ans += abs(curr - req[i]);
			curr = req[i];
			GD.push_back(curr);
		}
	}
	return ans;
}

int DSScreen::look(std::vector<int>& GD, int h, int pr, int c) {
	GD.clear();
	int lf[100],rg[100];
	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp = req[i];
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}
	std::sort(lf, lf + l);
	std::sort(rg, rg + r);
	int ans = 0, i;
	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < l; i++) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}
		for (i = 0; i < r; i++) {
			ans += rg[i] - curr;
			curr = rg[i];
			GD.push_back(curr);
		}
	}
	else {
		//rg first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < r; i++) {
			ans += rg[i] - curr;
			curr = rg[i];
			GD.push_back(curr);
		}
		for (i = 0; i < l; i++) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}
	}
	return ans;
}

int DSScreen::sstf(std::vector<int>& GD) {
	GD.clear();
	int cp[100];
	for (int i = 0; i < 100; i++)
		cp[i] = 0;
	int reqdone = 0;
	int ans = 0;
	int curr = header;
	GD.push_back(curr);
	int nextup = -1;
	int nextseek = 100000;
	while (reqdone < n) {
		for (int i = 0; i < n; i++) {
			if ((!cp[i]) && (abs(req[i] - curr) < nextseek)) {
				nextseek = abs(req[i] - curr);
				nextup = i;
			}
		}
		cp[nextup] = 1;
		curr = req[nextup];
		GD.push_back(curr);
		ans += nextseek;
		nextseek = 100000;
		reqdone++;
	}
	return ans;
}

int DSScreen::clook(std::vector<int>& GD, int h, int pr, int c) {
	GD.clear();
	int lf[100], rg[100];
	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp = req[i];
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}

	std::sort(lf, lf + l);
	std::sort(rg, rg + r);
	int ans = 0, i;

	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(h);
		for (i = l - 1; i >= 0; i--) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}

		for (i = r - 1; i >= 0; i--) {
			ans += abs(rg[i] - curr);
			curr = rg[i];
			GD.push_back(curr);
		}
	}
	else {
		//rg first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < r; i++) {
			ans += rg[i] - curr;
			curr = rg[i];
			GD.push_back(curr);
		}
		for (i = 0; i < l; i++) {
			ans += abs(curr - lf[i]);
			curr = lf[i];
			GD.push_back(curr);
		}
	}
	return ans;
}

int DSScreen::cscan(std::vector<int>& GD, int h, int pr, int c) {
	GD.clear();
	int lf[100], rg[100];
	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp = req[i];
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}

	std::sort(lf, lf + l);
	std::sort(rg, rg + r);
	int ans = 0, i;

	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(h);
		for (i = l - 1; i >= 0; i--) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}
		if (r) {
			ans += curr;
			GD.push_back(0);
			curr = c - 1;
			GD.push_back(curr);
			for (i = r - 1; i >= 0; i--) {
				ans += abs(rg[i] - curr);
				curr = rg[i];
				GD.push_back(curr);
			}
		}
	}
	else {
		//rg first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < r; i++) {
			ans += rg[i] - curr;
			curr = rg[i];
			GD.push_back(curr);
		}
		if (l) {
			ans += c - curr - 1;
			GD.push_back(c - 1);
			curr = 0;
			GD.push_back(curr);
			for (i = 0; i < l; i++) {
				ans += abs(curr - lf[i]);
				curr = lf[i];
				GD.push_back(curr);
			}
		}
	}
	return ans;
}

int DSScreen::scan(std::vector<int>& GD, int h, int pr, int c) {
	GD.clear();
	int lf[100], rg[100];
	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp = req[i];
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}

	std::sort(lf, lf + l);
	std::sort(rg, rg + r);
	int ans = 0, i;
	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < l; i++) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}
		if (r) {
			ans += curr;
			curr = 0;
			GD.push_back(curr);
			for (i = 0; i < r; i++) {
				ans += rg[i] - curr;
				curr = rg[i];
				GD.push_back(curr);
			}
		}
	}
	else {
		//rg first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < r; i++) {

			ans += rg[i] - curr;
			curr = rg[i];
			GD.push_back(curr);
		}
		if (l) {
			ans += c - curr - 1;
			curr = c - 1;
			GD.push_back(curr);
			for (i = 0; i < l; i++) {

				ans += curr - lf[i];
				curr = lf[i];
				GD.push_back(curr);
			}
		}
	}
	return ans;
}

void DSScreen::compute()
{
	ds[0]->seektime = fcfs(ds[0]->dc->GD);
	ds[1]->seektime = sstf(ds[1]->dc->GD);
	ds[2]->seektime = scan(ds[2]->dc->GD,header,preq,cyl);
	ds[3]->seektime = cscan(ds[3]->dc->GD, header, preq, cyl);
	ds[4]->seektime = look(ds[4]->dc->GD, header, preq, cyl);
	ds[5]->seektime = clook(ds[5]->dc->GD, header, preq, cyl);
	for (int i = 0; i < 6; i++)
		ds[i]->dc->display(cyl);
	updateDisplay();
}

void DSScreen::updateInputs()
{
	std::istringstream driStr(dri->text);
	n = 0;
	while (driStr >> req[n++]);
	n--;
	printf("UI: %d\n", n);
	std::istringstream dhiStr(dhi->text);
	dhiStr >> header;
	std::istringstream dpiStr(dpi->text);
	dpiStr >> preq;
	std::istringstream dciStr(dci->text);
	dciStr >> cyl;
	compute();
}

void DSScreen::updateDisplay()
{
	if (dseek != NULL){
		container->removeChild(dseek);
		dseek->children.clear();
		delete dseek;
		container->removeChild(dcc);
		dcc->children.clear();
		delete dcc;
		container->removeChild(dtitle);
		dtitle->children.clear();
		delete dtitle;
	}
	dcc = new MovieClip();
	dcc->x = 340;
	dcc->y = 0;
	dcc->addChild(ds[focus]->dc);
	container->addChild(dcc);
	dtitle = new MovieClip(ds[focus]->name,"Myriad Pro Regular",32);
	dtitle->x = 60;
	dtitle->y = 10;
	container->addChild(dtitle);
	std::stringstream str;
	str << "Seek Time: " << ds[focus]->seektime;
	dseek = new MovieClip(str.str(), "Myriad Pro Regular", 24);
	dseek->x = 60;
	dseek->y = 70;
	container->addChild(dseek);
}

DSScreen::DSScreen()
{
	focus = 0;
	dcc = dtitle = dseek = NULL;
	destination = ScreenType::DS_SCREEN;
}

void DSScreen::init()
{
	focus = 0;
	reqsubmit = false;
	tl = tr = false;
	em = new ESCMenu(ScreenType::MAIN_SCREEN, &destination);
	container = new MovieClip(640, 480, { 191,87,0,255 });
	Window.stage->addChild(container);
	Window.stage->addChild(em);
	dri = new DInput();
	dri->y = 440;
	dri->target = &reqsubmit;
	container->addChild(dri);
	dhi = new DInput(40, 20);
	dhi->y = 410;
	dhi->target = &reqsubmit;
	dhi->textInput("50");
	container->addChild(dhi);
	dpi = new DInput(40, 20);
	dpi->y = 410;
	dpi->x = 45;
	dpi->target = &reqsubmit;
	dpi->textInput("75");
	container->addChild(dpi);
	dci = new DInput(40, 20);
	dci->y = 410;
	dci->x = 90;
	dci->target = &reqsubmit;
	dci->textInput("100");
	container->addChild(dci);
	ds[0] = new DSoln("FCFS", cyl);
	ds[1] = new DSoln("SSTF", cyl);
	ds[2] = new DSoln("SCAN", cyl);
	ds[3] = new DSoln("CSCAN", cyl);
	ds[4] = new DSoln("LOOK", cyl);
	ds[5] = new DSoln("CLOOK", cyl);
	updateInputs();
	updateDisplay();
	l = new LeftButton();
	l->x = 10;
	l->y = 10;
	l->target = &tl;
	container->addChild(l);
	r = new RightButton();
	r->x = 330 - 50;
	r->y = 10;
	r->target = &tr;
	container->addChild(r);
}

ScreenType DSScreen::mainLoop()
{
	if (reqsubmit) {
		reqsubmit = false;
		updateInputs();
	}
	if (tl) {
		tl = false;
		focus = (focus - 1) < 0 ? 5 : focus - 1;
		updateDisplay();
	}
	if (tr) {
		tr = false;
		focus = (focus + 1) % 6;
		updateDisplay();
	}
	return destination;
}

void DSScreen::exit()
{
	Window.stage->removeChild(em);
	delete em;
	Window.stage->removeChild(container);
	delete container;
}

DInput::DInput(int w, int h) : TextInputClip(w,h)
{

}

void DInput::onTextSubmit()
{
	*target = true;
}

DClip::DClip(int c) : MovieClip(300, 440, { 184,184,184,255 }) {
	cyl = c;
	GD.clear();
	display(100);
}

void DClip::display(int c)
{
	cyl = c;
	for (auto &it : children)
		delete it;
	children.clear();
	int len = GD.size();
	int lens = 480 - 20;
	int lenc = 300 - 20;
	for (int i = 0; i < len; i++) {
		DUnit *du = new DUnit(GD[i]);
		du->y = (i*lens) / len;
		du->x = (GD[i] * lenc) / cyl;
		addChild(du);
	}
}

DUnit::DUnit(int x):MouseClip(20,20)
{
	this->loc = x;
	dc = new DContext(x);
	Window.stage->addChild(dc);
}

DUnit::~DUnit()
{
	Window.stage->removeChild(dc);
}

void DUnit::onMouseOver()
{
	printf("DSAD");
	dc->visible = true;
}

void DUnit::onMouseOut()
{
	dc->visible = false;
}

DContext::DContext(int x)
{
	visible = false;
	std::stringstream dStr;
	dStr << x;
	this->loc = x;
	tmc = new MovieClip(dStr.str(), "Myriad Pro Regular", 18);
	tmc->x = (w - tmc->w) / 2;
	tmc->y = (h - tmc->h) / 2;
	addChild(tmc);
}

void DContext::processEvent(SDL_Event & e)
{
	if (!visible)
		return;
	int mx, my;
	switch (e.type) {
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mx, &my);
		x = mx - w;
		y = my - h;
	}
}

void DContext::render(int x, int y)
{
	if (visible) {
		int nx = (this->x) + x, ny = (this->y) + y;
		absX = nx;
		absY = ny;
		texture->render(renderer, nx + tx, ny + ty);
		for (auto &it : children)
			it->render(nx, ny);
	}
}

DSoln::DSoln(std::string name, int cyl)
{
	this->name = name;
	dc = new DClip(cyl);
	seektime = 0;
}
