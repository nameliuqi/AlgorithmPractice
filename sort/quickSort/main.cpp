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
    return arr[low];//选择选取序列的第一个元素作为基准
}

int SelectPivotRandom(int arr[],int low,int high)
{
    //产生枢轴的位置
    srand((unsigned)time(NULL));
    int pivotPos = rand()%(high - low) + low;

    //把枢轴位置的元素和low位置元素互换，此时可以和普通的快排一样调用划分函数
    swap(arr[pivotPos],arr[low]);
    return arr[low];
}

int SelectPivotMedianOfThree(int arr[],int low,int high)
{
    int mid = low + ((high - low) >> 1);//计算数组中间的元素的下标

    //使用三数取中法选择枢轴
    if (arr[mid] > arr[high])//目标: arr[mid] <= arr[high]
    {
        swap(arr[mid],arr[high]);
    }
    if (arr[low] > arr[high])//目标: arr[low] <= arr[high]
    {
        swap(arr[low],arr[high]);
    }
    if (arr[mid] > arr[low]) //目标: arr[low] >= arr[mid]
    {
        swap(arr[mid],arr[low]);
    }
    //此时，arr[mid] <= arr[low] <= arr[high]
    return arr[low];
    //low的位置上保存这三个位置中间的值
    //分割时可以直接使用low位置的元素作为枢轴，而不用改变分割函数了
}

void LQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = SelectPivot(arr,l,r);
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

void RQuickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = SelectPivotRandom(arr,l,r);
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
        RQuickSort(arr, l, i - 1); // 递归调用
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
        MQuickSort(arr, l, i - 1); // 递归调用
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
        MIQuickSort(arr, l, i - 1); // 递归调用
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
    cout<<"\n1000w插入排序9个元素的运行时间为"<<totaltime<<"秒！"<<endl;
    start=clock();
    for (int i = 0; i < 10000000; i++)
    {
        LQuickSort(a,0,8);
    }
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n快速排序的运行时间为"<<totaltime<<"秒！"<<endl;
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

    //一次分割
    int key = SelectPivotMedianOfThree(arr,low,high);//使用三数取中法选择枢轴

    while(low < high)
    {
        while(high > low && arr[high] >= key)
        {
            if (arr[high] == key)//处理相等元素
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

    //一次快排结束
    //把与枢轴key相同的元素移到枢轴最终位置周围
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
    cout<<"\n取左+100w随机数据运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n取随机+100w随机数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+100w随机数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+100w随机数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+聚集相同数+100w随机数据的运行时间为"<<totaltime<<"秒！"<<endl;
    n = 30000;
    increasingArray(a,n);
    cp(a,b,n);
    start=clock();
    LQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n取左+3w递增数据运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n取随机+3w递增数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+3w递增数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+3w递增数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+聚集相同数+3w递增数据的运行时间为"<<totaltime<<"秒！"<<endl;
    n = 30000;
    decreasingArray(a,n);
    cp(a,b,n);
    start=clock();
    LQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n取左+3w递减数据运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    RQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n取随机+3w递减数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+3w递减数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    MIQuickSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+3w递减数据的运行时间为"<<totaltime<<"秒！"<<endl;
    cp(a,b,n);
    start=clock();
    QSort(b,0,n-1);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n三数取中+插入排序+聚集相同数+3w递减数据的运行时间为"<<totaltime<<"秒！"<<endl;
//    start=clock();
//    randomArray(a,n);
//    increasingArray(a,n);
//    quickSort(a,0,n-1);
//    finish=clock();
//    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
//    cout<<"\n取左+100w随机数据的运行时间为"<<totaltime<<"秒！"<<endl;
    return 0;
}
/**
取左+100w随机数据运行时间为0.319秒！

取随机+100w随机数据的运行时间为0.385秒！

三数取中+100w随机数据的运行时间为0.294秒！

三数取中+插入排序+100w随机数据的运行时间为0.24秒！

三数取中+插入排序+聚集相同数+100w随机数据的运行时间为0.188秒！
*/
