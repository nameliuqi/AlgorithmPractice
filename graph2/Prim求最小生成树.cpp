//By Sss 2015.4.11
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 100000;
const int oo = 0x7fffffff;
struct Edge{
    int ed, w; //�ߵ��յ�ͱ�Ȩ
    Edge(int _ed, int _w){
        ed = _ed; w = _w;
    }
};
struct Edge2{
    int st, w; //�ߵ����ͱ�Ȩ
};

struct Graph{
    int n; //������
    int m; //����
    vector<Edge*> st[N];
    Edge2 d[N]; //��¼��i���㵽��ǰ�Ѵ�������̾���
    bool flag[N]; //��ǵ�ǰ���Ƿ��Ѵ�����
    void init()
    {
        int x, y, w;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
            st[i].clear();
        for(int i = 0; i < m; i++){
            scanf("%d%d%d", &x, &y, &w);
            st[x].push_back(new Edge(y, w));
            st[y].push_back(new Edge(x, w));
        }
    }

    void Prim()
    {
        cout << "--------Prim�㷨����С����������--------" << endl;
        memset(flag, 0, sizeof(flag));//�����δ����
        memset(d, 0x3f, sizeof(d)); //�������ȫΪ�����

        flag[1] = true; //1�Žڵ���Ϊ����Ѵ���Ŀ�(Ⱦɫ)
        //���������d���飬��ֵΪ��1����̾���
        for(unsigned int i = 0; i < st[1].size(); i++){
            d[st[1][i]->ed].w = st[1][i]->w;
            d[st[1][i]->ed].st = 1;   //��¼�����
        }

        int tot = n - 1; //��С����������n-1����
        int sum = 0;
        while(tot--){//������d������δ��Ⱦɫ�ĵ㵽��Ⱦɫ�����С�����
            int k, mint = oo;
            for(int i = 1; i <= n; i++)
                if(!flag[i] && d[i].w < mint)
                    k = i, mint = d[i].w;
            printf("%d %d %d\n", d[k].st, k, d[k].w);
            sum += d[k].w;
            flag[k] = true;//��k��Ⱦɫ
            for(unsigned int i = 0; i < st[k].size(); i++) //��k��ȥ����d����
                if(d[st[k][i]->ed].w > st[k][i]->w){
                    d[st[k][i]->ed].w = st[k][i]->w;
                    d[st[k][i]->ed].st = k;
                }
        }
        printf("��С��������Ȩֵ��СΪ��%d\n", sum);
    }
};

Graph* G;

int main()
{
    G = new Graph;
    G->init();
    G->Prim();

}
