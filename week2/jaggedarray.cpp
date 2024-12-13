#include <iostream>
using namespace std;
int main()
{
    int rows =3;
    int *jaggedarr[rows];
    
    jaggedarr[0]=new int [2];
    jaggedarr[1]=new int[5];
    jaggedarr[2]=new int[3];
    
    for(int i=0;i<rows;i++)
    {
        for(int j=0 ;j<(i==0?2:(i==1?5:3));j++)
        {
            jaggedarr[i][j]=i+j;
        }
    }
        for(int i=0;i<rows;i++)
    {
        for(int j=0 ;j<(i==0?2:(i==1?5:3));j++)
        {
            cout<<jaggedarr[i][j]<<" ";
        }
        cout<<"\n";
    }
    for(int i=0;i<rows;i++)
    {
        delete[] jaggedarr[i];
    }
}