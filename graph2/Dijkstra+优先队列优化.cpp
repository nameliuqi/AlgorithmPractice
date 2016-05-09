#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define MAXN 1000002
using namespace std;
bool flag[MAXN];
int dist[MAXN],n;
struct Node{
	int id,val;
	Node(){}
	Node(int _id,int _val):id(_id),val(_val){}
	bool operator<(const Node &a)const{
//����<,ʹ���ȶ��ж���ʼ����val��С��Ԫ��
		return val > a.val;
	}
};
struct Old{
	int u,v,w;
	Old(){}
	Old(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
}a[MAXN];
struct Edge{
	int v,cost;
	Edge(){}
	Edge(int _v,int _cost):v(_v),cost(_cost){}
};
vector<Edge>mp[MAXN];                                        //mp[i][j].v��ʾi�ĵ�j�������ӵ��Ƕ���v��ȨֵΪmp[i][j].cost
long long dijkstra(int s){
	int i,j,k,v,cost;
	Node tep,tep2;
	memset(flag,false,sizeof(flag));
	memset(dist,0x7f,sizeof(dist));
	priority_queue<Node>que;
	while(!que.empty()) que.!pop();//��ն���
	dist[s] = 0;
	tep.id = s;
	tep.val = 0;
	que.push(tep);   //������
	while(!que.empty()){
		tep = que.top();
		que.pop();
		if(flag[tep.id]) continue;
 //���tep.id�Ѿ��ڼ����У������ó�
		flag[tep.id] = true;                                                  //��tep.id���뼯��
		for(i = 0;i < mp[tep.id].size(); i++){
			v = mp[tep.id][i].v;
			cost = mp[tep.id][i].cost;
			if(!flag[v] && dist[v] > dist[tep.id] + cost){                //�ɳ�
				dist[v] = dist[tep.id] + cost;
				tep2.id = v;
				tep2.val = dist[v];
    //���ȶ����а��ڵ�Ȩֵ���У���С����
				que.push(tep2);                                     //���뼯��
			}
		}
	}
	long long sum = 0;
	for(i = 1;i <= n; i++) sum += dist[i];
	return sum;
}
int main()
{
	int i,j,k,m,T;
        int u,v,w;
        long long ans;
        scanf("%d",&T);
        while(T--){
                scanf("%d%d",&n,&m);
                for(i = 1;i <= n; i++) mp[i].clear();
                for(i = 1;i <= m;i++){
                        scanf("%d%d%d",&u,&v,&w);
                        a[i] = Old(u,v,w);
                        mp[u].push_back(Edge(v,w));
                }
                ans = 0;
                ans += dijkstra(1);
                for(i = 1;i <= n; i++) mp[i].clear();
                for(i = 1;i <= m; i++){
                        u = a[i].u;
                        v = a[i].v;
                        w = a[i].w;
                        mp[v].push_back(Edge(u,w));
                }
                ans += dijkstra(1);
                printf("%I64d/n",ans);
        }
}
