#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

//��㣨ƽ�������Ĵ洢�ṹ
typedef struct Node{
    int data;   //���������
    int bf;     //ƽ������
    Node* lchild, *rchild;  //���Ӻ��Һ���
}AVLNode, *AVLTree;

void R_Rotate(AVLTree &p){
    //����*pΪ���ڵ��������������
    AVLTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p; p = lc;
}
void L_Rotate(AVLTree &p){
    //����*pΪ���ڵ��������������
    AVLTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p; p = rc;
}
void LeftBalance(AVLTree &T){
    //����*TΪ���ڵ��������ƽ�⴦��
    AVLTree lc = T->lchild; //���ڵ������
    switch(lc->bf){
    case 1: //�������ߣ���������
        R_Rotate(T);
        T->bf = T->rchild->bf = 0;  //����ƽ������
        break;
    case -1: //�������ߣ�������������
        AVLTree rd = lc->rchild;    //���ڵ�����ӵ��Һ���
        L_Rotate(T->lchild);   //������������
        R_Rotate(T);    //��������������
        T->bf = 0;      //����ƽ������
        switch(rd->bf){
        case 1: //���뵽��������������������������
            T->lchild->bf = 0;
            T->rchild->bf = -1;
            break;
        case -1:    //���뵽��������������������������
            T->rchild->bf = 0;
            T->lchild->bf = 1;
            break;
        //case 0?
        }
        break;
    }
}
void RightBalance(AVLTree &T){
    //����*TΪ���ڵ��������ƽ�⴦��
    AVLTree rc = T->rchild; //���ڵ���Һ���
    switch(rc->bf){
    case -1:    //�½����뵽���Һ��ӵ���������
        L_Rotate(T);    //��������
        T->bf = T->lchild->bf = 0;  //����ƽ������
        break;
    case 1:     //�½����뵽���Һ��ӵ��������ϣ�������������
        AVLTree ld = rc->lchild;    //���ڵ���Һ��ӵ�����
        R_Rotate(T->rchild);   //�ȶԸ���������������
        L_Rotate(T);    //�ٶ�����������
        T->bf = 0;      //����ƽ������
        switch(ld->bf){
        case 1: //���뵽�˸��ڵ���Һ��ӵ����ӵ���������
            T->lchild->bf = 0;
            T->rchild->bf = -1;
            break;
        case -1:
            T->lchild->bf = 1;
            T->rchild->bf = 0;
            break;
        }
        break;
    }
}
bool InsertNode(AVLTree &T, int e, bool &taller){
    /*����*TΪ����ƽ��������в���һ����e����ͬ�ؼ��ֵĽ��
    ����ɹ�����true�����򷵻�false��taller��ӳƽ�����������*/
    if (!T){    //*T�ǿ���
        T = (AVLTree) malloc (sizeof(AVLNode));
        T->data = e;
        T->bf = 0;
        T->lchild = T->rchild = NULL;
        taller = true;
    }else{
        if (T->data == e){
            taller = false;
            return false;
        }
        if (e<T->data){ //��ô���Ӧ���뵽*T����������
            if (!InsertNode(T->lchild, e, taller)) return false;    //���벻�ɹ�
            if (taller){    //������������
                switch (T->bf){ //���T��ƽ������
                case 1:
                    LeftBalance(T); taller = false; break;
                case 0:
                    T->bf = 1; taller = true;   break;
                case -1:
                    T->bf = 0;  taller = false; break;
                }
            }
        }
        else {  //��ô���Ӧ���뵽*T����������
            if (!InsertNode(T->rchild, e, taller)) return false;    //���벻�ɹ�
            if (taller){    //������������
                switch(T->bf){
                case 1:
                    T->bf = 0; taller = false; break;
                case 0:
                    T->bf = -1; taller = true; break;
                case -1:
                    RightBalance(T); taller = false; break;
                }
            }
        }
    }
    return true;
}
bool DeleteNode(AVLTree &T, int e, bool &lower){
    /*��ƽ������ɾ��һ���ؼ���Ϊe�Ľ��*/
    bool return_flag;    //���ɾ�������Ƿ�ɹ�
    int lfort; //�����ɾ���������ϵĽ�㻹���������ϵĽ��
    if (!T) return false;   //������ɾ��ʧ��
    if (T->data == e){
        //�ҵ�����Ҫɾ���Ľ��
        if (T->rchild == NULL){ //����ýڵ����Һ���
            T = T->lchild;
            lower = true;
            return true;
        }else{  //�ýڵ����Һ���
            AVLTree rc = T->rchild; //�ҵ��������йؼ�����С���
            while (rc->lchild) rc = rc->lchild;
            T->data = rc->data;
            return_flag = DeleteNode(T->rchild, rc->data, lower);
            lfort = -1; //���ɾ����Ϊ�������ϵĽ��
        }
    }else if(e<T->data){
        return_flag = DeleteNode(T->lchild, e, lower);  //����������ɾ���ý��
        lfort = 1;
    }else{
        return_flag = DeleteNode(T->rchild, e, lower);  //����������ɾ���ý��
        lfort = -1;
    }
    if (lower){ //��������䰫��
        switch(lfort){
        case 1: //�������䰫��
            switch(T->bf){
            case 1:
                T->bf = 0; lower = true;   break;
            case 0:
                T->bf = -1; lower = false; break;
            case -1:
                RightBalance(T); lower = true; break;
            }
            break;
        case -1:    //�������䰫��
            switch(T->bf){
            case 1:
                LeftBalance(T); lower = true; break;
            case 0:
                T->bf = 1; lower = false; break;
            case -1:
                T->bf = 0; lower = true; break;
            }
            break;
        }
    }
    return return_flag;
}
AVLTree SearchNode(AVLTree &T, int key){
    //��ƽ�����в��ҹؼ���Ϊkey�Ľ��
    if (!T) return NULL;    //��Ϊ�յ����
    if (T->data == key) return T;
    else if (key < T->data) return (SearchNode(T->lchild, key));
    else return (SearchNode(T->rchild, key));
}
void DisplayTree(AVLTree &T, int space_num){
    //����ӡƽ����
    if (T){
        if (T->rchild) DisplayTree(T->rchild, space_num+1);
        for (int i=0; i<2*space_num; i++) printf(" ");
        printf("%d\n", T->data);
        if (T->lchild) DisplayTree(T->lchild, space_num+1);
    }
}
int main()
{
    char op;
    AVLTree T = NULL;
    int key;
    bool taller, lower, flag = true;
    while (flag){
        printf("==========ƽ������AVL����==========\n\
1. ����\n\
2. ����\n\
3. ɾ��\n\
0. �˳�\n\
====================================\n\
���������ִ����Ӧ������");
        op = getchar();
        switch(op){
        case '1':
            printf("������������Ĺؼ��֣�");
            scanf("%d", &key);
            getchar();
            taller = false;
            if (!InsertNode(T, key, taller)) printf("����ʧ�ܣ�");
            else printf("����ɹ���");
            printf("\n������ƽ����������ʾ��\n");
            DisplayTree(T, 1);
            break;
        case '2':
            printf("�����������ҵĹؼ��֣�");
            scanf("%d", &key);
            getchar();
            if (!SearchNode(T, key)) printf("û�ҵ���");
            else printf("�ҵ��ˣ�");
            printf("\n");
            break;
        case '3':
            printf("��������ɾ���Ĺؼ��֣�");
            scanf("%d", &key);
            getchar();
            lower = false;
            if (!DeleteNode(T, key, lower)) printf("ɾ��ʧ�ܣ�");
            else printf("ɾ���ɹ���");
            printf("\nɾ�����ƽ����������ʾ��\n");
            DisplayTree(T, 1);
            break;
        case '0':
            flag = false;
            printf("���˳���\n");
            break;
        }
    }
    system("pause");
    return 0;
}
