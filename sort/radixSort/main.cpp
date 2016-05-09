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
*�������ƣ�RadixSort
*����˵����pDataArray �������飻
*          iDataNumΪ�������ݸ���
*˵����    ��������
*********************************************************/
#define RADIX_10 10    //��������
#define KEYNUM_31 10     //�ؼ��ָ���������Ϊ����λ��
void RadixSort(int* pDataArray, int iDataNum)
{
    int *radixArrays[RADIX_10];    //�ֱ�Ϊ0~9�����пռ�
    for (int i = 0; i < 10; i++)
    {
        radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
        radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
    }

    for (int pos = 1; pos <= KEYNUM_31; pos++)    //�Ӹ�λ��ʼ��31λ
    {
        for (int i = 0; i < iDataNum; i++)    //�������
        {
            int num = GetNumInPos(pDataArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = pDataArray[i];
        }

        for (int i = 0, j =0; i < RADIX_10; i++)    //�ռ�
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                pDataArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0;    //��λ
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
            while(i < j && arr[j] >= x) // ���������ҵ�һ��С��x����
                j--;
            if(i < j)
                arr[i++] = arr[j];

            while(i < j && arr[i] < x) // ���������ҵ�һ�����ڵ���x����
                i++;
            if(i < j)
                arr[j--] = arr[i];
        }
        arr[i] = x;
        LQuickSort(arr, l, i - 1); // �ݹ����
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
