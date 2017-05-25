#include <iostream>
#include<cstdlib>
#include<vector>

using namespace std;

struct pro{
	int at,bt,ct,tat,wt,id,pno;
}P[100],Pq[100];

int qs = 0,qc = 0;

struct Gantt{
	int pno, st, et;
};

vector<Gantt> GC;

float atat,awt;

void swapp(struct pro *a, struct pro *b){
        struct pro tmp = *a;
        *a = *b;
        *b = tmp;
}

void push(struct pro a){
	Pq[qs+qc] = a;
	qc++;
}

struct pro pop(){
	qc--;
	return Pq[qs++];
}

void robin(int p,int tq){
	struct Gantt tmp;
	int t=0;
	int i = 0;
	while(i<p||qc){
		while(i<p&&P[i].at<=t){
			push(P[i]);
			i++;
		}
		if(!qc)
			t = P[i].at;
		else{
			struct pro exec_pro = pop();
			tmp.pno = exec_pro.pno;
			tmp.st  = t;			
			int texec = (tq<exec_pro.bt)?tq:exec_pro.bt;
			exec_pro.bt-=texec;
			t+=texec;
			tmp.et = t-1;
			GC.push_back(tmp);
			while(i<p&&P[i].at<=t){
				push(P[i]);
				i++;
			}
			if(exec_pro.bt)
				push(exec_pro);
			else
				P[exec_pro.id].ct =	t;
		}
	}
}

void calct(int p){
	int i = 0;
	for(i = 0; i<p; i++){
		P[i].tat = P[i].ct-P[i].at;
		P[i].wt = P[i].tat-P[i].bt;		
	}
}

void printpro(int p){
	cout << "P. No.\tAT\tBT\tCT\tTAT\tWT\n";
	int i;
	for(i = 0; i<p; i++){
		cout<< P[i].pno<<"\t" <<P[i].at<<"\t" <<P[i].bt<<"\t" <<P[i].ct<<"\t" <<P[i].tat<<"\t" <<P[i].wt <<endl;	
		P[i].tat = P[i].ct-P[i].at;
		P[i].wt = P[i].tat-P[i].bt;
		atat+=P[i].tat;
		awt += P[i].wt;		
	}
	atat/=p;
	awt/=p;
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
	int p, i, j;
	cout << "Enter number of processes: ";
	cin >> p;
	for(i = 0; i<p; i++){
		P[i].pno = i+1;
		cout << "For process " << i+1 << ":\nEnter Arrival Time(AT): ";
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
	int tq;
	cout << "Enter the time Quanta: ";
	cin >> tq ;
	robin(p,tq);
	for(i=0;i<p;i++){
                for(j=0;j<p-i-1;j++){
                        if(P[j].pno>P[j+1].pno)
                        swapp(&P[j],&P[j+1]);
                }
        }
	calct(p);
	printpro(p);
	printGantt();
	return 0;
}

//6 0 4 1 5 2 2 3 1 4 6 6 3
