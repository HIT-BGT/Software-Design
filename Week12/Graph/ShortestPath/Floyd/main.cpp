#include <cstdio>
#include <cstring>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <iostream>
#define MAX_VERTEX_NUM 20
using namespace std;
const int oo = 10000;

int n, m, x, y, w, d[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
void Floyd()
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

}

int Check()
{
    for(int i = 1; i <= n; i++)
        if(d[i][i] < 0){
        //��i���㵽��i������뱻�����ˣ����ڸ�Ȩ��·
            return false;
        }
    return true;
}

int main()
{
//    freopen("");
    printf("������ͼ�Ķ������ͱ�����");
    scanf("%d%d", &n, &m);
    memset(d, oo, sizeof(d));
    for(int i = 1; i <= n; i++)
        d[i][i] = 0;
    for(int i = 0; i < m; i++)
    {
        printf("�������%d���ߵ���㡢�յ��Լ�Ȩֵ��", i+1);
        scanf("%d%d%d", &x, &y, &w);
        d[x][y] = w;
    }
    Floyd();

    if(Check() == false){
        printf("���ڸ�Ȩ��·��\n");
        return 0;
    }
    cout << "���������:";
    cin >> x;
    cout << endl;
    printf("���Ϊ%d�ĵ㵽����������·Ϊ\n", x);
    for(int i = 1; i <= n; i++)
        if(d[x][i] >= oo)
            printf("%d->%d: oo\n", x, i);
        else
            printf("%d->%d: %d\n", x, i, d[x][i]);
    system("pause");
    return 0;
}
