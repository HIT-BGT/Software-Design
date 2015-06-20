#include <iostream>
#include <algorithm>
#include <stdio.h>
#define MAX_VERTEX_NUM 20
#define MAX_EDGE_NUM 190
using namespace std;

/*ʹ��ɭ�ֱ�ʾ���鼯���������νṹ����˫�ױ�ʾ����
���鼯�ϵ��Ż��У�1.�ڲ��鼯�����������ϲ���ʱ�����ǽ�Ԫ���ٵļ��ϲ���Ԫ�ض�ļ�����
              2.�ڲ��鼯�в���ĳ���ڵ����ڵļ���ʱ��ѹ��·����*/
typedef struct{
    int parent; //�洢������λ��
    bool parentag;  //��־parent���Ǵ�Ÿ��ڵ�λ�û����Ӽ�������Ա�ĸ���
    char data;  //�˽���������
}Cell;
typedef struct{
    int vexnum;                 //��Ų��鼯�еĳ�ʼ���ϣ���㣩��
    Cell vexs[MAX_VERTEX_NUM];  //��Ų��鼯�еĳ�ʼ���ϣ���㣩����
}MFset;

typedef struct{
    char start, end; //�ߵ���ʼ������ֹ���
    int weight;     //�ߵ�Ȩֵ
}Edge;

int CreateGraph(MFset &MST, Edge edges[]); //����ͼ
bool cmpare(Edge e1, Edge e2);  //�Ƚ������ߵ�Ȩֵ��С
int find_mfset(MFset &MST, int i);  //�ڲ��鼯�в���Ԫ��i���ڵ��Ӽ�
void merge_mfset(MFset &MST, int i, int j); //�ڲ��鼯�н�Ԫ��i��Ԫ��j���ڵ��Ӽ��ϲ�
void MiniSpanTree_Kruskal(MFset &MST, Edge edges[], int arcnum);    //ʹ��Kruskal\
�㷨����С������
int LocateVex(MFset &MST, char data); //������ͼ�е�λ��

int main()
{
    MFset MST;
    Edge edges[MAX_EDGE_NUM];
    int arcnum = CreateGraph(MST, edges);    //����ͼ
    MiniSpanTree_Kruskal(MST, edges, arcnum);//ʹ��Kruskal�㷨����С������
    system("pause");
    return 0;
}

int CreateGraph(MFset &MST, Edge edges[]){
    /*����ͼ*/
    int arcnum; //���ڼ�¼����
    printf("==========��С������Kruskal�㷨==========\n");
    printf("�����붥������Լ��ߵĸ���(�м��Կո����)��");
    scanf("%d %d", &MST.vexnum, &arcnum);
    getchar();
    for (int i=0; i<MST.vexnum; i++){
        printf("�������%d���������Ϣ��", i+1);
        scanf("%c", &MST.vexs[i].data);
        getchar();
        MST.vexs[i].parent = 1;
        MST.vexs[i].parentag = false;
    }
    for (int i=0; i<arcnum; i++){
        printf("�������%d���ߵ���ʼ��㡢��ֹ����Լ�Ȩֵ��", i+1);
        scanf("%c %c %d", &edges[i].start, &edges[i].end, &edges[i].weight);
        getchar();
    }
    return arcnum;  //���ر���
}
bool cmpare(Edge e1, Edge e2){
    /*�Ƚ������ߵ�Ȩֵ��С*/
    return e1.weight < e2.weight;
}
int find_mfset(MFset &MST, int i){
    /*�ڲ��鼯�в���Ԫ��i���ڵ��Ӽ�*/
    int j, k;
    for (j=i; MST.vexs[j].parentag; j=MST.vexs[j].parent);
    for (k=i; k!=j; k=MST.vexs[k].parent) MST.vexs[k].parent = j;   //ѹ��·��
    return j;
}
void merge_mfset(MFset &MST, int i, int j){
    /*�ڲ��鼯�н�Ԫ��i��Ԫ��j���ڵ��Ӽ��ϲ�*/
    if (MST.vexs[i].parent < MST.vexs[j].parent){
        MST.vexs[i].parent += MST.vexs[j].parent;
        MST.vexs[j].parent = i; MST.vexs[j].parentag = true;
    }else{
        MST.vexs[j].parent += MST.vexs[i].parent;
        MST.vexs[i].parent = j; MST.vexs[i].parentag = true;
    }
}
void MiniSpanTree_Kruskal(MFset &MST, Edge edges[], int arcnum){
    /*ʹ��Kruskal�㷨����С������*/
    int rest = MST.vexnum, cost = 0;   //��¼���鼯��ʣ�༯����
    sort(edges, edges+arcnum, cmpare);  //�Դ�űߵ����鰴��Ȩֵ��������
    printf("��С�������еı��У�\t");
    for (int i=0; i<arcnum&&rest>1; i++){   ///��ʵֻ��Ҫɨ��һ�ξ͹���
        int start_root = find_mfset(MST, LocateVex(MST, edges[i].start)), \
            end_root = find_mfset(MST, LocateVex(MST, edges[i].end));
        if (start_root == end_root) continue;   //���Ȩֵ��С�ߵ������յ���ͬһ��ͨ��֧
        else{
            merge_mfset(MST, start_root, end_root); //�������յ����ڵ��Ӽ��ϲ�
            printf("V%c-V%c\t", edges[i].start, edges[i].end);    //���������
            cost += edges[i].weight;    //�������ߵ�Ȩֵ���뵽��С��������Ȩֵ��
            rest--; //���鼯��ʣ�༯������һ
        }
    }
    printf("\n��С��������Ȩֵ�ǣ�%d\n", cost);
}
int LocateVex(MFset &MST, char data){
    /*������ͼ�е�λ��*/
    for (int i=0; i<MST.vexnum; i++){
        if (MST.vexs[i].data == data){
            return i; break;
        }
    }
    return -1;  //���û�ҵ���Ӧ�ڵ㣬�򷵻�-1
}
