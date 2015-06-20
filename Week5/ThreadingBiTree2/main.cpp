#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef enum{Link, Thread} PointTag;
typedef struct Node{    //�����������������ʾ��
    char data;
    Node* lchild, *rchild, *parent;     //ָ�����Һ��Ӽ����ڵ�
    PointTag Ltag, Rtag;    //����������־
}BiNode, *BiTree;
BiTree CreateBiTree(void);  //ǰ����������
void CopyBiTree(BiTree &bt, BiTree &bt2);   //���ƶ�����
void ThreadingBiTree(BiTree &H, BiTree T, int option);   //������������
void PreThreading(BiTree T);    //ǰ��������������
void PreOrderTraverse(BiTree T); //ǰ�����ǰ��������������
void InOrderTraverse(BiTree H); //�������ǰ��������������
void PostThreading(BiTree T);   //����������������
BiTree Parent(BiTree &H, BiTree &P); //Ѱ�ҽڵ�P�ĸ��ڵ�
void PostOrderTraverse(BiTree T);   //�����������������������

int main()
{
    printf("��������ڵ��ֵ����#������գ���");
    BiTree bt = CreateBiTree(), bt2, head, head2;
    CopyBiTree(bt, bt2);
    ThreadingBiTree(head, bt, 1);
    printf("\nǰ�����ǰ���������������Ľ���ǣ�\n"); PreOrderTraverse(head);
    printf("\n�������ǰ���������������Ľ���ǣ�\n"); InOrderTraverse(head);
    ThreadingBiTree(head2, bt2, 2);
    printf("\n������������������������Ľ���ǣ�\n"); PostOrderTraverse(head2);
    printf("\n");
    system("pause");
    return 0;
}

BiTree CreateBiTree(void){
/*ǰ����������*/
    char ch;
    BiTree root;
    scanf(" %c", &ch);
    if (ch == '#') root = NULL;
    else{
        root = (BiTree) malloc (sizeof (BiNode));
        root->data = ch;
        printf("������%c�����ӣ���#������գ���", ch);
        root->lchild = CreateBiTree(); root->Ltag = Link;
        if (root->lchild) root->lchild->parent = root;
        printf("������%c���Һ��ӣ���#������գ���", ch);
        root->rchild = CreateBiTree(); root->Rtag = Link;
        if (root->rchild) root->rchild->parent = root;
    }
    return root; //���ظ��ڵ�
}
void CopyBiTree(BiTree &bt, BiTree &bt2){
/*���ƶ�����*/
    if (bt){
        bt2 = (BiTree)malloc(sizeof(BiNode));
        bt2->data = bt->data;
        CopyBiTree(bt->lchild, bt2->lchild);    //�ݹ鸴��������
        bt2->Ltag = Link;
        CopyBiTree(bt->rchild, bt2->rchild);    //�ݹ鸴��������
        bt2->Rtag = Link;
    }
    else{
        bt2 = NULL;
    }
}
BiTree pre;
void ThreadingBiTree(BiTree &H, BiTree T, int option){
/*������������*/
    H = (BiTree) malloc(sizeof(BiNode));    //Ϊͷ�ڵ�����ռ�
    H->Ltag = Link; H->Rtag = Thread;
    H->rchild = H;  //��ָ���ָ
    if(!T)  H->lchild  = H;     //���������գ�����ָ���ָ
    else{
        pre = H;   //��H����Ϊpreָ��
        H->lchild = T;  //H�������Ӧ���Ƕ������ĸ��ڵ�
        T->parent = H;  //���ڵ�ĸ������ͷ���
        if (option == 1)PreThreading(T);    //ǰ��������������
        else if (option == 2) PostThreading(T);
        if (!pre->rchild) {
            pre->rchild = H;    //ǰ����������һ���ڵ��������ָ��ͷ�ڵ�
            pre->Rtag = Thread;
        }
        H->rchild = pre;
    }
}
void PreThreading(BiTree T){
/*ǰ��������������*/
    if (T){     //�ж����Ƿ�Ϊ��
        if (!T->lchild){    //�����ڽڵ��������ָ����ָ��ǰ���ڵ�
            T->lchild = pre;
            T->Ltag = Thread;
        }
        if (!pre->rchild)   //���ոմ�����Ľڵ��������ָ����ָ���̽ڵ�
        {
            pre->rchild = T;
            pre->Rtag = Thread;
        }
        pre = T;
        if (T->Ltag == Link) PreThreading(T->lchild);   //�ݹ��ǰ����������ǰ�ڵ��������
        if (T->Rtag == Link) PreThreading(T->rchild);   //�ݹ��ǰ����������ǰ�ڵ��������
    }
}
void PreOrderTraverse(BiTree H){

/*ǰ�����ǰ��������������*/
    BiTree root = H->lchild;
    while (root != H){  //�ж��Ƿ��������
        printf("%c ", root->data);
        if (root->Ltag == Link) root = root->lchild;    //�ɷ��Ϊif(root->lchild)???
        else root = root->rchild;
    }
}
void InOrderTraverse(BiTree H){
/*�������ǰ��������������*/
    BiTree root = H->lchild;
    while (root->lchild && (root->Ltag == Link)) root = root->lchild;   //Ѱ����������ĵ�һ�����
    while (root != H){  //�жϱ����Ƿ����
        printf("%c ", root->data);
        if (root->Rtag==Link){  //�����������������Ҷ��������Լ���������������
            root = root->rchild;
            while (root->lchild && (root->Ltag==Link)) root = root->lchild;   //����������������ĵ�һ�����
        }
        else if ((root->Ltag==Link) && (root->Rtag==Thread)){   //��������������
            if (root->rchild == H) root = H;
            else root = root->parent;
        }
        else if ((root->Ltag==Thread) && (root->Rtag==Thread)){ //���Ҷ�����
            if (root==root->parent->lchild)    //�Ǹ��ڵ������
                root = root->parent;
            else if (root == root->parent->rchild){ //�Ǹ��ڵ���Һ���
                if (root->rchild == H) root = H;    //���������ָ��ͷ�ڵ㣬��ôѭ������
                else root = root->rchild->parent;   //�����������ָ��ͷ�ڵ㣬��ôָ���������ĸ��ڵ�
            }
        }
    }

}
void PostThreading(BiTree T){
/*����������������*/
    if(T){
        PostThreading(T->lchild);   //�ݹ�غ�����������ǰ�ڵ��������
        PostThreading(T->rchild);   //�ݹ�غ�����������ǰ�ڵ��������
        if (!T->lchild){    //�����ڽڵ��������ָ����ָ��ǰ���ڵ�
            T->lchild = pre;
            T->Ltag = Thread;
        }
        if (!pre->rchild){  //���ոմ�����Ľڵ��������ָ����ָ���̽ڵ�
            pre->rchild = T;
            pre->Rtag = Thread;
        }
        pre = T;
    }
}
BiTree Parent(BiTree &H, BiTree &P){
/*Ѱ�ҽڵ�P�ĸ��ڵ�*/
    BiTree tmp = P;
    if (H->lchild == P) return H;   //���ڵ���ͷ�ڵ�
    else {
        tmp = H->lchild;  //tmpָ��������ĸ�
        while(tmp->lchild != P && tmp->rchild != P){    //�����δ�ҵ����ڵ�
            if (tmp->Rtag == Link) tmp = tmp->rchild;   //�����ǰ�ڵ�������������������
            else tmp = tmp->lchild; //���������ߣ�������������������
        }
        return tmp;
    }
}
void PostOrderTraverse(BiTree H){
/*�����������������������*/
    BiTree tmp = H, par;
    while (1){      //�ҵ���������ĵ�һ���ڵ�
        while (tmp->Ltag == Link) tmp = tmp->lchild;
        if (tmp->Rtag == Link) tmp = tmp->rchild;
        else break;
    }
    while (tmp != H){   //����û�б���������ʱ
        printf("%c ", tmp->data);
        par = Parent(H, tmp);
        if (par == H) tmp = H;  //���ͷ�ڵ��Ǹ��ڵ�Ļ�����ô��ǰ�ڵ��Ǹ��ڵ㣬�޺��
        else{
            if ((par ->rchild == tmp) || (par->Rtag == Thread) ) tmp = par; //���tmp�Ǹ��ڵ���Һ��ӻ��߶�������
            else{   //����tmp���丸�ڵ������
                par = par->rchild;
                while (1){
                    while (par->Ltag == Link) par = par->lchild;
                    if (par->Rtag == Link) par = par->rchild;
                    else break;
                }
                tmp = par;
            }
        }
    }

}
