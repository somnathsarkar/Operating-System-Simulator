#include "PGScreen.h"

using namespace std;

int PGScreen::frequency(int arr[], int frame, int k)
{
	int count = 0;
	for (int i = k; i >= 0; i--)
		if (arr[i] == frame)
			count++;

	if (count != 0)
		return count;
	return -1;
}


void PGScreen::mfu(int arr[], int pages[], int curr, int size, int num_of_frames) {

	int index[100], i;
	if (size < num_of_frames)
		arr[size] = pages[curr];
	else
	{
		for (i = 0; i <size; i++)
			index[i] = frequency(pages, arr[i], curr - 1);
		i = max(index, size);
		arr[i] = pages[curr];

	}
}

void PGScreen::lfu(int arr[], int pages[], int curr, int size, int num_of_frames) {

	int index[100], i;
	if (size < num_of_frames)
		arr[size] = pages[curr];
	else
	{
		for (i = 0; i <size; i++)
			index[i] = frequency(pages, arr[i], curr - 1);
		i = min(index, size);
		arr[i] = pages[curr];

	}
}

int PGScreen::display(int arr[], int size, int cnt, int outputmat[][100], int index)
{
	if (size >= cnt + 1)
		size = cnt;
	for (int i = 0; i<size; i++)
	{
		cout << arr[i] << " ";
		outputmat[index][i] = arr[i];
	}

	index++;
	cout << endl << endl;
	return index;
}

int PGScreen::check(int arr[], int page, int size)
{
	for (int i = 0; i<size; i++)
		if (arr[i] == page)
			return 1;
	return 0;
}

int PGScreen::lastuse(int arr[], int frame, int k)
{
	for (int i = k; i >= 0; i--)
		if (arr[i] == frame)
			return i;
	return -1;
}

int PGScreen::nextuse(int arr[], int frame, int size, int k)
{
	for (int i = k; i<size; i++)
		if (arr[i] == frame)
			return i;
	return 1000;
}

int PGScreen::min(int arr[], int size)
{
	int i, min = 0;
	for (i = 1; i<size; i++)
		if (arr[i] < arr[min])
			min = i;
	return min;
}

int PGScreen::max(int arr[], int size)
{
	int i, min = 0;
	for (i = 1; i<size; i++)
		if (arr[i] > arr[min])
			min = i;
	return min;
}

void PGScreen::fifo(int arr[], int page, int size)
{
	static int track = 1;
	arr[track] = page;
	track = (track + 1) % size;
}

void PGScreen::optimal(int arr[], int pages[], int curr, int size, int num_of_frames, int num_of_pages)
{
	int index[100], i;
	if (size < num_of_frames)
		arr[size] = pages[curr];
	else
	{
		for (i = 0; i<size; i++)
			index[i] = nextuse(pages, arr[i], num_of_pages, curr + 1);
		i = max(index, size);
		arr[i] = pages[curr];
	}
}

void PGScreen::lru(int arr[], int pages[], int curr, int size, int num_of_frames)
{
	int index[100], i;
	if (size < num_of_frames)
		arr[size] = pages[curr];
	else
	{
		for (i = 0; i<size; i++)
			index[i] = lastuse(pages, arr[i], curr - 1);
		i = min(index, size);
		arr[i] = pages[curr];
	}
}

void PGScreen::pagemain()
{
	num_of_faults = 0, index = 0, num_of_hits = 0;
	/*cout<<"Enter number of pages: ";
	cin>>num_of_pages;
	cout<<"Enter page sequence: ";
	for (i=0;i<num_of_pages;i++)
	cin>>pages[i];
	cout<<"Enter number of frames: ";
	cin>>num_of_frames;
	cout<<"The page replacement algorithms are:\n1. FIFO\n2. Optimal\n3. LRU\nEnter choice:";
	cin>>choice;*/
	cout << "Fault -> ";
	num_of_faults++;
	frames[0] = pages[0];
	index = display(frames, num_of_frames, num_of_faults, outputmat, index);
	i = 1;

	while (i < num_of_pages)
	{
		if (num_of_faults < num_of_frames)
			size = num_of_faults;
		else
			size = num_of_frames;
		if (!check(frames, pages[i], size))
		{
			cout << "Fault -> ";
			if (choice == 1)
				fifo(frames, pages[i], num_of_frames);
			else if (choice == 2)
				optimal(frames, pages, i, size, num_of_frames, num_of_pages);
			else if (choice == 3)
				lru(frames, pages, i, size, num_of_frames);
			else if(choice==4)
				lfu(frames, pages, i, size, num_of_frames);
			else if(choice==5)
				mfu(frames, pages, i, size, num_of_frames);
			num_of_faults++;
		}
		else
		{
			cout << "Hit -> ";
			num_of_hits++;
		}
		index = display(frames, num_of_frames, num_of_faults, outputmat, index);
		i++;
	}

	//FINAL OUTPUT TO BE USED FOR GUI
	//state after each page request is stored in outputmat
	for (i = 0; i<index; i++)
	{
		for (int j = 0; j<num_of_frames; j++)
			cout << outputmat[i][j] << " ";
		cout << endl;
	}
}

void PGScreen::updateFrames()
{
	if (fb != NULL) {
		for (int i = 0; i < num_of_frames; i++) {
			container->removeChild(fb[i]);
			delete fb[i];
		}
		delete[] fb;
	}
	std::istringstream fStr(fi->text);
	fStr >> num_of_frames;
	fb = new FrameBlock*[num_of_frames];
	int tw = (640-((100 * num_of_frames) + (6 * (num_of_frames - 1))))/2;
	for (int i = 0; i < num_of_frames; i++) {
		fb[i] = new FrameBlock();
		fb[i]->x = tw + (100 * i) + (6 * (i));
		fb[i]->y = 20;
		container->addChild(fb[i]);
	}
}

void PGScreen::updatePages()
{
	std::istringstream pStr(pi->text);
	num_of_pages = 0;
	while(pStr >> pages[num_of_pages++]);
	//for (int i = 0; i < num_of_pages; i++)
		//printf("%d\n", pages[i]);
	num_of_pages--;
	compute();
}

void PGScreen::compute()
{
	choice = ch;
	pagemain();
	focus = 0;
	displayControls();
	updateLabels();
	updateDisplay();
}

void PGScreen::displayControls()
{
	if (l != NULL&&r != NULL)
		return;
	l = new LeftButton();
	l->x = 320 - 50 - 10;
	l->y = 100 + 20 + 10;
	l->target = &ml;
	container->addChild(l);
	
	r = new RightButton();
	r->x = 320 + 10;
	r->y = 100 + 20 + 10;
	r->target = &mr;
	container->addChild(r);
}

void PGScreen::updateDisplay()
{
	for (int j = 0; j < num_of_frames; j++)
		fb[j]->changeValue(outputmat[focus][j]);
}

void PGScreen::updateLabels()
{
	if (numFaults != NULL&&numHits != NULL) {
		container->removeChild(numFaults);
		container->removeChild(numHits);
		delete numFaults;
		delete numHits;
	}
	std::stringstream str;
	str << "Number of Faults: " << num_of_faults;
	numFaults = new MovieClip(str.str(), "Myriad Pro Regular", 24);
	str.clear();
	str.str("");
	str << "Number of Hits: " << num_of_hits;
	numHits = new MovieClip(str.str(), "Myriad Pro Regular", 24);
	numFaults->x = 640 - numFaults->w;
	numHits->x = 640 - numHits->w;
	numFaults->y = 480 - 40 - 30;
	numHits->y = 480 - 40 - 30 - 30;
	container->addChild(numHits);
	container->addChild(numFaults);
}

PGScreen::PGScreen()
{
	ch = 1;
	frameUpdate = pageUpdate = ml = mr = choicechange = false;
	destination = ScreenType::PG_SCREEN;
}

void PGScreen::init()
{
	fb = NULL;
	fi = NULL;
	pi = NULL;
	em = new ESCMenu(ScreenType::MAIN_SCREEN, &destination);
	Window.stage->addChild(em);
	container = new MovieClip(640, 480, { 139,0,0,255 });
	Window.stage->addChild(container);
	
	//fi
	fi = new FrameInput();
	fi->y = 400;
	container->addChild(fi);
	fi->target = &frameUpdate;

	//pi
	pi = new PageInput();
	pi->y = 440;
	container->addChild(pi);
	pi->target = &pageUpdate;

	//buttons
	PageButton *pb1 = new PageButton(1, "FIFO");
	pb1->x = 440;
	pb1->y = 440-60;
	pb1->target = &choicechange;
	pb1->targetchoice = &ch;
	container->addChild(pb1);
	PageButton *pb2 = new PageButton(2, "OPT");
	pb2->x = 440;
	pb2->y = 440-120;
	pb2->target = &choicechange;
	pb2->targetchoice = &ch;
	container->addChild(pb2);
	PageButton *pb3 = new PageButton(3, "LRU");
	pb3->x = 440;
	pb3->y = 440-180;
	pb3->target = &choicechange;
	pb3->targetchoice = &ch;
	container->addChild(pb3);
	PageButton *pb4 = new PageButton(4, "LFU");
	pb4->x = 440;
	pb4->y = 440-240;
	pb4->target = &choicechange;
	pb4->targetchoice = &ch;
	container->addChild(pb4);
	PageButton *pb5 = new PageButton(5, "MFU");
	pb5->x = 440;
	pb5->y = 440-300;
	pb5->target = &choicechange;
	pb5->targetchoice = &ch;
	container->addChild(pb5);
}

ScreenType PGScreen::mainLoop()
{
	if (frameUpdate) {
		frameUpdate = false;
		updateFrames();
	}
	if (pageUpdate) {
		pageUpdate = false;
		updatePages();
	}
	if (ml) {
		ml = false;
		focus = std::max(0, focus - 1);
		updateDisplay();
	}
	if (mr) {
		mr = false;
		focus = std::min(index, focus + 1);
		updateDisplay();
	}
	if (choicechange) {
		choicechange = false;
		compute();
	}
	return destination;
}

void PGScreen::exit()
{
	Window.stage->removeChild(container);
	Window.stage->removeChild(em);
	delete em;
	delete container;
}

FrameBlock::FrameBlock() : MovieClip(100,100)
{
	MovieClip *tmp = new MovieClip();
	addChild(tmp);
	numval = tmp;
}

void FrameBlock::changeValue(int x)
{
	removeChild(numval);
	delete numval;
	std::stringstream str;
	str << x;
	numval = new MovieClip(str.str(), "Myriad Pro Regular", 32);
	numval->x = (w - numval->w) / 2;
	numval->y = (h - numval->h) / 2;
	addChild(numval);
}

FrameInput::FrameInput() : TextInputClip(40, 40)
{
}

void FrameInput::onTextSubmit()
{
	*target = true;
}

PageInput::PageInput() : TextInputClip(640, 40)
{
}

void PageInput::onTextSubmit()
{
	*target = true;
}

PageButton::PageButton(int x, std::string name) : MouseClip(80, 60, { 211,211,211,255 })
{
	MovieClip * tmc = new MovieClip(name, "Arial", 24);
	tmc->x = (w - tmc->w)/2;
	tmc->y = (h - tmc->h) / 2;
	chval = x;
	addChild(tmc);
}

void PageButton::onMouseUp()
{
	*target = true;
	*targetchoice = chval;
}
