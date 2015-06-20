/*ɭ���������֮���ת��*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODES_NUM 100
using namespace std;

/*�������Ķ�������洢�ṹ*/
typedef struct BiTNode{
    char data;      //������
    BiTNode* lchild, *rchild;   //ָ�����Һ���
}BiTNode, *BiTree;

/*���ĺ�������Ĵ洢��ʾ*/
typedef struct CTNode{  //���ӽڵ�
    int index;
    CTNode* next;   //ָ����һ�����ӽڵ�
}* ChildPtr;
typedef struct{
    char data;
    ChildPtr firstchild;    //���������ͷָ��
}CTBox;
typedef struct{
    CTBox nodes[MAX_NODES_NUM];
    int n, r;               //������͸���λ��
}CTree;

BiTree CreateBiTree(void);  //����������
void HorizontalBiTree(BiTree root, int space); //�����ӡ������, space����ÿ��ǰ�ո���
vector<CTree> CreateCTree(void);   //������
void PrintTree(CTree ctree);     //�Թ������ʽ��ӡ��
void DFSPrint(CTree ctree, int i);  //���Ѵ�ӡ��
vector<CTree> ConvertBTtoF(BiTree bt);    //��������ת��Ϊɭ��
void RecConvertBTtoF(BiTree bt, CTree* CTptr, int index);  //��������ת��Ϊɭ�ֵĵݹ麯��
BiTree ConvertFtoBT(vector<CTree> forest);      //��ɭ��ת��Ϊ������
BiTree RecConvertCTtoBT(CTree ctree, int index);     //����ת��Ϊ�������ĵݹ麯��

int main()
{
    char op;
    printf("==========ɭ�����������ת��=========\n1.������ת����ɭ��\n2.ɭ��ת���ɶ�����\n0.�˳�\n���������ִ����Ӧ������");
    scanf(" %c", &op);
    while (op!='0'){
         switch(op){
            case '1':{
                printf("��������ڵ�����ݣ���#������գ���");
                 BiTree bitree = CreateBiTree();
                printf("������Ķ�����Ϊ��\n");
                HorizontalBiTree(bitree, 1);
                vector<CTree> forest = ConvertBTtoF(bitree);
                printf("==========������ת����ɭ�ֵĽ�����£�==========\n");
                for (int i=0; i<forest.size(); i++) {
                    printf("��%d�����Ĺ������ʽΪ��", i+1);
                    PrintTree(forest[i]);
                }
                break;
            }
            case '2':{
                vector<CTree> cforest = CreateCTree();
                for (int i=0; i<cforest.size(); i++) {
                    printf("��%d�����Ĺ������ʽΪ��", i+1);
                    PrintTree(cforest[i]);
                }
                BiTree result = ConvertFtoBT(cforest);
                printf("==========ɭ��ת���ɶ������Ľ�����£�==========\n");
                HorizontalBiTree(result, 1);
                break;
                }
    }
    printf("==========ɭ�����������ת��=========\n1.������ת����ɭ��\n2.ɭ��ת���ɶ�����\n0.�˳�\n���������ִ����Ӧ������");
    scanf(" %c", &op);
}
    return 0;
}

BiTree CreateBiTree(void){
/*����������*/
    char ch;
    BiTree root;
    scanf(" %c", &ch);
    if (ch == '#') root = NULL;
    else{
        root = (BiTree) malloc (sizeof (BiTNode));
        root->data = ch;
        printf("������%c�����ӣ���#������գ���", ch);
        root->lchild = CreateBiTree();
        printf("������%c���Һ��ӣ���#������գ���", ch);
        root->rchild = CreateBiTree();
    }
    return root; //���ظ��ڵ�
}
void HorizontalBiTree(BiTree root, int space) {
/*�����ӡ������*/
    if (root){
        HorizontalBiTree(root->rchild, space+1);   //�ݹ�����ӡ������
        for (int i=0; i<2*space; i++) printf(" ");
        printf("%c\n", root->data);                     //��ӡ�ڵ���Ϣ
        HorizontalBiTree(root->lchild, space+1);  //�ݹ�����ӡ������
    }
}
vector<CTree> CreateCTree(void){
/*������*/
    char prefix[5] = "tree", filename[10] = "";
    vector<CTree> forest;
    for (int i=1; ; i++){
        sprintf(filename, "%s%d", prefix, i);
        ifstream in(filename);
        if (!in) break;
        CTree ctree;
        string inputStr;
        char* charIndex;
        int count = 0;
        ChildPtr tmpPtr;
        getline(in, inputStr);
        while (strcmp(inputStr.c_str(), "")){
            char* inputStr2 = new char[inputStr.length() + 1];
            strcpy(inputStr2, inputStr.c_str());
            char* firstnode = strtok(inputStr2, " ");
            ctree.nodes[count].data = firstnode[0];
            if (!(charIndex = strtok(NULL, " "))) ctree.nodes[count++].firstchild = NULL;
            else (tmpPtr = ctree.nodes[count++].firstchild = (ChildPtr)malloc(sizeof(CTNode)))->index = atoi(charIndex);
            while ((charIndex = strtok(NULL, " "))) {
                ChildPtr child  = (ChildPtr) malloc(sizeof(CTNode));
                child->index = atoi(charIndex);
                tmpPtr->next = child;
                tmpPtr = child;
            }
            tmpPtr->next = NULL;
            getline(in, inputStr);
        }
        ctree.n = count;
        ctree.r = 0;
        forest.push_back(ctree);
    }
    return forest;
}
int visit[MAX_NODES_NUM];
void PrintTree(CTree ctree){
/*�Թ������ʽ��ӡ��*/
    for (int i=0; i<ctree.n; i++) visit[i] = 0;
    for (int i=0; i<ctree.n; i++){  //�����ǰ����δ���ʵĽڵ㣬��������Ѵ�ӡ
        if (!visit[i])  DFSPrint(ctree, i);
    }
    printf("\n");
}
void DFSPrint(CTree ctree, int i){
/*���Ѵ�ӡ��*/
    bool flag = true;
    printf("%c", ctree.nodes[i].data);
    if (ctree.nodes[i].firstchild) printf("(");
    else flag = false;
    visit[i] = 1;
    ChildPtr p = ctree.nodes[i].firstchild;  //��pָ��ڵ�i�ĺ��������ͷ�ڵ�
    while (p){
        if (!visit[p->index]) DFSPrint(ctree, p->index);
        if (p->next) printf(",");
        p = p->next;
    }
    if (flag) printf(")");
}
vector<CTree> ConvertBTtoF(BiTree bt){
    /*��������ת��Ϊɭ��*/
    vector<CTree> CTvec;
    BiTree tmp = bt;
    while(tmp){
        CTree ctree;
        ctree.nodes[0].data = tmp->data;
        ctree.nodes[0].firstchild = NULL;
        ctree.r = 0; ctree.n = 1;
        RecConvertBTtoF(tmp->lchild, &ctree, 0);
        CTvec.push_back(ctree);
        tmp = tmp->rchild;
    }
    return CTvec;
}
void RecConvertBTtoF(BiTree bt, CTree* CTptr, int index){
    /*��������ת��Ϊɭ�ֵĵݹ麯��*/
    if (bt){
        BiTree tmp = bt;
        while (tmp){
            CTptr->nodes[CTptr->n].data = tmp->data;
            CTptr->nodes[CTptr->n].firstchild = NULL;
            if(!CTptr->nodes[index].firstchild){
                ChildPtr firstptr = (ChildPtr)malloc(sizeof(CTNode));
                firstptr->index = CTptr->n;
                firstptr->next = NULL;
                CTptr->nodes[index].firstchild = firstptr;
            }
            else{
                ChildPtr child = CTptr->nodes[index].firstchild;
                while(child->next) child = child->next;
                ChildPtr ptr = (ChildPtr)malloc(sizeof(CTNode));
                ptr->index = CTptr->n;
                ptr->next = NULL;
                child->next = ptr;
            }
            CTptr->n++;
            RecConvertBTtoF(tmp->lchild, CTptr, CTptr->n-1);
            tmp = tmp->rchild;
        }
    }
}
BiTree ConvertFtoBT(vector<CTree> forest){
/*��ɭ��ת��Ϊ������*/
    BiTree root, tmp;
    for (int i=0; i<forest.size(); i++){
        BiTree sibling = (BiTree)malloc(sizeof(BiTNode));
        sibling->data = forest[i].nodes[forest[i].r].data;
        sibling->lchild = RecConvertCTtoBT(forest[i], forest[i].r);
        if (!i) root = tmp = sibling;
        else{
            tmp->rchild = sibling;
            tmp = sibling;
        }
    }
    tmp->rchild = NULL;
    return root;
}
BiTree RecConvertCTtoBT(CTree ctree, int index){
    /*����ת��Ϊ�������ĵݹ麯��*/
    if (ctree.nodes[index].firstchild){
        BiTree child = (BiTree)malloc(sizeof(BiTNode));
        ChildPtr tmp = ctree.nodes[index].firstchild;       //tmpָ��ָ�������ĺ��������е�ǰ�����Ľڵ�
        child->data = ctree.nodes[tmp->index].data;
        child->lchild = RecConvertCTtoBT(ctree, tmp->index);
        tmp = tmp->next;
        BiTree remem = child;   //rememָ��ոմ����Ķ������ڵ�
        for ( ; tmp; tmp = tmp->next, remem = remem->rchild){
            BiTree sibling = (BiTree)malloc(sizeof(BiTNode));
            sibling->data = ctree.nodes[tmp->index].data;
            sibling->lchild = RecConvertCTtoBT(ctree, tmp->index);
            remem->rchild = sibling;
        }
        remem->rchild = NULL;
        return child;
    }
    return NULL;
}
