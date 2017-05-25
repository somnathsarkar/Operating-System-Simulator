#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct pro{
	int at,bt,ct,tat,wt,pno;
}P[100];

struct Gantt{
	int pno, st, et;
};

vector<Gantt> GC;

float atatt[10],awtt[10];

void swap(struct pro *a, struct pro *b){
        struct pro tmp = *a;
        *a = *b;
        *b = tmp;
}

float atat = 0,awt = 0;

void fcfs(int p){
	struct Gantt tmp;
	int i;

	int t = 0;
	for(i = 0; i<p; i++){
		if(t<P[i].at)
			t = P[i].at;
		tmp.pno = P[i].pno;
		tmp.st = t;
		t += P[i].bt;
		tmp.et = t-1;
		GC.push_back(tmp);
		P[i].ct = t;
	}
	for(i = 0; i<p; i++){				//calculating tat and wt
		P[i].tat = P[i].ct-P[i].at;
		P[i].wt = P[i].tat-P[i].bt;
		atat+=P[i].tat;
		awt += P[i].wt;		
	}
	atat/=p;
	awt/=p;
	atatt[0] = atat;				//storing atat and awt
	awtt[0] = awt;
}



void printpro(int p){
	cout << "P. No.\tAT\tBT\tCT\tTAT\tWT\n";
	int i;
	for(i = 0; i<p; i++){
		cout<< P[i].pno<<"\t" <<P[i].at<<"\t" <<P[i].bt<<"\t" <<P[i].ct<<"\t" <<P[i].tat<<"\t" <<P[i].wt <<endl;	
	}
	cout << "Average Turnaround Time: "<< atat << "\n";
	cout << "Average Wait Time: "<< awt <<"\n" ;
}

void printGantt(){
	for(vector<Gantt>::iterator it=GC.begin(); it!=GC.end(); it++){
		cout << " P"<< (*it).pno<<"    "<< endl; 
		cout << (*it).st <<"   " << (*it).et << " " <<endl;
	}
}

int main(){
	
	int p,i,j;
	cout << "Enter number of processes: ";
	cin >> p;
	for(i = 0; i<p; i++){
		P[i].pno = i+1;
		cout << "For process "<<i+1<<"\nEnter Arrival Time(AT): ";
		cin >> P[i].at;
		cout << "Enter Burst Time(BT): ";
		cin >> P[i].bt;
	}
	 for(i=0;i<p;i++){
                for(j=0;j<p-i-1;j++){
                        if(P[j].at>P[j+1].at)
                        swap(&P[j],&P[j+1]);
                }
        }

	fcfs(p);
	for(i=0;i<p;i++){
                for(j=0;j<p-i-1;j++){
                        if(P[j].pno>P[j+1].pno)
                        swap(&P[j],&P[j+1]);
                }
        }
	printpro(p);
	printGantt();
	return 0;
}
