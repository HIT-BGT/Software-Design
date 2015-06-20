#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1000;
const int inf = 0x3f3f3f3f;
struct Edge{
    int ed, w;
    Edge(int _ed, int _w)
    {
        ed = _ed; w = _w;
    }
};
vector<Edge> st[N];
int n, m, d[N];
bool vis[N];
void Dijkstra(int s) {
    memset(d, 0x3f, sizeof(d)); //��ʼʱ����ֵΪ�����
    memset(vis, false, sizeof(vis)); //����Ƿ����
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int k = 0, mint = inf;
        //��һ������������̵ĵ�
        for (int j = 1; j <= n; j++)
            if (!vis[j] && d[j] < mint)
                mint = d[j], k = j;
        if (k == 0) break; //û�ҵ���˵���Ѿ���������
        vis[k] = true; //�ҵ��ĵ�Ϊk
        for (int j = 0, ed, w; j < (int)st[k].size(); j++) {
            ed = st[k][j].ed, w = st[k][j].w;
            if (!vis[ed] && d[ed] > d[k] + w)
                d[ed] = d[k] + w;
        }
    }
}
int main()
{
    //freopen("Graph.txt", "r", stdin);
    printf("������ͼ�Ķ������ͱ�����");
    scanf("%d%d", &n, &m);
    for (int i=0; i<=n; i++) st[i].clear();
    for (int i=0, a, b, c; i<m; i++) {
        printf("�������%d���ߵ���㡢�յ��Լ�Ȩֵ��", i+1);
        scanf("%d%d%d", &a, &b, &c);
        st[a].push_back(Edge(b, c));
        st[b].push_back(Edge(a, c));
    }
    int s;
    printf("���������:");
    scanf("%d", &s);
    Dijkstra(s);
    printf("���Ϊ%d�ĵ㵽����������·���£�\n", s);
    for(int i = 1; i <= n; i++)
        printf("%d: %d\n", i, d[i]);
    system("pause");
    return 0;
}
