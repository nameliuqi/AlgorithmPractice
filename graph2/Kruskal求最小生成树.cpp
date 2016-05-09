//By Sss 2015.4.11
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100000;

struct Edge{
    int x, y, w; //�ߵ���㣬�յ㣬��Ȩ
};

int cmp(const Edge & A, const Edge & B)
{
    return A.w < B.w;
}
struct Graph{
    int n; //������
    int m; //����
    Edge e[N];
    int fa[N];
    void init()
    {
        scanf("%d%d", &n, &m);
        if(n == 0) return ;
        for(int i = 0; i < m; i++)
            scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
        for(int i = 1; i <= n; i++) fa[i] = i;
    }

    //���鼯�������Ż�Kruskal
    int father(int x)
    {
        if(fa[x] == x) return x;
        return fa[x] = father(fa[x]);
    }

    //Kruskal������С������,������ͼϡ��ʱ
    void Kruskal()
    {
        int sum = 0;
        cout << "---------Kruskal�����õ���С����������--------" << endl;
        sort(e, e + m, cmp);
        for(int i = 0 ; i < m; ++i){
            int fx = father(e[i].x);
            int fy = father(e[i].y);
            if(fx == fy) continue; //�ж������ǲ�����ͬһ����
            fa[fx] = fy; //�ϲ����飨�˱�Ϊ��С�������ߣ�
            sum += e[i].w;
            printf("%d %d %d\n", e[i].x, e[i].y, e[i].w);
        }
        printf("��С��������Ȩֵ��СΪ��%d\n", sum);
    }
};

Graph* G;

int main()
{
    G = new Graph;
    while(true){
        G->init();
        if(G->n == 0) return 0;
        G->Kruskal();
    }
}
