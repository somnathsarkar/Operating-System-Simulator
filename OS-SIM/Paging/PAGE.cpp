#include <bits/stdc++.h>
using namespace std;

int display(int arr[], int size, int cnt, int outputmat[][100], int index)
{
    if (size >= cnt + 1)
        size = cnt;
    for(int i=0;i<size;i++)
        {
            cout<<arr[i]<<" ";
            outputmat[index][i]=arr[i];
        }

    index ++;
    cout<<endl<<endl;
    return index;
}

int check(int arr[], int page, int size)
{
    for (int i=0;i<size;i++)
        if (arr[i] == page)
            return 1;
    return 0;
}

int lastuse(int arr[], int frame, int k)
{
    for (int i=k;i>=0;i--)
        if (arr[i] == frame)
            return i;
    return -1;
}

int nextuse(int arr[], int frame, int size, int k)
{
    for (int i=k;i<size;i++)
        if (arr[i] == frame)
            return i;
    return 1000;
}

int min(int arr[], int size)
{
    int i, min = 0;
    for (i=1;i<size;i++)
        if (arr[i] < arr[min])
            min = i;
    return min;
}

int max(int arr[], int size)
{
    int i, min = 0;
    for (i=1;i<size;i++)
        if (arr[i] > arr[min])
            min = i;
    return min;
}

void fifo(int arr[], int page, int size)
{
    static int track = 1;
    arr[track] = page;
    track = (track + 1) % size;
}

void optimal(int arr[], int pages[], int curr, int size, int num_of_frames, int num_of_pages)
{
    int index[num_of_frames], i;
    if (size < num_of_frames)
        arr[size] = pages[curr];
    else
    {
        for (i=0;i<size;i++)
            index[i] = nextuse(pages, arr[i], num_of_pages, curr + 1);
        i = max(index, size);
        arr[i] = pages[curr];
    }
}

void lru(int arr[], int pages[], int curr, int size, int num_of_frames)
{
    int index[num_of_frames], i;
    if (size < num_of_frames)
        arr[size] = pages[curr];
    else
    {
        for (i=0;i<size;i++)
            index[i] = lastuse(pages, arr[i], curr - 1);
        i = min(index, size);
        arr[i] = pages[curr];
    }
}

int pagemain()
{
    num_of_faults = 0, index=0, num_of_hits = 0;
    /*cout<<"Enter number of pages: ";
    cin>>num_of_pages;
    cout<<"Enter page sequence: ";
    for (i=0;i<num_of_pages;i++)
        cin>>pages[i];
    cout<<"Enter number of frames: ";
    cin>>num_of_frames;
    cout<<"The page replacement algorithms are:\n1. FIFO\n2. Optimal\n3. LRU\nEnter choice:";
    cin>>choice;*/

    cout<<"Fault -> ";
    num_of_faults++;
    frames[0] = pages[0];
    index = display(frames, num_of_frames, num_of_faults, outputmat, index);
    i=1;

    while (i < num_of_pages)
    {
        if (num_of_faults < num_of_frames)
            size = num_of_faults;
        else
            size = num_of_frames;
        if (!check(frames, pages[i], size))
        {
            cout<<"Fault -> ";
            if(choice==1)
                fifo(frames, pages[i], num_of_frames);
            else if(choice==2)
                optimal(frames, pages, i, size, num_of_frames, num_of_pages);
            else if(choice==3)
                lru(frames, pages, i, size, num_of_frames);
            num_of_faults++;
        }
        else
        {
            cout<<"Hit -> ";
            num_of_hits++;
        }
        index = display(frames, num_of_frames, num_of_faults, outputmat, index);
        i++;
    }

    //FINAL OUTPUT TO BE USED FOR GUI
    //state after each page request is stored in outputmat
    for(i=0; i<index; i++)
    {
        for(int j=0;j<num_of_frames; j++)
            cout<<outputmat[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}