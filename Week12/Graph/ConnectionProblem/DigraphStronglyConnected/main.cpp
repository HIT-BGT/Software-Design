/*����Tarjan�㷨������ͼ��ǿ��ͨ����*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#define MAX_VERTEX_NUM 20
using namespace std;

/*����ͼ���ڽӱ�洢�ṹ*/
typedef struct ArcNode{
    int adjvex; //�ñ���ָ�򶥵���ͼ�е�λ��
    ArcNode *next;  //ָ����һ���ߵ�ָ��
}ArcNode;
typedef struct VNode{
    char data;  //������Ϣ
    ArcNode *firstarc;  //ָ�������ڸö���ĵ�һ���ߵ�ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertices;   //��Ŷ������������
    int vexnum, arcnum; //�ֱ��Ŷ������ͱ���
}DiGraph;

stack<int> vertexstk;   //���ڴ�Ŷ����ջ

int LocateVex(DiGraph &G, char vexdata);  //��ͼG��ȷ����ϢΪdata�Ľ��λ��
void CreateDG(DiGraph &G);  //��������ͼ
void FindStrConnectedComponent(DiGraph &G); //������ͼG��Ѱ�Ҳ����ǿ��ͨ����
void Tarjan(DiGraph &G, int v0);    //��ͼG�дӱ��Ϊv0�Ķ��㿪ʼ����Tarjan�㷨

int count;                      //���ڼ���DFS����
int visited[MAX_VERTEX_NUM];    //���ڴ��DFS���㱻���ʵĴ���
int low[MAX_VERTEX_NUM];        //���ڴ��u��u�������ܹ�׷�ݵ�DFSʱ���类���ʵĶ���
bool instack[MAX_VERTEX_NUM];    //���ڼ�¼�����Ƿ���ջ��

int main()
{
    DiGraph G;
    CreateDG(G);    //��������ͼ
    FindStrConnectedComponent(G);   //��Tarjan�㷨Ѱ��ǿ��ͨ����
    system("pause");
    return 0;
}

int LocateVex(DiGraph &G, char vexdata){
    /*��ͼ��Ѱ�ҽ����ϢΪvexdata�Ķ��㣬��������ͼ��λ��*/
    for (int i=0; i<G.vexnum; i++)
        if (vexdata == G.vertices[i].data) return i;
    return -1;
}

void CreateDG(DiGraph &G){
    /*��������ͼ*/
    int i;
    printf("����������ͼ�Ľ������Լ��ߵĸ������м��Կո��������");
    scanf("%d %d", &G.vexnum, &G.arcnum);
    getchar();
    for (i=0; i<G.vexnum; i++){
        printf("������� %d ��������Ϣ��", i+1);
        G.vertices[i].data = getchar();
        getchar();
        G.vertices[i].firstarc = NULL;
    }
    for (i=0; i<G.arcnum; i++){
        char sour, dest;
        printf("������� %d ���ߵ������յ㣨�м��Կո��������", i+1);
        scanf("%c %c", &sour, &dest);
        getchar();
        ArcNode* arc = (ArcNode*) malloc (sizeof(ArcNode));
        arc->adjvex = LocateVex(G, dest);
        arc->next = G.vertices[LocateVex(G, sour)].firstarc;
        G.vertices[LocateVex(G, sour)].firstarc = arc;
    }
}

void FindStrConnectedComponent(DiGraph &G){
    /*������ͼG��Ѱ�Ҳ����ǿ��ͨ����*/
    count = 0;  //��������ʼ��
    memset(visited, 0, sizeof(visited));    //�����ʼ��
    memset(low, 0, sizeof(low));
    memset(instack, 0, sizeof(instack));
    for (int i=0; i<G.vexnum; i++)
        if (!visited[i]) Tarjan(G, i);
}

void Tarjan(DiGraph &G, int v0){
    /*��ͼG�дӱ��Ϊv0�Ķ��㿪ʼ����Tarjan�㷨*/
    int mini = visited[v0] = ++count;
    vertexstk.push(v0); //������v0ѹ��ջ��
    instack[v0] = true;
    for (ArcNode* ptr = G.vertices[v0].firstarc; ptr; ptr=ptr->next){
        //����v0��ÿ���ڽӶ���
        int w = ptr->adjvex;
        if (!visited[w]){   //w�Ǵ�δ���ʹ��Ķ���
            Tarjan(G, w);   //�����low[w]
            if (low[w] < mini) mini = low[w];
        }else if (instack[w] && visited[w] < mini){
            mini = visited[w];
        }
    }
    low[v0] = mini;
    if (visited[v0] == low[v0]){    //��ô��v0Ϊ����DFS������һ��ǿ��ͨ����
        printf("�µ�ǿ��ͨ������"); //��ӡǿ��ͨ����
        int tmp;
        do{
            tmp = vertexstk.top();  vertexstk.pop();    //����ջ��Ԫ��
            instack[tmp] = false;
            printf("%c ", G.vertices[tmp].data);
        }while (tmp != v0);
        printf("\n");
    }
}
