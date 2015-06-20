#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTEX_NUM  20
using namespace std;

//ͼ���ڽӱ�洢�ṹ
typedef struct ArcCell{
    int adjvex; //�ߵ��ڽӶ�����ͼ�е�λ��
    int weight; //�ߵ�Ȩֵ
    struct ArcCell* next;  //ָ����һ����
}ArcCell;
typedef struct{
    char data;  //��Ŷ������Ϣ
    ArcCell* firstarc;  //�����ڴ˶���ĵ�һ����
}Node;
typedef struct{
    int vexnum, arcnum; //���ͼ�Ķ�����Ŀ�ͱߵ���Ŀ
    Node vexs[MAX_VERTEX_NUM+1];   //��Ŷ��������
}Gragh;

typedef struct { //�������鶨��
        int startnum;   //�����
        int adjvex;    //Ȩֵ��С�ߵ���һ�ڽӶ���
        int lowcost;    //Ȩֵ��С�ߵ�Ȩֵ
}Elem;

void CreateGraph(Gragh &G); //��������ͼ
int LocateVex(Gragh &G, char data); //��ͼ��ȷ������Ϊdata�Ķ����λ��
void MiniSpanTree_Prim(Gragh &G); //��Prim�㷨����ͼG����С������
void Swap(int i, int j); //����closedge�������±�Ϊi��j������Ԫ��
void PushDown(int first, int last); //����ѣ���closedge[first]���Ƶ���\
���ʵ�λ��
void MakeHeap(int num);    //��Elem���͵������ǰn��Ԫ������ɶ�

int main()
{
    Gragh G;    //����һ������ͼ
    CreateGraph(G); //��������ͼ
    MiniSpanTree_Prim(G);   //������С������
    return 0;
}

int LocateVex(Gragh &G, char data){
    /*��ͼ��ȷ������Ϊdata�Ķ����λ��*/
    for (int i=1; i<=G.vexnum; i++){
        if (G.vexs[i].data == data){
            return i; break;
        }
    }
    return -1;  //��û�ҵ��ö���Ļ�����-1
}
void CreateGraph(Gragh &G){
    /*��������ͼ*/
    printf("������ͼ�Ķ������ͱ������м��Կո�ָ�����");
    scanf("%d %d", &G.vexnum, &G.arcnum);
    getchar();
    int i;
    for (i=1; i<=G.vexnum; i++){
        printf("�������%d���������Ϣ", i);
        scanf("%c", &G.vexs[i].data);
        getchar();
        G.vexs[i].firstarc = NULL;
    }
    for (i=0; i<G.arcnum; i++){
        char start_data, end_data;  //������ʱ����û�����ıߵ���Ϣ
        int start, end, weight;
        printf("�������%d���ߵ���ʼ���㡢��ֹ�����Ȩֵ", i+1);
        scanf("%c %c %d", &start_data, &end_data, &weight);
        getchar();
        start = LocateVex(G, start_data); end = LocateVex(G, end_data);
        ArcCell* arcptr = (ArcCell*) malloc (sizeof(ArcCell));
        arcptr->adjvex = end;
        arcptr->weight = weight;
        arcptr->next = G.vexs[start].firstarc;  //ʹ�����߳�Ϊ������start�ĵ�һ����
        G.vexs[start].firstarc = arcptr;
        ArcCell* arcptr2 = (ArcCell*) malloc (sizeof(ArcCell));
        arcptr2->adjvex = start;
        arcptr2->weight = weight;
        arcptr2->next = G.vexs[end].firstarc;
        G.vexs[end].firstarc = arcptr2;
    }
}
int pos[MAX_VERTEX_NUM+1];  //��¼���Ϊi�Ķ����ڶ���pos[i]��λ��
Elem closedge[MAX_VERTEX_NUM+1];    //��������

void MiniSpanTree_Prim(Gragh &G){
    /*��Prim�㷨����ͼG����С������*/
    printf("�����ô��ĸ����㿪ʼ������С�������������룺");
    char v = getchar();
    int k = LocateVex(G, v);    //ȷ������k��ͼ�е�λ��
    int i;
    pos[k] = k;
    closedge[k].startnum = k;
    closedge[k].lowcost = 0;    //��������k�Ѿ����뵽��С����������
    for (i=1; i<=G.vexnum; i++){
        if (i!=k){
            pos[i] = i;
            closedge[i].startnum = i;
            closedge[i].adjvex = k;
            closedge[i].lowcost = INT_MAX;  //�Ƚ���������ʼ��Ϊ����
        }
    }
    for (ArcCell* ptr=G.vexs[k].firstarc; ptr; ptr=ptr->next){  //���������붥��k�����б�
        closedge[ptr->adjvex].lowcost = ptr->weight;    //����k�ڽӶ��������������
    }
    int record = G.vexnum;  //��¼�洢�ߵĶ���Ԫ�ظ���
    MakeHeap(record); //�����б�����ɶ�
    while (!closedge[1].lowcost){  //ȡ���Ѿ����뵽��С�������Ķ���
        Swap(1, record);
        record--;
        PushDown(1, record);
    }
    printf("���뵽��С�������еı��У�\t");
    for (i=1; i<=G.vexnum-1; i++){  //����С�������м���|V|-1������
        printf("V%c-V%c\t",G.vexs[closedge[1].adjvex].data, \
               G.vexs[closedge[1].startnum].data);
        closedge[1].lowcost = 0;
        for (ArcCell* ptr = G.vexs[closedge[1].startnum].firstarc; ptr; \
        ptr=ptr->next ){    //���Ǹռ����������ڽӱ�
            if (ptr->weight < closedge[pos[ptr->adjvex]].lowcost){  //����Ȩֵ��С��
                closedge[pos[ptr->adjvex]].lowcost = ptr->weight;
                closedge[pos[ptr->adjvex]].adjvex =\
                closedge[1].startnum;
            }
        }
        Swap(1, record); //���ոռ�����С�������Ķ����Ƴ���
        record--;   //����Ԫ�ظ�����һ
        PushDown(1, record);    //�����
    }
}
void Swap(int i, int j){
    /*����closedge�������±�Ϊi��j������Ԫ��*/
    Elem tmp = closedge[i]; //������������Ԫ��
    closedge[i] = closedge[j];
    closedge[j] = tmp;
    pos[closedge[i].startnum] = i;
    pos[closedge[j].startnum] = j;
}
void PushDown(int first, int last){
    /*����ѣ���closedge[first]���Ƶ������ʵ�λ��*/
    int r;
    r = first;
    while (r <= last/2){    //��ʱ���ܻ���Ҫ������
        if (2*r == last){
            if (closedge[r].lowcost > closedge[last].lowcost){
                Swap(r, last);
            }
            r = last;
        }else if (closedge[2*r].lowcost <= closedge[2*r+1].lowcost && \
                  closedge[r].lowcost > closedge[2*r].lowcost){
                    Swap(r, 2*r); //����r��r�������
                    r = 2*r;

        }else if (closedge[2*r].lowcost > closedge[2*r+1].lowcost && \
                 closedge[r].lowcost > closedge[2*r+1].lowcost)
                {
                    Swap(r, 2*r+1); //����r��r���Ҷ���
                    r = 2*r + 1;
        }else{
            r = last;   //���϶ѵĶ��壬ѭ������
        }
    }
}
void MakeHeap(int num){
    /*��Elem���͵������ǰn��Ԫ������ɶ�*/
    for (int i=num/2; i>=1; i--){
        PushDown(i, num);
    }
}
