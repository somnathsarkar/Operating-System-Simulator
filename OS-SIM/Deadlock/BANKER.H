#include<iostream.h>
#include <stdio.h>
#include<stdlib.h>
	int ballocate[20][20],bmax[20][20],bneed[20][20],bavail[20][20],binstance[20],bav[100],bwork[20],btime[20],bfinish[20];
	int bk,bt,bct,bpos[20],brq[20],br,bpro,bp,bi,bj,bdisp[20][20],bq=0,bpcount=0;

	void read()
	{	cout<<"\nEnter Number of Resources : ";
		cin>>br;
		for(bi=0;bi<br;bi++)
		{       cout<<"\nEnter Max. Instance of Resource-"<<(char)(bi+65)<<" : ";
			cin>>binstance[bi];
		}
		cout<<"\nEnter Number of Process : ";
		cin>>bp;
		cout<<"\nEnter Allocation Matrix :\n   ";
		for(bi=0;bi<br;bi++)
		{       cout<<" "<<(char)(bi+65);
		}
		cout<<"\n";
		for(bi=0;bi<bp;bi++)
		{       cout<<"\n "<<bi+1<<". ";
			for(bj=0;bj<br;bj++)
			{	cin>>ballocate[bi][bj];
				bavail[0][bj]=ballocate[bi][bj]+bavail[0][bj];
			}
			bpos[bi]=bi+1;
		}
		cout<<"\nEnter Max Matrix :\n   ";
		for(bi=0;bi<br;bi++)
		{       cout<<" "<<(char)(bi+65);
		}
		cout<<"\n";
		for(bi=0;bi<bp;bi++)
		{       cout<<"\n "<<bi+1<<". ";
			for(bj=0;bj<br;bj++)
			{	cin>>bmax[bi][bj];
			}
		}
		for(bi=0;bi<bp;bi++)
		{	bfinish[bi] = -1;
		}
		for(bi=0;bi<br;bi++)
		{       bavail[0][bi]=binstance[bi]-bavail[0][bi];
			bav[bi]=bavail[0][bi];
			bwork[bi]=bavail[0][bi];
		}
		for(bi=0;bi<bp;bi++)
		{       for(bj=0;bj<br;bj++)
			{       bneed[bi][bj]=bmax[bi][bj]-ballocate[bi][bj];
			}
		}
	}
	void check_safe()
	{
		cout<<"\nAvailable  : \n";
		for(bi=0;bi<br;bi++)
		{      cout<<bavail[0][bi]<<" ";
		}
		for(bi=0;bi<bp;bi++)
		{      	bfinish[bi]=-1;
		}
		for(bk=0;bk<bp;bk++)
		{	for(bi=0;bi<bp;bi++)
			{	bct = 0;
				if(bfinish[bi] == -1)
				{	for(bj=0;bj<br;bj++)
					{	if(bneed[bi][bj] <= bwork[bj])
						bct++;
						else
						break;
					}
					if(bct==br)
					{	for(bj=0;bj<br;bj++)
						{	bwork[bj] = bwork[bj] + ballocate[bi][bj];
							bavail[bi][bj] = bwork[bj];
						}
						bfinish[bi] = 0;
						bpcount++;
						btime[bi] = bt++;
						cout<<"\n";
						for(int bw=0;bw<br;bw++)
						{   cout<<bwork[bw]<<" ";
						}

					}
				}
			}
		}
		for(bi=0;bi<bp;bi++)
		{	if(bfinish[bi] == -1)
			{	cout<<"\n\n\tSystem is in UNSAFE state\n\n";
				exit(0) ;
			}
		}
		cout<<"\n\n\tSystem is in SAFE state\n\n";
	}
	void display()
	{	int btemp;
		for(bi=0;bi<bp-1;bi++)
		{	for(bj=0;bj<bp-bi-1;bj++)
			{	if(btime[bj]>btime[bj+1])
				{	btemp = btime[bj];
					btime[bj] = btime[bj+1];
					btime[bj+1] = btemp;

					btemp = bpos[bj];
					bpos[bj] = bpos[bj+1];
					bpos[bj+1] = btemp;
				}
			}
		}
		cout<<"\n-------------------------------------";
		cout<<"\nNeed Matrix\n   ";
		for(bi=0;bi<br;bi++)
		{       cout<<" "<<(char)(bi+65);
		}
		for(bi=0;bi<bp;bi++)
		{       cout<<"\n "<<bi+1<<". ";
			for(bj=0;bj<br;bj++)
			cout<<bneed[bi][bj]<<" ";
		}
		cout<<"\n-------------------------------------";
		cout<<"\nAvailable Matrix\n   ";
		for(bi=0;bi<br;bi++)
		{       cout<<" "<<(char)(bi+65);
		}
		for(bi=0;bi<bp;bi++)
		{       cout<<"\n "<<bi+1<<". ";
			for(bj=0;bj<br;bj++)
			{       cout<<bavail[bi][bj]<<" ";
			}
		}
		cout<<"\n-------------------------------------";
		cout<<"\nExecution Sequence : <";
		for(bi=0;bi<bp;bi++)
		{	cout<<"P"<<bpos[bi]<<" ";
		}
		cout<<">\n";
		cout<<"\n-------------------------------------\n";

	}
	void check_request_allocate()
	{	cout<<"\nEnter Process for which request arrives : ";
		cin>>bpro;
		cout<<"\nEnter Request P->"<<bpro<<" : ";
		for(bi=0;bi<br;bi++)
		{	cin>>brq[bi];
		}
		for(bj=0;bj<br;bj++)
		{	if(brq[bj]>bneed[bpro-1][bj])
			{	cout<<"Request NOT Granted!\n";
				exit(0);
			}
		}
		for(bj=0;bj<br;bj++)
		{	if(brq[bj]>bavail[bpro-1][bj])
			{	cout<<"\n\tRequest NOT Granted!\n";
				exit(0);
			}
			else
			{
				bav[bj] = bav[bj] - brq[bj];
				ballocate[bpro-1][bj] = ballocate[bpro-1][bj] + brq[bj];
				bneed[bpro-1][bj] = bneed[bpro-1][bj] - brq[bj];
			}
		}
		for(bi=0;bi<br;bi++)
		{	bwork[bi]=bav[bi];
		}
		cout<<"\n";

	}