#include "PSScreen.h"

int qc, qs;

pro Pq[100];

bool compat(pro &a, pro &b) {
	return a.at < b.at;
}

bool compno(pro &a, pro &b) {
	return a.pno < b.pno;
}

void swapp(struct pro *a, struct pro *b) {
	struct pro tmp = *a;
	*a = *b;
	*b = tmp;
}

void push(struct pro a) {
	Pq[qs + qc] = a;
	int i = qs + qc - 1;
	qc++;
	while (i >= qs&&Pq[i + 1].bt<Pq[i].bt) {
		swapp(&Pq[i], &Pq[i + 1]);
		i--;
	}
}

void push2(struct pro a) {
	Pq[qs + qc] = a;
	qc++;
}

void push3(struct pro a) {
	Pq[qs + qc] = a;
	int i = qs + qc - 1;
	qc++;
	while (i >= qs&&Pq[i + 1].priority>Pq[i].priority) {
		swapp(&Pq[i], &Pq[i + 1]);
		i--;
	}
}

struct pro pop() {
	qc--;
	return Pq[qs++];
}

void fcfs(int p, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int i;
	int t = 0;
	for (i = 0; i<p; i++) {
		if (t<P[i].at)
			t = P[i].at;
		tmp.pno = P[i].pno;
		tmp.st = t;
		tmp.readyqueue.clear();
		for (int j = i; j<p&&P[j].at <= t; j++)
			tmp.readyqueue.push_back(std::make_pair(P[j].pno, P[j].at));
		t += P[i].bt;
		tmp.et = t - 1;
		GC.push_back(tmp);
		P[i].ct = t;
	}
	for (i = 0; i<p; i++) {				//calculating tat and wt
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		atat += P[i].tat;
		awt += P[i].wt;
	}
	atat /= p;
	awt /= p;
}

void sjf(int p, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	qs = 0, qc = 0;
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int i = 0;
	int t = 0;
	while (i<p || qc) {
		while (i<p&&P[i].at <= t) {
			push(P[i]);
			i++;
		}
		if (!qc)
			t = P[i].at;
		else {
			struct pro exec_pro = pop();
			tmp.pno = exec_pro.pno;
			tmp.st = t;
			tmp.readyqueue.clear();
			tmp.readyqueue.push_back(std::make_pair(exec_pro.pno, exec_pro.bt));
			for (int i = qs; i < qs + qc; i++)
				tmp.readyqueue.push_back(std::make_pair(Pq[i].pno, Pq[i].bt));
			t += exec_pro.bt;
			tmp.et = t - 1;
			P[exec_pro.id].ct = t;
			GC.push_back(tmp);
		}
	}
	for (i = 0; i<p; i++) {				//calculating tat and wt
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		atat += P[i].tat;
		awt += P[i].wt;
	}
	atat /= p;
	awt /= p;
	//atatt[0] = atat;				//storing atat and awt
	//awtt[0] = awt;
}

void srtf(int n, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	qs = 0, qc = 0;
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int t = 0;
	int i = 0;
	while (i < n || qc) {
		while (i < n&&P[i].at <= t) {
			push(P[i]);
			i++;
		}
		if (!qc)
			t = P[i].at;
		else {
			struct pro exec_pro = pop();
			tmp.pno = exec_pro.pno;
			int time_next = 100000;
			if (i < n)
				time_next = P[i].at;
			tmp.readyqueue.clear();
			tmp.readyqueue.push_back(std::make_pair(exec_pro.pno, exec_pro.bt));
			for (int j = qs; j < qs + qc; j++) 
				tmp.readyqueue.push_back(std::make_pair(Pq[j].pno, Pq[j].bt));
			if (t + exec_pro.bt <= time_next) {
				tmp.st = t;
				t += exec_pro.bt;
				tmp.et = t - 1;
				P[exec_pro.id].ct = t;
			}
			else {
				exec_pro.bt -= (time_next - t);
				tmp.st = t;
				t = time_next;
				tmp.et = t - 1;
				push(exec_pro);
			}
			GC.push_back(tmp);
		}
	}
	for (i = 0; i<n; i++) {				//calculating tat and wt
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		atat += P[i].tat;
		awt += P[i].wt;
	}
	atat /= n;
	awt /= n;
	//atatt[0] = atat;				//storing atat and awt
	//awtt[0] = awt;
}

void robin(int p, int tq, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	qs = 0, qc = 0;
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int t = 0;
	int i = 0;
	while (i<p || qc) {
		while (i<p&&P[i].at <= t) {
			push2(P[i]);
			i++;
		}
		if (!qc)
			t = P[i].at;
		else {
			struct pro exec_pro = pop();
			tmp.pno = exec_pro.pno;
			tmp.st = t;
			tmp.readyqueue.clear();
			tmp.readyqueue.push_back(std::make_pair(exec_pro.pno, exec_pro.at));
			for (int j = qs; j < qs + qc; j++)
				tmp.readyqueue.push_back(std::make_pair(Pq[j].pno, Pq[j].at));
			int texec = (tq<exec_pro.bt) ? tq : exec_pro.bt;
			exec_pro.bt -= texec;
			t += texec;
			tmp.et = t - 1;
			GC.push_back(tmp);
			while (i<p&&P[i].at <= t) {
				push2(P[i]);
				i++;
			}
			if (exec_pro.bt)
				push2(exec_pro);
			else
				P[exec_pro.id].ct = t;
		}
	}
}

void pri(int p, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	qs = 0, qc = 0;
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int i = 0;
	int t = 0;
	while (i<p || qc) {
		while (i<p&&P[i].at <= t) {
			push3(P[i]);
			i++;
		}
		if (!qc)
			t = P[i].at;
		else {
			struct pro exec_pro = pop();
			tmp.readyqueue.clear();
			tmp.readyqueue.push_back(std::make_pair(exec_pro.pno, exec_pro.priority));
			for (int j = qs; j < qs + qc; j++)
				tmp.readyqueue.push_back(std::make_pair(Pq[j].pno, Pq[j].priority));
			tmp.pno = exec_pro.pno;
			tmp.st = t;
			t += exec_pro.bt;
			tmp.et = t - 1;
			P[exec_pro.id].ct = t;
			GC.push_back(tmp);
		}
	}
	for (i = 0; i<p; i++) {				//calculating tat and wt
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		atat += P[i].tat;
		awt += P[i].wt;
	}
	atat /= p;
	awt /= p;
	//atatt[0] = atat;				//storing atat and awt
	//awtt[0] = awt;
}

void ppri(int n, std::vector<Gantt>& GC, pro* P) {
	GC.clear();
	qs = 0, qc = 0;
	double atat = 0, awt = 0;
	struct Gantt tmp;
	int t = 0;
	int i = 0;
	while (i < n || qc) {
		while (i < n&&P[i].at <= t) {
			push(P[i]);
			i++;
		}
		if (!qc)
			t = P[i].at;
		else {
			struct pro exec_pro = pop();
			tmp.readyqueue.clear();
			tmp.readyqueue.push_back(std::make_pair(exec_pro.pno, exec_pro.priority));
			for (int j = qs; j < qs + qc; j++)
				tmp.readyqueue.push_back(std::make_pair(Pq[j].pno, Pq[j].priority));
			tmp.pno = exec_pro.pno;
			int time_next = 100000;
			if (i < n)
				time_next = P[i].at;
			if (t + exec_pro.bt <= time_next) {
				tmp.st = t;
				t += exec_pro.bt;
				tmp.et = t - 1;
				P[exec_pro.id].ct = t;
			}
			else {
				exec_pro.bt -= (time_next - t);
				tmp.st = t;
				t = time_next;
				tmp.et = t - 1;
				push(exec_pro);
			}
			GC.push_back(tmp);
		}
	}
	for (i = 0; i<n; i++) {				//calculating tat and wt
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		atat += P[i].tat;
		awt += P[i].wt;
	}
	atat /= n;
	awt /= n;
	//atatt[0] = atat;				//storing atat and awt
	//awtt[0] = awt;
}

std::string getRand(int x, int y) {
	std::stringstream str;
	str.clear();
	str << (rand() % (y-x+1))+x;
	return str.str();
}

void printpro(int p, pro* P, double atat, double awt) {
	printf("P. No.\tAT\tBT\tCT\tTAT\tWT\n");
	int i;
	for (i = 0; i<p; i++)
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pno,P[i].at,P[i].bt,P[i].ct,P[i].tat,P[i].wt);
	printf("Average Turnaround Time: %f\n",atat);
	printf("Average Wait Time: %f\n", awt);
}

void printGantt(std::vector<Gantt> GC) {
	for (std::vector<Gantt>::iterator it = GC.begin(); it != GC.end(); it++) {
		printf(" P%d   \n",it->pno);
		printf("%d   %d\n", it->st, it->et);
	}
}

ScreenType PSScreen::mainLoop()
{
	if (gcContainer != NULL) {
		for (auto &it : gcContainer->children) {
			int newx = (((GanttClip*)it)->ganttroot->x + (((GanttClip*)it)->l->val) + (((GanttClip*)it)->r->val));
			if (((GanttClip*)it)->ganttroot->w>640) {
				int lim = 640 - ((GanttClip*)it)->ganttroot->w;
				if (newx < lim)
					newx = lim;
			}
			else
				newx = 0;
			if (newx > 0)
				newx = 0;
			((GanttClip*)it)->ganttroot->x = newx;
		}
	}
	return destination;
}

void PSScreen::exit()
{
	Window.stage->removeChild(em);
	Window.stage->removeChild(container);
	delete em;
	if (container != NULL)
		delete container;
}

void PSScreen::processUpdate() {
	int p = psi->processInputs.size();
	pro *P = new pro[p];
	for (int i = 0; i < p; i++) {
		P[i].pno = i;
		P[i].at = std::stoi(((TextInputClip*)(psi->processInputs[i]->getChildAt(1)))->text);
		P[i].bt = std::stoi(((TextInputClip*)(psi->processInputs[i]->getChildAt(2)))->text);
		P[i].priority = std::stoi(((TextInputClip*)(psi->processInputs[i]->getChildAt(3)))->text);
	}
	if(gcContainer!=NULL)
		container->removeChild(gcContainer);
	delete gcContainer;
	gcContainer = new MovieClip();
	gcContainer->y = psi->h;
	GanttClip *fcfsg = new GanttClip("FCFS");
	GanttClip *sjfg = new GanttClip("SJF");
	GanttClip *srtfg = new GanttClip("SRTF");
	GanttClip *robing = new GanttClip("Round Robin");
	GanttClip *prig = new GanttClip("Priority");
	GanttClip *pprig = new GanttClip("Preemptive Priority");
	std::sort(P, P + p, compat);
	for (int i = 0; i < p; i++)
		P[i].id = i;
	fcfs(p, fcfsg->GC, P);
	printGantt(fcfsg->GC);
	sjf(p, sjfg->GC, P);
	srtf(p, srtfg->GC, P);
	robin(p, 2, robing->GC, P);
	pri(p, prig->GC, P);
	ppri(p, pprig->GC, P);
	printpro(p, P, 0, 0);
	printGantt(fcfsg->GC);
	fcfsg->display();
	sjfg->display();
	srtfg->display();
	robing->display();
	prig->display();
	pprig->display();
	gcContainer->addChild(fcfsg);
	gcContainer->addChild(sjfg);
	gcContainer->addChild(srtfg);
	gcContainer->addChild(robing);
	gcContainer->addChild(prig);
	gcContainer->addChild(pprig);
	fcfsg->y = 0;
	sjfg->y = fcfsg->y+fcfsg->h;
	srtfg->y = sjfg->y+sjfg->h;
	robing->y = srtfg->y+srtfg->h;
	prig->y = robing->y + robing->h;
	pprig->y = prig->y + prig->h;
	container->addChild(gcContainer);
	container->h = pprig->y + pprig->h + psi->h;
}

PSScreen::PSScreen()
{
	destination = ScreenType::PS_SCREEN;
}

void PSScreen::init()
{
	em = new ESCMenu(ScreenType::MAIN_SCREEN, &destination);
	Window.stage->addChild(em);
	container = new MouseClip();
	gcContainer = new MovieClip();
	psi = new PSInput();
	container->addChild(psi);
	gcContainer->y = psi->h;
	Window.stage->addChild(container);
	container->scrollable = true;
	container->scrollspeed = 10;
	container->w = 640;
}

PSInput::PSInput()
{
	MovieClip *processLabel = new MovieClip("Process", "Arial", 18);
	MovieClip *atLabel = new MovieClip("AT", "Arial", 18);
	MovieClip *btLabel = new MovieClip("BT", "Arial", 18);
	MovieClip *prLabel = new MovieClip("Priority", "Arial", 18);
	prLabel->x = 640 - 80;
	btLabel->x = prLabel->x - 80;
	atLabel->x = btLabel->x - 80;
	w = 640;
	h = processLabel->h;
	addChild(processLabel);
	addChild(atLabel);
	addChild(btLabel);
	addChild(prLabel);
	for (int i = 0; i < 5; i++)
	addProcess();
}

void PSInput::addProcess()
{
	MovieClip *newPI = new MovieClip();
	newPI->w = 640;
	newPI->h = 40;
	newPI->y = this->h;
	int pino = processInputs.size();
	std::stringstream str;
	str << "P" << pino;
	MovieClip *piLabel = new MovieClip(str.str(),"Arial",18);
	PSInputText *atInput = new PSInputText(80, 40);
	PSInputText *btInput = new PSInputText(80, 40);
	PSInputText *prInput = new PSInputText(80, 40);
	atInput->textInput(getRand(0,10));
	btInput->textInput(getRand(1,10));
	prInput->textInput(getRand(0,10));
	prInput->x = 640 - 80;
	btInput->x = prInput->x - 80;
	atInput->x = btInput->x - 80;
	newPI->addChild(piLabel);
	newPI->addChild(atInput);
	newPI->addChild(btInput);
	newPI->addChild(prInput);
	processInputs.push_back(newPI);
	addChild(newPI);
	h += newPI->h;
}

void PSInput::removeProcess(int x)
{

}

PSInputText::PSInputText(int w, int h) : TextInputClip(w, h)
{
}

void PSInputText::onTextSubmit()
{
	((PSScreen*)Window.screen)->processUpdate();
}
