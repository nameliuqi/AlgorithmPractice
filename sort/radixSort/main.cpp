#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

int GetNumInPos(int num,int pos)
{
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= 10;

    return (num / temp) % 10;
}

/********************************************************
*函数名称：RadixSort
*参数说明：pDataArray 无序数组；
*          iDataNum为无序数据个数
*说明：    基数排序
*********************************************************/
#define RADIX_10 10    //整形排序
#define KEYNUM_31 10     //关键字个数，这里为整形位数
void RadixSort(int* pDataArray, int iDataNum)
{
    int *radixArrays[RADIX_10];    //分别为0~9的序列空间
    for (int i = 0; i < 10; i++)
    {
        radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
        radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
    }

    for (int pos = 1; pos <= KEYNUM_31; pos++)    //从个位开始到31位
    {
        for (int i = 0; i < iDataNum; i++)    //分配过程
        {
            int num = GetNumInPos(pDataArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = pDataArray[i];
        }

        for (int i = 0, j =0; i < RADIX_10; i++)    //收集
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                pDataArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0;    //复位
        }
    }
}

void LQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = arr[l];
        while (i < j)
        {
            while(i < j && arr[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                arr[i++] = arr[j];

            while(i < j && arr[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                arr[j--] = arr[i];
        }
        arr[i] = x;
        LQuickSort(arr, l, i - 1); // 递归调用
        LQuickSort(arr, i + 1, r);
    }
}

int main()
{
    int SIZE = 100000;
    clock_t timSta = 0;
    int* tmpMem = new int[SIZE];
    int n = SIZE;
    int arr[SIZE];
    // Initial array to be sorted.
    srand( (unsigned)time(0) );
    for ( int i = 0; i < SIZE; ++i )
    {
        arr[i] = i;
    }
    random_shuffle( &arr[0], &arr[SIZE - 1] );

    // Store the random array.
    memcpy( &tmpMem[0], &arr[0], SIZE * sizeof(arr[0]) );

    // STL sort.
    memcpy( &arr[0], &tmpMem[0], SIZE * sizeof(arr[0]) );
    timSta = clock();
    LQuickSort(arr,0,SIZE-1);
    cout << "STL sort time: " << clock() - timSta << endl;
    // Heap sort.
    memcpy( &arr[0], &tmpMem[0], SIZE * sizeof(arr[0]) );
    timSta = clock();
    make_heap( &arr[0], &arr[SIZE-1] );
    int mark = SIZE - 1;
    while ( mark > 0 )
    {
        pop_heap( &arr[0], &arr[mark--] );
    }
    cout << "Heap sort time: " << clock() - timSta << endl;
    // Radix sort.
    memcpy( &arr[0], &tmpMem[0], SIZE * sizeof(arr[0]) );
    timSta = clock();
    RadixSort(arr,SIZE);
    cout << "Radix sort time: " << clock()  - timSta << endl;
    delete[] tmpMem;
    return 0;
}
