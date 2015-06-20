//����ͼ�޻�·������㷨������������ɨ�裬 o(n + m)
#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <cstring>
const int N = 100;
using namespace std;
struct Edge{
    int ed, w; //�ߵ��յ��ź�Ȩֵ
    Edge* next;
    Edge(int _ed, int _w, Edge* _next)
    {
        ed = _ed; w = _w; next = _next;
    }
};

struct Node{
    int du; //��¼�˵�����
    Edge* e; //�ڽӱ�洢�˵������ı�
    Node()
    {
        du = 0; e = NULL;
    }
};

int n, m, x, y, w, d[N];
Node* Graph[N];

int main()
{
    printf("������ͼ�Ķ������ͱ�����");
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        Graph[i] = new Node();
    for(int i = 0; i < m; i++){
        printf("�������%d���ߵ���㣬�յ��Ȩֵ��", i+1);
        scanf("%d%d%d", &x, &y, &w);
        Graph[x]->e = new Edge(y, w, Graph[x]->e);
        Graph[y]->du++; //���������
    }
    stack<int> S; //�洢���Ϊ��ĵ�
    queue<int> Q; //�洢��������
    while(!S.empty()) S.pop();
    while(!Q.empty()) Q.pop();
    for(int i = 1; i <= n; i++)
        if(Graph[i]->du == 0) S.push(i);
    //������Ƚ�����������
    while(!S.empty()){
        x = S.top(); S.pop();
        Q.push(x);
        for(Edge* p = Graph[x]->e; p != NULL; p = p->next)
        {
            Graph[p->ed]->du--;
            if(Graph[p->ed]->du == 0) S.push(p->ed);
        }
    }
    memset(d, 0x3f, sizeof(d));
    printf("��������㣺");
    cin >> y; d[y] = 0;
    //������������ÿ����Ϊ�����������ĵ����̾���
    while(!Q.empty()){
        x = Q.front(); Q.pop();
        for(Edge* p = Graph[x]->e; p != NULL; p = p->next)
            d[p->ed] = min(d[p->ed], d[x] + p->w);
    }
    printf("���Ϊ%d�ĵ㵽�������е�����·������Ϊ��\n", y);
    for(int i = 1; i <= n; i++){
        printf("%d->%d: ", y, i);
        if(d[i] == 0x3f3f3f3f)
            printf("oo");
        else
            printf("%d", d[i]);
        printf("\n");
    }
}
