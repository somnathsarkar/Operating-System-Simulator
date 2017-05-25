#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<algorithm>

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

int fcfs(std::vector<int>& GD){
	int ans = 0;
	GD.push_back(header);
	ans += abs(header - req[0]);
	int curr = req[0];
	GD.push_back(curr);
	for(int i =1; i<n; i++){
		ans += abs(curr - req[i]);
		curr = req[i];
		GD.push_back(curr);
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
	}
	printf("Total Seek Time: %d\n", sstf());
	printGantt();
	return 0;
}
