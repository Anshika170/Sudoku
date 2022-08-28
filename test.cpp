# include<iostream>
# include<vector>
using namespace std;

void printSudoku(int arr[9][9])
{
    cout<<"---------------------"<<endl;
    for(int r=0;r<9;r++)
    {
        for(int c=0;c<9;c++)
          cout<<arr[r][c]<<" ";
        cout<<endl;
        
    }
    cout<<"---------------------"<<endl;
}

bool canPlace(int arr[9][9], int row, int col,int n)
{
  if(arr[row][col]!=0) 
    return false;
  bool status=true;
  int gridx =(col/3)*3;
  int gridy =(row/3)*3;
  for(int i=0;i<9;i++)
  {
    if(arr[row][i]==n)
    {
        status=false;
    }
    if(arr[i][col]==n)
    {
        status=false;
    }
    if(arr[gridy+i/3][gridx+i % 3]==n)
    {
        status=false;
    }
  }
  return status;
}

vector<int> findplacebles(int arr[9][9],int r,int c)
{
    vector<int> cps ={};
    for(int i=1;i<=9;i++)
    {
        if(canPlace(arr,r,c,i))
           cps.push_back(i);
    }
    return cps;
}

void copyArray(int arr[9][9], int arrcopy[9][9])
{
    for(int y=0;y<9;y++)
    {
        for(int x=0;x<9;x++)
          arrcopy[y][x]= arr[y][x];
    }
}

void nextempty(int arr[9][9],int row,int col,int &nRow, int &nCol)
{
    int index =9*9;
    for(int i=row*9 + col+1; i,9*9;i++)
    {
        if(arr[i/9][i%9]==0)
        {
            index =i;
            break;
        }
    }
    nRow= index/9;
    nCol= index%9;
}

bool solveSudoku(int arr[9][9],int row,int col)
{
    if(row > 8)return true;
    if(arr[row][col] !=0)
    {
      int nextCol,nextRow;
      nextempty(arr,row,col,nextRow, nextCol);
      return solveSudoku(arr, nextRow,nextCol);

    }
    vector<int> placables= findplacebles(arr,row,col);

    if(placables.size()==0)return false;

    bool status = false;
    for(int i=0;i< placables.size();i++)
    {
      int n = placables[i];
      int arrcopy[9][9];
      copyArray(arr,arrcopy);
      arrcopy[row][col]=n;
      int nextCol,nextRow;
      nextempty(arrcopy,row,col,nextRow, nextCol);
      if(solveSudoku(arrcopy, nextRow,nextCol))
      {
        copyArray(arrcopy,arr);
        status=true;
        break;
      }
    }
    return status;

}


int main()
{
    int board[9][9]={
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9},
    };
    printSudoku(board);
    solveSudoku(board,0,0);
    
    printSudoku(board);
    return 0;
}
