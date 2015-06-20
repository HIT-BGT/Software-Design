#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
#define N 1006
using namespace std;

struct node{
    int x, y, w, next;
}e[100006];
int a[N], d[N], head[N],
    ans, tot, n, m, x, y, w;
bool v[N];
queue <int> Q;
void addEdge(int x,int y,int w)
{
    tot++;
    e[tot].x = x; e[tot].y = y; e[tot].w = w;
    e[tot].next = head[x]; head[x] = tot;
}

void spfa(int S)
{
    int x, k;
    memset(d, 0x3f, sizeof(d));
    memset(v, 0, sizeof(v));
    Q.push(S); v[S] = true; //��Դ����Ϊ�ڶ�����
    d[S] = 0;
    while(!Q.empty()) //���п�ʱ˵�����·���Ѿ��ȶ�������
    {
        x = Q.front(); Q.pop(); //ȡ����Ԫ��
        v[x] = false; k = head[x];
        for (k=head[x]; k!=-1; k=e[k].next)
        {
            if(d[x]+e[k].w < d[e[k].y]) //���S��x��y��·������С�����еĴ�S��y��·������
            {
                d[e[k].y] = d[x] + e[k].w;  //�������·������
                if(!v[e[k].y])  //�������y���ڶ����У����������в����
                {
                    Q.push(e[k].y);
                    v[e[k].y] = true;
                }
            }
        }
    }
}
int main()
{
    printf("������ͼ�Ķ������ͱ�����");
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));	//��ʼ��head����
    for(int i = 0; i < m; i++){
        printf("�������%d���ߵ���㡢�յ��Ȩֵ��", i+1);
        scanf("%d%d%d", &x, &y, &w);
        addEdge(x, y, w);
        //addEdge(y, x, w); //�������ͼ�Ĳ���
    }
    int st;
    printf("���������·������㣺");
    scanf("%d", &st);
    spfa(st);
    printf("�Ӷ���%d��������������·���������£�\n", st);
    for (int i=1; i<=n; i++){
        printf("%d->%d: ", st, i);
        if (d[i] >= 0x3f3f3f3f) printf("oo");
        else printf("%d", d[i]);
        printf("\n");
    }
    return 0;
}
