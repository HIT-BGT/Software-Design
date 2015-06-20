#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

enum Color{ //��ɫö����
    RED, BLACK
};

typedef struct RBNode{
    Color color; //�����ɫ
    int key;    //�����������
    struct RBNode* lchild;    //ָ�����ӵ�ָ��
    struct RBNode* rchild;    //ָ���Һ��ӵ�ָ��
    struct RBNode* parent;    //ָ�򸸽ڵ��ָ��
}RBNode, *RBTree;

RBTree root = NULL; //������ĸ��ڵ�

void L_Rotate(RBTree &root, RBTree &x){
    /*��������*/
    RBTree y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild) y->lchild->parent = x;
    y->parent = x->parent;  //����y�ĸ��ڵ�
    if (!x->parent) root = y;   //�����תǰx�Ǹ��ڵ�
    else{
        if (x == x->parent->lchild) x->parent->lchild = y;
        else x->parent->rchild = y;
    }
    y->lchild = x;  //��x��Ϊy������
    x->parent = y;  //����x�ĸ��ڵ�
}
void R_Rotate(RBTree &root, RBTree &y){
    /*��������*/
    RBTree x = y->lchild;
    y->lchild = x->rchild;
    if (x->rchild) x->rchild->parent = y;
    x->parent = y->parent;  //����x�ĸ��ڵ�
    if (!y->parent)  root = x;//�����תǰy�Ǹ��ڵ�
    else {
        if (y == y->parent->lchild) y->parent->lchild = x;
        else y->parent->rchild = x;
    }
    x->rchild = y;  //����yΪx���Һ���
    y->parent = x;  //����y�ĸ��ڵ�
}
void InsertFix(RBTree &root, RBTree &node){
    /*�������в���һ���ڵ������޸���ʹ��������������������*/
    RBTree parent, gparent; //��ǰ�ڵ�ĸ��ڵ���游�ڵ�
    while ((parent=node->parent) && parent->color==RED){    //���ڵ�Ϊ��ɫ
        gparent = parent->parent;   //�游�ڵ�
        if (parent == gparent->lchild){ //������׽ڵ����游�ڵ�������
            RBTree uncle = gparent->rchild; //������
            if (uncle && uncle->color == RED){   //Case1: ����������Ҳ�Ǻ�ɫ
                parent->color = BLACK;  //�����ڵ���Ϊ��ɫ
                uncle->color = BLACK;   //����������Ϊ��ɫ
                gparent->color = RED;   //���游�ڵ���Ϊ��ɫ
                node = gparent;         //����ǰ�ڵ�����Ϊ�游�ڵ�
                continue;
            }
            if (node == parent->rchild){    //Case2: ����ڵ��Ǻ�ɫ����ǰ�ڵ��Ǹ��ڵ���Һ���
                RBTree tmp = parent;
                L_Rotate(root, parent); //�Ը��ڵ�Ϊ֧������
                parent = node;
                node = tmp;             //�Ը��ڵ���Ϊ��ǰ�ڵ�
            }
            //�������Ǻ�ɫ���ҵ�ǰ�ڵ�Ϊ���ڵ������
            parent->color = BLACK;  //�����ڵ���Ϊ��ɫ
            gparent->color = RED;   //���游�ڵ���Ϊ��ɫ
            R_Rotate(root, gparent);    //���游�ڵ�Ϊ֧������
        }
        else{   //������׽ڵ����游�ڵ���Ҷ���
            RBTree uncle = gparent->lchild; //������
            if (uncle && uncle->color == RED){  //Case1: ����������Ҳ�Ǻ�ɫ
                parent->color = BLACK;
                uncle->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }
            if (node == parent->lchild){
                RBTree tmp = parent;
                R_Rotate(root, parent);
                parent = tmp;
                node = tmp;
            }
            parent->color = BLACK;
            gparent->color = RED;
            L_Rotate(root, gparent);
        }
    }
    root->color = BLACK;    //�����ڵ���Ϊ��ɫ
}
bool InsertNode(RBTree &root, RBTree &node){
    /*�������в���һ���ڵ�*/
    RBTree y = NULL, x = root;
    while (x){  //ֱ��xΪ��
        y = x;
        if (node->key == x->key) return false;
        else if (node->key < x->key) x = x->lchild;
        else x = x->rchild;
    }
    node->parent = y;   //����node�ĸ��ڵ�
    if (!y) root = node; //������ǿ���
    else if (node->key < y->key) y->lchild = node;
    else y->rchild = node;
    node->color = RED;  //������Ľ����Ϊ��ɫ
    InsertFix(root, node);
    return true;
}
RBTree SearchNode(RBTree &root, int key){
    //�ں�����в��ҹؼ���Ϊkey�Ľ��
    if (!root) return NULL; //����Ϊ��
    if (key == root->key) return root;
    if (key < root->key) return (SearchNode(root->lchild, key));    //�ݹ����������
    else return (SearchNode(root->rchild, key));    //�ݹ�ز���������
}
void DeleteFix(RBTree &root, RBTree  &node, RBTree &parent){
    /*����ɾ���ڵ���޸������ʹ���������5������*/
    while ((!node || node->color == BLACK) && node!=root){
        //����ǰ�ڵ�Ϊ��ɫ���Ҳ��Ǹ��ڵ�ʱ
        if (node == parent->lchild){    //�����ǰ�ڵ�������
            RBTree brother = parent->rchild;
            if (brother->color == RED){ //case 1:�ֵܽڵ��Ǻ�ɫ
                brother->color = BLACK; //�ֵܽڵ�Ⱦ��
                parent->color = RED;    //���ڵ�Ⱦ��
                L_Rotate(root, parent); //�Ը��ڵ�Ϊ֧������
                brother = parent->rchild;   //�����ֵܽڵ�
            }
            if ((!brother->lchild || brother->lchild->color==BLACK) &&
                (!brother->rchild || brother->rchild->color==BLACK))
            {//case 2:�ֵܽڵ��Ǻ�ɫ�����ֵܽڵ�˫�Ӿ���
                brother->color = RED;   //�ֵܽڵ�Ⱦ��
                node = parent;  //��ǰ�ڵ���Ϊ���ڵ�
                parent = parent->parent;    //���¸��ڵ�
            }
            else{
                if (!brother->rchild || brother->rchild->color==BLACK){
                    //case 3:�ֵܽڵ��Ǻ�ɫ�����������Ӻ죬�Һ��Ӻ�
                    brother->lchild->color = BLACK; //�ֵܽڵ�����Ⱦ��
                    brother->color = RED;   //�ֵܽڵ�Ⱦ��
                    R_Rotate(root, brother);    //���ֵܽڵ�Ϊ֧������
                    brother = parent->rchild;   //�����ֵܽڵ�
                }
                //case 4: �ֵܽ��ڣ������Һ��Ӻ�
                brother->color = parent->color; //�����ڵ���ɫ�����ֵܽڵ�
                parent->color = BLACK;  //���ڵ�Ⱦ��
                brother->rchild->color = BLACK; //�ֵܽڵ��Һ���Ⱦ��
                L_Rotate(root, parent); //�Ը��ڵ�Ϊ֧������
                node = root;    //����ǰ�ڵ���Ϊ���ڵ�
                break;  //����ѭ��??????
            }
        }
        else {  //��ǰ�ڵ����Һ���
            RBTree brother = parent->lchild; //�ֵܽ��
            if (brother->color == RED){
                //case 1:�ֵܽ��Ϊ��ɫ
                brother->color = BLACK;
                parent->color = RED;
                R_Rotate(root, parent);
                brother = parent->lchild;
            }
            if ((!brother->lchild || brother->lchild->color==BLACK) &&
                (!brother->rchild || brother->rchild->color==BLACK)){
                    brother->color = RED;
                    node = parent;
                    parent = parent->parent;
                }
            else{
                if (!brother->lchild || brother->lchild->color==BLACK){
                    brother->rchild->color = BLACK;
                    brother->color = RED;
                    L_Rotate(root, brother);
                    brother = parent->lchild;
                }
                brother->color = parent->color;
                parent->color = BLACK;
                brother->lchild->color = BLACK;
                R_Rotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (!node) node->color = BLACK;
}

void DeleteNode(RBTree &root, RBTree &node){
    /*�Ӻ������ɾ��node���*/
    RBTree child, parent;
    Color color;
    if ((node->lchild) && (node->rchild)){  //���Һ��Ӷ���Ϊ��
        RBTree rp = node;
        rp = rp->rchild;    //��ȡȡ���ڵ�
        while (rp->lchild) rp = rp->lchild;
        if (!node->parent) //���node�Ǹ��ڵ�
            root = rp;
        else{
            if (node == node->parent->lchild)
                node->parent->lchild = rp;
            else node->parent->rchild = rp;
        }
        child = rp->rchild; //ȡ���ڵ���Һ���
        parent = rp->parent; //ȡ���ڵ�ĸ��ڵ�
        color = rp->color;  //ȡ���ڵ����ɫ
        if (parent == node){
            parent = rp;
        }
        else{
            if (child){//��������Ϊ��
                child->parent = parent;
            }
            parent->lchild = child;
            rp->rchild = node->rchild;
            rp->rchild->parent = rp;
        }
        rp->parent = node->parent;
        rp->color = node->color;
        rp->lchild = node->lchild;
        rp->lchild->parent = rp;
        if (color == BLACK) DeleteFix(root, child, parent);
        free(node);
        return;
    }
    if (node->lchild){  //���node����������Ϊ��
        child = node->lchild;
    }
    else
        child = node->rchild;
    parent = node->parent;
    color = node->color;    //���������ɾ������ɫ
    if (child) child->parent = parent;
    if (!parent){   //node����Ǹ��ڵ�
        root = child;
    }else{
        if (node == parent->lchild) parent->lchild = child;
        else parent->rchild = child;
    }
    if (color == BLACK) DeleteFix(root, child, parent);
    free(node);
}
void DisplayTree(RBTree &T, int space_num){
    //����ӡƽ����
    if (T){
        if (T->rchild) DisplayTree(T->rchild, space_num+1);
        for (int i=0; i<2*space_num; i++) printf(" ");
        if (T->color == RED) printf("(R)");
        else printf("(B)");
        printf("%d\n", T->key);
        if (T->lchild) DisplayTree(T->lchild, space_num+1);
    }
}

int main()
{
    char op;
    int key;
    bool flag = true;
    RBTree node;
    while (flag){
        printf("===============�����===============\n\
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
            node = (RBTree) malloc (sizeof(RBNode));
            node->key = key;
            node->lchild = node->rchild = NULL;
            if (!InsertNode(root, node)) printf("����ʧ�ܣ�");
            else printf("����ɹ���");
            printf("\n�����ĺ����������ʾ��\n");
            DisplayTree(root, 1);
            break;
        case '2':
            printf("�����������ҵĹؼ��֣�");
            scanf("%d", &key);
            getchar();
            if (!SearchNode(root, key)) printf("û�ҵ���");
            else printf("�ҵ��ˣ�");
            printf("\n");
            break;
        case '3':
            printf("��������ɾ���Ĺؼ��֣�");
            scanf("%d", &key);
            getchar();
            node = SearchNode(root, key);
            if (!node) printf("ɾ��ʧ�ܣ�\n");
            else{
                printf("ɾ���ɹ���\n");
                DeleteNode(root, node);
                DisplayTree(root, 1);
            }
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
