#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

int cp[100];
int lf[100];
int rg[100];

vector <int> GD;
int l, r;

int clook(int h, int pr, int c) {
	int ans = 0, i;
	
	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(h);
		for (i = l-1; i >= 0; i++) {
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);		
		}
		
		for (i = r-1; i >= 0; i++) {
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


void printGantt(){
	for(vector<int>::iterator it=GD.begin(); it!=GD.end(); it++){
		cout << *it <<"    "<< endl; 
	}
}

int main() {
	int n, i, j;
	int header;
	int prevreq;
	int cyl;
	cout << "Enter number of requests: ";
	cin >> n;
	cout << "Enter header: ";
	cin >> header;
	cout << "Enter prev. request: ";
	cin >> prevreq;
	cout << "Enter cylinders: ";
	cin >> cyl;
	l = r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp;
		cout << "Enter request "<< i  << ": ";
		cin >> reqtmp;
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}
	for (i = 0; i < l - 1; i++) {
		for (j = 0; j < l - i - 1; j++) {
			if (lf[j] > lf[j + 1]) {
				int tmp = lf[j];
				lf[j] = lf[j + 1];
				lf[j + 1] = tmp;
			}
		}
	}
	for (i = 0; i < r - 1; i++) {
		for (j = 0; j < r - i - 1; j++) {
			if (rg[j] > rg[j + 1]) {
				int tmp = rg[j];
				rg[j] = rg[j + 1];
				rg[j + 1] = tmp;
			}
		}
	}
	cout << "Seek Time: " <<  clook(header, prevreq, cyl) << endl;
	printGantt();
	return 0;
}

//9 143 125 5000 86 1470 913 1774 948 1509 1022 1750 130
