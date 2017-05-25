#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>

using namespace std;

vector<int> GD;

int req[100];
int cp[100];
int n,header;

void printGantt(){
	for(vector<int>::iterator it=GD.begin(); it!=GD.end(); it++){
		cout << *it <<"    "<< endl; 
	}
}

int sstf(){
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

int main() {
	
	printf("Enter number of requests: ");
	scanf("%d", &n);
	printf("Enter header: ");
	scanf("%d", &header);
	int i;
	for (i = 0; i < n; i++) {
		printf("Enter request %d: ", i);
		scanf("%d", &req[i]);
		cp[i] = 0;
	}
	
	printf("Total Seek Time: %d\n", sstf());
	printGantt();
	return 0;
}
