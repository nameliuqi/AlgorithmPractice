#include <iostream>
#include <vector>
using namespace std;

//小根堆
class Heap
{
public:
	Heap(int iSize);
	~Heap();

	int Enqueue(int iVal);
	int Dequeue(int &iVal);
	int GetMin(int &iVal);
	void printQueue();
protected:
    //存储数据
	int *m_pData;
	int m_iSize;
	int m_iAmount;
};
Heap::Heap(int iSize = 100)//注意这里是从0开始，所以如果根是i，那么左孩子是2*i+1，右孩子是2*i+2
{
	m_pData = new int[iSize];
	m_iSize = iSize;
	m_iAmount = 0;
}
Heap::~Heap()
{
	delete []m_pData;
}

int Heap::Enqueue(int iVal)//进入堆
{
    //满
	if (m_iAmount == m_iSize)
	{
		return 0;
	}
	m_pData[m_iAmount ++] = iVal;
	int iIndex = m_iAmount - 1;
	while (m_pData[iIndex] < m_pData[(iIndex - 1) /2])//上浮，直到满足最小堆
	{
		swap(m_pData[iIndex],m_pData[(iIndex - 1) /2]);
		iIndex = (iIndex - 1) /2;
	}
	return 1;
}

int Heap::Dequeue(int &iVal)//出堆
{
	if (m_iAmount == 0)
	{
		return 0;
	}
	iVal = m_pData[0];//出堆的数据
	m_pData[0] = m_pData[m_iAmount - 1];//最后一个数据放到第一个根上面
	-- m_iAmount;//总数减1
	int rc = m_pData[0];
	int s = 0;
	for (int j = 2*s +1; j < m_iAmount; j *= 2)//最后一个数放到第一个位置以后，开始下沉，来维持堆的性质
	{
		if (j < m_iAmount - 1 && m_pData[j] > m_pData[j+1])
		{
			++ j;
		}
		if (rc < m_pData[j])//rc应该插入在s位置上
		{
			break;
		}
		m_pData[s] = m_pData[j];
		s = j;
	}
	m_pData[s] = rc;
	return 1;
}

int Heap::GetMin(int &iVal)
{
	if (m_iAmount == 0)
	{
		return 0;
	}
	iVal = m_pData[0];
	return 1;
}

void Heap::printQueue()
{
	for (int i = 0; i < m_iAmount; ++ i)
	{
		cout << m_pData[i] << " ";
	}
	cout << endl;
}
int main()
{
	Heap heap;
	int n;
	cout<<"input the n:";
	cin>>n;
	while (n--)
	{
		int i;
		cin>>i;
		heap.Enqueue(i);
	}
	int iVal;
	heap.Dequeue(iVal);
	cout<<iVal<<endl;
	heap.Dequeue(iVal);
	cout<<iVal<<endl;

	heap.printQueue();
	return 0;
}
