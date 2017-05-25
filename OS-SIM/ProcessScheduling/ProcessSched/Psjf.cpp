#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

struct pro{
	int at,bt,ct,tat,wt,pno,id;
}P[100],Pq[100];

int qs = 0,qc = 0;;

struct Gantt{
	int pno, st, et;
};

vector<Gantt> GC;

void swapp(struct pro *a, struct pro *b){
        struct pro tmp = *a;
        *a = *b;
        *b = tmp;
}


void push(struct pro a){
	Pq[qs+qc] = a;
	int i = qs+qc-1;
	qc++;
	while(i>=qs&&Pq[i+1].bt<Pq[i].bt){
		swapp(&Pq[i],&Pq[i+1]);
		i--;
	}
}

struct pro pop(){
	qc--;
	return Pq[qs++];
}


float atat = 0,awt = 0;

void srtf(int n) {
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
			if (t + exec_pro.bt <= time_next) {
				tmp.st = t;
				t += exec_pro.bt;
				tmp.et = t-1;
				P[exec_pro.id].ct = t;
			}
			else {
				exec_pro.bt -= (time_next - t);
				tmp.st = t;
				t = time_next;
				tmp.et = t-1;
				push(exec_pro);
			}
			GC.push_back(tmp);
		}
	}
	for(i = 0; i<n; i++){				//calculating tat and wt
		P[i].tat = P[i].ct-P[i].at;
		P[i].wt = P[i].tat-P[i].bt;
		atat+=P[i].tat;
		awt += P[i].wt;		
	}
	atat/=n;
	awt/=n;
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
                        swapp(&P[j],&P[j+1]);
                }
        }
	
	for(i = 0; i<p; i++)
		P[i].id = i;
	srtf(p);
	for(i=0;i<p;i++){
                for(j=0;j<p-i-1;j++){
                        if(P[j].pno>P[j+1].pno)
                        swapp(&P[j],&P[j+1]);
                }
        }
	printpro(p);
	printGantt();
	return 0;
}
