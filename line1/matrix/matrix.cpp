#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include "algorithm"
#define MAXSIZE 12500            //假设非零元个数的最大值为12500

using namespace std;

typedef struct
{

    int  i,j;               //非零元的行下标和列下标

    int  e;                 //非零元

} Triple;

typedef struct
{

    Triple    data[MAXSIZE+1];  //用于存储非零元三元组表, data[0]未用

    int          mu,nu,tu;                 //矩阵的行数、列数和非零元个数

} TSMatrix;

int TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    if (T.tu)
    {
    	int q,col,p;
        q=0;               // q为当前三元组在T.data[ ]存储位置(下标)
        for (col=0; col<M.mu;  ++col)
            for (p=0;  p<M.tu;  ++p)      //p为扫描M.data[ ]的“指示器”
                //p“指向”三元组称为当前三元组
                if (M.data[p].j == col)
                {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    ++q;
                }
    }
    return 1;
}//  TransposeSMtrix

bool cmp(Triple t1,Triple t2)
{
    return (t1.j<t2.j)||(t1.j==t2.j && t1.i<t2.i);
}

int FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    //采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T。
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    if (T.tu)
    {
    	int p;
    	for (p=0; p<M.tu; ++p)
    	{
    			T.data[p].i = M.data[p].j;
    			T.data[p].j = M.data[p].i;
    			T.data[p].e = M.data[p].e;
        }
    	sort(T.data,T.data+T.tu,cmp);
    }//if
    return 1;
}//FastTransposeSMatrix

int main()
{
    int n,col,vol;
    cout<<"input col,vol,n\n";
    cin>>col>>vol>>n;
    cout<<"input i,j,e\n";
    TSMatrix T,M;
    M.tu = n;
    M.nu = col;
    M.mu = vol;
    for (int i=0;i<n;i++)
    {
        cin>>M.data[i].i>>M.data[i].j>>M.data[i].e;
    }
    int status;
    status = TransposeSMatrix(M,T);
    cout<<"trans:\n";
    if (status)
        for (int i=0;i<n;i++)
        {
            cout<<T.data[i].i<<" "<<T.data[i].j<<" "<<T.data[i].e<<endl;
        }
    status = FastTransposeSMatrix(M,T);
    cout<<"fastTrans\n";
    if (status)
        for (int i=0;i<n;i++)
        {
            cout<<T.data[i].i<<" "<<T.data[i].j<<" "<<T.data[i].e<<endl;
        }
    return 0;
}


//0 0 0 0 0
//-1 1 0 0 0
//0 0 0 0 3
//0 0 0 2 0
//
//0 -1 0 0
//0 1 0 0
//0 0 0 0
//0 0 0 2
//0 0 3 0
//
/**
4 5 4
1 0 -1
1 1 1
2 4 3
3 3 2
*/
