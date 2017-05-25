#include <iostream>
#include <stdlib.h>
using namespace std;

int x = 0, par, used[100], free_mem, ifrag = 0, pifrag[100], efrag = 0, pos[100], p[100],  pr[100], ap[100], q[100], front = 0, rear = 0;
void mem_alloc(), mem_dealloc(), display();

int main()
{
  int i, ch;
  cout<<"\nEnter No: of Partitions : ";
  cin>>par;

  for(i=0;i<100;i++)
  q[i] = -1;

  cout<<"\nEnter Size of Each Partition"<<endl;
  for(i=0;i<par;i++)
  {
    cout<<"Partition "<<i+1<<" : ";
    cin>>p[i];
    free_mem = free_mem + p[i];
    //cout<<free_mem;
    ap[i] = p[i];
    pifrag[i] = 0;
    used[i] = -1;
  }

  cout<<"\nMENU\n1. ALLOCATE  2. DEALLOCATE  3. DISPLAY  4. EXIT\n";

  for(;;)
  {
    cout<<"\nEnter Your Choice : ";
    cin>>ch;

    switch(ch)
    {
      case 1:mem_alloc();
             x++;
             break;

      case 2:mem_dealloc();
             break;

      case 3:display();
             break;

      default:exit(0);
    }
  }
}

void mem_alloc()
{
  cout<<endl;
  int j, ct, uct, flag = 0;
  if(q[front] != -1)
  {
    pr[x] = q[front++];
  }
  else
  {
    cout<<"Enter Memory Reqd. for Process "<<x+1<<" : ";
    cin>>pr[x];
  }

  ct = 0, uct = 0;
  for(j=0;j<par;j++)
  {
      if(pr[x]>p[j])
      ct++;
      else
      {
        if(used[j] == -1)
        {
          cout<<"Process "<<x+1<<" allocated to Partition "<<j+1<<"\n";
          pos[x] = j+1;

          pifrag[x] = p[j] - pr[x];
          free_mem = free_mem - pifrag[x];
          cout<<"Internal Fragmentation for Process "<<x+1<<" is "<<pifrag[x]<<"\n";
          used[j] = 0;
          break;
        }
        else
        uct++;
      }
  }

  //cout<<free_mem;
  if(ct == par || uct == par)
  {
    cout<<"Process can't be allocated"<<endl;

    if(pr[x]<=free_mem)
    efrag = efrag+free_mem;
    for(int i=0;i<par;i++)
    {
      if(pr[x]<ap[i])
      {
        cout<<"Process "<<x+1<<" put in Queue"<<endl;
        q[rear++] = pr[x];
        flag = 1;
        break;
      }
    }
    if(flag==0)
    x--;
  }
}

void mem_dealloc()
{
  cout<<endl;
  int pno;
  cout<<"Enter Process to Deallocate : ";
  cin>>pno;

  for(int j=0;j<par;j++)
  {
    if(pos[pno-1] == j+1)
    {
      pos[pno-1] = -1;
      free_mem = free_mem + pifrag[pno-1];
      p[pno-1] = ap[pno-1];
      pifrag[pno-1] = 0;
      used[j] = -1;
    }
  }
}

void display()
{
  cout<<"\n";
  int flag;
  for(int j=0;j<par;j++)
  {
    flag=0;
    cout<<"Partition "<<j+1<<" : ";
    for(int k = 0;k<x;k++)
    {
      if(pos[k] == j+1)
      {
        cout<<"Process "<<k+1<<endl;
        flag=1;
        break;
      }
    }
    if(flag==0)
    cout<<"\n";
  }

  cout<<"\nExternal Fragmentation = "<<efrag<<endl;
  cout<<"Internal Fragmentation = ";
  ifrag = 0;
  for(int j=0;j<x;j++)
  {
    ifrag = ifrag + pifrag[j];
  }
  cout<<ifrag<<endl;
}
