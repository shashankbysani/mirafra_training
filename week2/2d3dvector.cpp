#include<iostream>
#include<stdexcept>
#include<vector>

using namespace std;
int main()
{
    int row=3;
    int col=4;
    vector<vector<int>>vec(row,vector<int>(col));
     for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            vec[i][j]=i*col+j;
            cout<<vec[i][j]<<" ";
        }
        cout<<" "<<endl;
    }
    cout<<"using iterator\n";
    for(auto rowIt=vec.begin();rowIt!=vec.end();rowIt++)
    {
        for(auto colIt=rowIt->begin();colIt !=rowIt->end();colIt++)
        {
            
            cout<<*colIt<<" ";
        }
        cout<<" "<<endl;
    }
    cout<<"using range based iterator"<<endl;
    for(const auto& rowIt:vec)
    {
        for(const auto& elem:rowIt)
        {
            cout<<elem<<" ";
        }
        cout<<" "<<endl;
    }
}
/*
int main()
{
    int depth=2;
    int row=3;
    int col=4;
        vector<vector<vector<int>>>vec(depth,vector<vector<int>>(row,vector<int>(col)));
    for(int i=0;i<depth;i++)
    {
        for(int j=0;j<row;j++)
        {
            for(int k=0;k<col;k++)
            {
                 vec[i][j][k]=i*row*col+j*col+k;
                cout<<vec[i][j][k]<<" ";
            }
            cout<<" "<<endl;
        }
    }
}
/*
int main()
{
    int row=3;
    int col=4;
    vector<vector<int>>vec(row,vector<int>(col));
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            vec[i][j]=i*col+j;
            cout<<vec[i][j]<<" ";
        }
        cout<<" "<<endl;
    }
}
/*int main()
{
    int depth=2;
    int row=3;
    int col=4;
    
    int ***arr=new int **[depth];
    for(int i=0;i<depth;i++)
    {
        arr[i]=new int *[row];
        for(int j=0;j<row;j++)
        {
            arr[i][j]=new int[col];
        }
    }
    
    for(int i=0;i<depth;i++)
    {
        for(int j=0;j<row;j++)
        {
            for(int k=0;k<col;k++)
            {
                arr[i][j][k]=i*row*col+j*col+k;
                cout<<arr[i][j][k]<<" ";
            }
            cout<<" "<<endl;
        }
    }
    for(int i=0;i<depth;i++)
    {
        for(int j=0;j<row;j++)
        {
            delete[]arr[i][j];
        }
        delete[]arr[i];
    }
    delete[]arr;
    return 0;
    
}
/*int main()
{
    int row =3;
    int col =4;
    int **arr=new int*[row];
    for(int i=0;i<row;i++)
    {
        arr[i]=new int [col];
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            arr[i][j]=i*col+j;
            cout<<arr[i][j]<<" ";
        }
        cout<<" "<<endl;
    }
    for(int i=0;i<row;i++)
    {
        delete[]arr[i];
    }
    delete[]arr;
    return 0;
}*/
/*int main()
{
    int arr[3][4]={{1,2,3,4},{5,30,40,60},{11,23,35,46}};
    for(int row=0;row<3;row++)
    {
        for(int col=0;col<4;col++)
        {
            cout<<arr[row][col]<<" ";
        }
        cout<<" "<<endl;
    }
}*/