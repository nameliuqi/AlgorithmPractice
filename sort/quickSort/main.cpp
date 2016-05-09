#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

int a[10000000];
int b[10000000];

void insertSort(int arr[], int l,int r)
{
    int i, j;
    for (i = l+1; i <= r; i++)
        if (arr[i] < arr[i - 1])
        {
            int temp = arr[i];
            for (j = i - 1; j >= 0 && arr[j] > temp; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = temp;
        }
}

int SelectPivot(int arr[],int low,int high)
{
    return arr[low];//ѡ��ѡȡ���еĵ�һ��Ԫ����Ϊ��׼
}

int SelectPivotRandom(int arr[],int low,int high)
{
    //���������λ��
    srand((unsigned)time(NULL));
    int pivotPos = rand()%(high - low) + low;

    //������λ�õ�Ԫ�غ�lowλ��Ԫ�ػ�������ʱ���Ժ���ͨ�Ŀ���һ�����û��ֺ���
    swap(arr[pivotPos],arr[low]);
    return arr[low];
}

int SelectPivotMedianOfThree(int arr[],int low,int high)
{
    int mid = low + ((high - low) >> 1);//���������м��Ԫ�ص��±�

    //ʹ������ȡ�з�ѡ������
    if (arr[mid] > arr[high])//Ŀ��: arr[mid] <= arr[high]
    {
        swap(arr[mid],arr[high]);
    }
    if (arr[low] > arr[high])//Ŀ��: arr[low] <= arr[high]
    {
        swap(arr[low],arr[high]);
    }
    if (arr[mid] > arr[low]) //Ŀ��: arr[low] >= arr[mid]
    {
        swap(arr[mid],arr[low]);
    }
    //��ʱ��arr[mid] <= arr[low] <= arr[high]
    return arr[low];
    //low��λ���ϱ���������λ���м��ֵ
    //�ָ�ʱ����ֱ��ʹ��lowλ�õ�Ԫ����Ϊ���ᣬ�����øı�ָ����
}

void LQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = SelectPivot(arr,l,r);
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

void RQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = SelectPivotRandom(arr,l,r);
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
        RQuickSort(arr, l, i - 1); // �ݹ����
        RQuickSort(arr, i + 1, r);
    }
}

void MQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = SelectPivotMedianOfThree(arr,l,r);
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
        MQuickSort(arr, l, i - 1); // �ݹ����
        MQuickSort(arr, i + 1, r);
    }
}

void MIQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        if (r - l + 1 < 10)
        {
            insertSort(arr,l,r);
            return;
        }
        int i = l, j = r, x = SelectPivotMedianOfThree(arr,l,r);
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
        MIQuickSort(arr, l, i - 1); // �ݹ����
        MIQuickSort(arr, i + 1, r);
    }
}

void diffBetweenQsortAndIsort()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
    int a[] = {1,2,3,-1,4,9,6,-3,-6};
    for (int i = 0; i < 10000000; i++)
    {
        insertSort(a,0,8);
    }
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n1000w��������9��Ԫ�ص�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    start=clock();
    for (int i = 0; i < 10000000; i++)
    {
        LQuickSort(a,0,8);
    }
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n�������������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
}

void QSort(int arr[],int low,int high)
{
    int first = low;
    int last = high;

    int left = low;
    int right = high;

    int leftLen = 0;
    int rightLen = 0;

    if (high - low + 1 < 10)
    {
        insertSort(arr,low,high);
        return;
    }

    //һ�ηָ�
    int key = SelectPivotMedianOfThree(arr,low,high);//ʹ������ȡ�з�ѡ������

    while(low < high)
    {
        while(high > low && arr[high] >= key)
        {
            if (arr[high] == key)//�������Ԫ��
            {
                swap(arr[right],arr[high]);
                right--;
                rightLen++;
            }
            high--;
        }
        arr[low] = arr[high];
        while(high > low && arr[low] <= key)
        {
            if (arr[low] == key)
            {
                swap(arr[left],arr[low]);
                left++;
                leftLen++;
            }
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = key;

    //һ�ο��Ž���
    //��������key��ͬ��Ԫ���Ƶ���������λ����Χ
    int i = low - 1;
    int j = first;
    while(j < left && arr[i] != key)
    {
        swap(arr[i],arr[j]);
        i--;
        j++;
    }
    i = low + 1;
    j = last;
    while(j > right && arr[i] != key)
    {
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    QSort(arr,first,low - 1 - leftLen);
    QSort(arr,low + 1 + rightLen,last);
}



int randomArray(int a[],int num)
{
    srand((int)time(0));
    int maxNum = 100000000;
    cout<<"in random"<<endl;
    for (int i = 0;i < num ;i++)
    {
        a[i] = rand()%maxNum;
    }
    return num;
}

int increasingArray(int a[],int num)
{
    for (int i = 0;i < num;i++)
    {
        a[i] = i;
    }
    return num;
}

int decreasingArray(int a[],int num)
{
    for (int i = 0;i < num;i++)
    {
        a[i] = 1000000 - i;
    }
    return num;
}

int cp(int a[],int b[],int n)
{
    for (int i = 0;i < n;i++)
    {
        b[i] = a[i];
    }
    return n;
}

int main()
{
    clock_t start,finish;
    double totaltime;
    int n = 1000000;
    randomArray(a,n);
    cp(a,b,n);
    start=clock();
    LQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ��+100w�����������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ���+100w������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+100w������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+100w������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+�ۼ���ͬ��+100w������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    n = 30000;
    increasingArray(a,n);
    cp(a,b,n);
    start=clock();
    LQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ��+3w������������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ���+3w�������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+3w�������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+3w�������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+�ۼ���ͬ��+3w�������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    n = 30000;
    decreasingArray(a,n);
    cp(a,b,n);
    start=clock();
    LQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ��+3w�ݼ���������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\nȡ���+3w�ݼ����ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+3w�ݼ����ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+3w�ݼ����ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n����ȡ��+��������+�ۼ���ͬ��+3w�ݼ����ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
//    start=clock();
//    randomArray(a,n);
//    increasingArray(a,n);
//    quickSort(a,0,n-1);
//    finish=clock();
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    cout<<"\nȡ��+100w������ݵ�����ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    return 0;
}
/**
ȡ��+100w�����������ʱ��Ϊ0.319�룡

ȡ���+100w������ݵ�����ʱ��Ϊ0.385�룡

����ȡ��+100w������ݵ�����ʱ��Ϊ0.294�룡

����ȡ��+��������+100w������ݵ�����ʱ��Ϊ0.24�룡

����ȡ��+��������+�ۼ���ͬ��+100w������ݵ�����ʱ��Ϊ0.188�룡
*/
