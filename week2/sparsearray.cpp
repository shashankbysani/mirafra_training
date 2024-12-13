#include<iostream>
#include<vector>
using namespace std;
class csMatrix
{
    vector<double>values;
    vector<int>rowIdx ;
    vector<int>colIdx ;
    
    int numRows;
    int numCols;
    
    public:
    csMatrix(int row,int col):numRows(row),numCols(col)
    {
        //rowIdx.resize(row+1,0);
        rowIdx.reserve(row);
    }
    void addValue(int row,int col,double value)
    {
        if(value!=0)
        {
            values.push_back(value);
            colIdx.push_back(col);
            rowIdx.push_back(row);
            
        }
    }
    double getValues( int row,int col)const
    {
        int rowSt=rowIdx[row];
        int rowEd=rowIdx[row+1];
        
        for(int i=rowSt;i<rowEd;i++)
        {
            if(colIdx[i]==col)
            {
                return values[i];
                
            }
        }
        return 0.0;
    }
    void displayMatrix()const{
        cout<<endl<<"Values";
        for(double val:values)
        {
            cout<<val<<" ";
            
        }
        cout<<endl<<"column index: ";
        for(int col: colIdx)
        {
            cout<<col<<" ";
        }
        cout<<endl<<"Rows index ";
        for(int row:rowIdx)
        {
            cout<<row <<" ";
        }
    }
};
int main()
{
  csMatrix csr(4,4);
  csr.addValue(0,2,3);
  csr.addValue(1,0,4);
  csr.addValue(1,3,5);
  csr.addValue(2,3,6);
  csr.addValue(3,0,7);
  csr.addValue(3,2,8);
  
  csr.displayMatrix();
}