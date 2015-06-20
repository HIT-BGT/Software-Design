#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#define MAX_VERTEX_NUM 20

using namespace std;
/*����ͼ���ڽӱ�洢�ṹ*/
typedef struct ArcNode{
    int adjvex; //�ñ���ָ�򶥵���ͼ�е�λ��
    ArcNode *next;  //ָ����һ���ߵ�ָ��
    bool been;  //��ʶ�Ƿ��Ѿ��߹�������
}ArcNode;
typedef struct VNode{
    char data;  //������Ϣ
    ArcNode *firstarc;  //ָ�������ڸö���ĵ�һ���ߵ�ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertices;   //��Ŷ������������
    int vexnum, arcnum; //�ֱ��Ŷ������ͱ���
}UndiGraph;
typedef struct Edge{
    int sour;   //�ߵ����
    int dest;   //�ߵ��յ�
}Edge;

void CreateUDG(UndiGraph &G);   //��������ͼ
int LocateVex(UndiGraph &G, char vexdata);    //��ͼ��Ѱ�ҽ����ϢΪvexdata�Ķ��㣬��������ͼ��λ��
void FindBiComponent(UndiGraph &G);     //������ͼG�в��Ҳ��������˫��ͨ����
void DFSBiComponet(UndiGraph &G, int v0);   //�Ӷ���v0������������ȱ���ͼG�����Ҳ����˫��ͨ����
void PrintBiComponent(UndiGraph &G, int sour, int dest);  //��ӡ˫��ͨ����

stack<Edge> edgestk;
int count, visited[MAX_VERTEX_NUM] = {0}, low[MAX_VERTEX_NUM] = {0};
int main()
{
    UndiGraph G;
    CreateUDG(G);
    DFSBiComponet(G, 0);
    return 0;
}

int LocateVex(UndiGraph &G, char vexdata){
    /*��ͼ��Ѱ�ҽ����ϢΪvexdata�Ķ��㣬��������ͼ��λ��*/
    for (int i=0; i<G.vexnum; i++)
        if (vexdata == G.vertices[i].data) return i;
    return -1;
}

void CreateUDG(UndiGraph &G){
    /*��������ͼ*/
    int i;
    printf("����������ͼ�Ľ������Լ��߸������м��Կո��������");
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
        arc->been = false;
        arc->adjvex = LocateVex(G, dest);
        arc->next = G.vertices[LocateVex(G, sour)].firstarc;
        G.vertices[LocateVex(G, sour)].firstarc = arc;
        ArcNode* arc2 = (ArcNode*) malloc (sizeof(ArcNode));
        arc2->been = false;
        arc2->adjvex = LocateVex(G, sour);
        arc2->next = G.vertices[LocateVex(G, dest)].firstarc;
        G.vertices[LocateVex(G, dest)].firstarc = arc2;
    }
}
void DFSBiComponet(UndiGraph &G, int v0){
    /*�Ӷ���v0������������ȱ���ͼG�����Ҳ����˫��ͨ����*/
    int mini = visited[v0] = ++count;   //������v0����������ȱ��
    for (ArcNode* ptr=G.vertices[v0].firstarc; ptr; ptr = ptr->next){
        //����v0������������ڽӶ���
        int w = ptr->adjvex;
        if (!ptr->been){
            Edge edge = {v0, w};
            edgestk.push(edge);
            ptr->been = true;
            for (ArcNode* ptr2=G.vertices[w].firstarc; ptr2; ptr2=ptr2->next){
                if (ptr2->adjvex == v0) {
                    ptr2->been = true; break;
                }
            }
        }
            if (!visited[w]){   //w��δ���ʹ����¶���
                DFSBiComponet(G, w);    //�����low[w]
                if (low[w]<mini) mini = low[w];
                if (low[w]>=visited[v0]){   //v0�ǹؽڵ�
                PrintBiComponent(G, v0, w);
                }
            }else if(visited[w] < mini) //w�����Ƚ��
                mini = visited[w];
        }
        low[v0] = mini;
    }
void PrintBiComponent(UndiGraph &G, int sour, int dest){
    /*��ӡ˫��ͨ����*/
    printf("���: %c ", G.vertices[sour].data);
    printf("�µ�˫��ͨ������");
    while(!((edgestk.top().sour==sour) && (edgestk.top().dest==dest))){
        Edge topedge = edgestk.top(); edgestk.pop();
        printf("<%c,%c>", G.vertices[topedge.sour].data, G.vertices[topedge.dest].data);
    }
    printf("<%c,%c>", G.vertices[sour].data, G.vertices[dest].data);
    printf("\n");
}
