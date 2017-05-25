#include <iostream>
#include<cmath>
#include<vector>
#include<stdio.h>

using namespace std;

int cp[100];
int lf[100];
int rg[100];

int l, r;

vector<int> GD;

int scanalgo(int h, int pr, int c) {
	int ans = 0,i;
	if (pr >= h) {
		//lf first
		int curr = h;
		GD.push_back(curr);
		for (i = 0; i < l; i++){
			ans += curr - lf[i];
			curr = lf[i];
			GD.push_back(curr);
		}
		ans += curr;
		curr = 0;
		GD.push_back(curr);
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
		
		ans += c-curr-1;
		curr = c-1;
		GD.push_back(curr);
		for (i = 0; i < l; i++) {
			
			ans += curr - lf[i];
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
	int n,i,j;
	int header;
	int prevreq;
	int cyl;
	printf("Enter number of requests: ");
	scanf("%d", &n);
	printf("Enter header: ");
	scanf("%d", &header);
	printf("Enter prev. request: ");
	scanf("%d", &prevreq);
	printf("Enter cylinders: ");
	scanf("%d", &cyl);
	l = r = 0;
	for (int i = 0; i < n; i++) {
		int reqtmp;
		printf("Enter request %d: ", i);
		scanf("%d", &reqtmp);
		if (reqtmp < header)
			lf[l++] = reqtmp;
		else
			rg[r++] = reqtmp;
	}
	for (i = 0; i < l-1; i++) {
		for (j = 0; j < l - i - 1; j++) {
			if (lf[j] < lf[j + 1]) {
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
	printf("Seek Time: %d\n",scanalgo(header,prevreq,cyl));
	printGantt();
	return 0;
}
