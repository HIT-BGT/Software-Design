#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 1000

using namespace std;

struct Node{    //Huffman���ڵ�ṹ
    unsigned char letter;   //�ַ���ֵ
    int weight, order;  //�ַ���������������
    Node* parent, *lchild,*rchild;  //����㡢�����Լ��Һ��ӽ��ָ��
    Node* Front, *Back;  //ָ��ͬһ��������ǰ�����ͺ�̽ڵ�
}*root;

struct LeafNode{    //Ҷ�ӽڵ�Ľṹ
    Node* charnode; //Ҷ�ӽڵ��Ӧ���ַ��ڵ�
    LeafNode* next; //Ҷ�������е���һ���ڵ�
}*leaf, *weight;

ifstream in, tmpin;
ofstream out, tmpout;
long int all;

void Compression(void); //ѹ���ļ�����
void Decompression(void);   //��ѹ�ļ�����
void Update(struct Node*); //�޸�������Ϣ
void AddChar(unsigned char);    //��̬Huffman�������һ���ַ�
unsigned char ReadChar(void);   //���ļ��ж�ȡһ���ַ���ASCII��
void ProduceCode(Node*);    //����������Ϣ

int main()
{
    char letter;
    printf("==========Dynamic Huffman Coding==========\n");
    printf("1. Dynamic Huffman Compression\n");
    printf("1. Dynamic Huffman Decompression\n");
    printf("Please input 1 or 2 to execute corresponding operation:");
    letter = getchar();
    if (letter == '1') Compression();
    else if (letter == '2') Decompression();
    return 0;
}
void initial(void){
/*��ʼ���ӳ���*/
    root = (Node *) malloc (sizeof(Node));
    root->parent = root->lchild = root->rchild = NULL;
    root->Front = root->Back = NULL;
    root->weight = 0;
    root->letter = 0;
    root->order = 1000; //���ڵ��������Ϊ1000
    leaf = (LeafNode*) malloc(sizeof(LeafNode));
    weight = (LeafNode*) malloc(sizeof(LeafNode));
    leaf->charnode = root;
    weight->charnode = NULL;
    leaf->next = weight->next = NULL;
}
void Compression(void){
/*ѹ���ӳ���*/
    LeafNode * p;
    char tmpletter;
    bool found;
    char tmpstr[MAX];
    char oldfile[MAX], newfile[MAX];    //�����ļ�·��
    printf("==========Huffman Compression Procedure==========\n");
    printf("Please input the old file name:");
    scanf("%s", oldfile);
    printf("Please input the new file name:");
    scanf("%s", newfile);
    in.open(oldfile);
    tmpout.open("temp.txt");
    out.open(newfile);
    initial();
    all = 0;
    tmpletter = in.get();
    while (!in.eof()){
        found = false;
        all++;
        p = leaf->next;
        while (p){
            if (p->charnode->letter == tmpletter){
                found = true; break;
            }
            else p = p->next;
        }
        if (!found){ //Ҷ�������޴��ַ�
            ProduceCode(leaf->charnode);    //�������ַ��ı���
            for (int i=0; i<8; i++){
                tmpout<<((tmpletter>>(7-i)) & 0x01); //��ASCII��������ʱ����ļ�
            }
            //tmpout<<tmpletter;
            AddChar(tmpletter); //��tmpletter���뵽Huffman����
            Update(leaf->charnode->parent);     //�޸���Ӧ����������Ϣ
        }else{
            ProduceCode(p->charnode);   //��������
            Update(p->charnode);    //�޸�������Ϣ
        }
        tmpletter = in.get();
    }
    tmpout.close();
    tmpin.open("temp.txt");
    out<<all<<endl;
    tmpin.getline(tmpstr, MAX);
    while(strcmp(tmpstr, "")){
        out<<tmpstr<<endl;
        tmpin.getline(tmpstr, MAX);
    }
    in.close();
    tmpin.close();
    out.close();
    remove("temp.txt");
}
void Decompression(void){   //��ѹ�ӳ���
    char oldfile[MAX], newfile[MAX], str[MAX], bit;    //���ļ��������ļ���
    unsigned char letter;
    Node* tmp;
    printf("==========Dynamic Huffman Decompression Program==========\n");
    printf("Please input the old file name:");
    scanf("%s", oldfile);
    printf("Please input the new file name:");
    scanf("%s", newfile);
    in.open(oldfile);   //�򿪾��ļ���Ϊ������
    out.open(newfile);  //�����ļ���Ϊ�����
    initial();
    in.getline(str, MAX);
    all = atoi(str);
    letter = ReadChar();
    AddChar(letter);
    out<<letter;
    all--;
    while (all>0){  //��ѹû���
        tmp = root;
        while ((tmp->lchild) && (tmp->rchild)){
            in>>bit;
            if (bit == '0') tmp = tmp->lchild;
            else tmp = tmp->rchild;
        }
        if (tmp == leaf->charnode){ //Ϊ�սڵ�����
            letter = ReadChar();
            out<<letter;
            all--;
            AddChar(letter);
        }
        else{   //�ҵ��ý��
            letter = tmp->letter;
            out<<letter;
            all--;
        }
        Update(tmp);
    }
    in.close();
    out.close();
}
void InserWeight(Node* Tmp){
    /*����������С���ڵ���뵽��������*/
    LeafNode *p, *q;
    bool found = false;
    Node* Tmpa;
    p = weight;
    Tmp->Front = Tmp->Back = NULL;
    while (p->next){    //����������ͬ����
        if (p->next->charnode->weight == Tmp->weight){
            found = true;
            break;
        }
        else p = p->next;
    }
    if (!found){    //���û���ҵ���Ӧ����
        q = (LeafNode*) malloc(sizeof(LeafNode));
        p->next = q;
        q->next = NULL;
        q->charnode = Tmp;
    }
    else{   //����ҵ��˶�Ӧ��������������ɴ�С����
        Tmpa = p->next->charnode;
        //if (Tmpa != Tmp){
            if (Tmp->order >= Tmpa->order){
                Tmp->Back = Tmpa;
                Tmpa->Front = Tmp;
                p->next->charnode = Tmp;
                }
            else{
                while (Tmpa->Back != NULL){
                    if (Tmpa->Back->order < Tmp->order) break;
                    else Tmpa = Tmpa->Back;
                }
                Tmp->Back = Tmpa->Back;
                Tmp->Front = Tmpa;
                Tmpa->Back = Tmp;
                if (Tmp->Back != NULL) Tmp->Back->Front = Tmp;
        }
        //}
    }
}
void Update(Node* Tmp){
    /*�޸���Ӧ������*/
    Node *Tmpa, *Pointer;
    LeafNode *p, *q, *b;
    unsigned char letter;
    while (Tmp != root){    //����û���������ڵ�ʱ
        p = weight;
        if (Tmp->weight){
            p = weight;
            while (p->next->charnode->weight != Tmp->weight)
                p = p->next;
        if (Tmp->Front != NULL){
            Tmpa = Tmp;
            while(Tmp->Front) {Tmp = Tmp->Front;}
            Pointer = Tmp->lchild;  //�����������
            if (Pointer) Pointer->parent = Tmpa;
            Tmp->lchild = Tmpa->lchild;
            if (Tmp->lchild) Tmp->lchild->parent = Tmp;
            Tmpa->lchild = Pointer;
            Pointer = Tmp->rchild;
            if (Pointer) Pointer->parent = Tmpa;
            Tmp->rchild = Tmpa->rchild;
            if (Tmp->rchild) Tmp->rchild->parent = Tmp;
            Tmpa->rchild = Pointer;
            letter = Tmp->letter;
            Tmp->letter = Tmpa->letter;
            Tmpa->letter = letter;
            if ((!Tmpa->lchild)&&(!Tmpa->rchild)){
                b = leaf;
                while (b){
                    if (b->charnode == Tmp){
                        b->charnode = Tmpa;
                        break;
                    }
                    else b = b->next;
                }
            }
            if ((!Tmp->lchild)&&(!Tmp->rchild)){
                b = leaf;
                while (b){
                    if (b->charnode == Tmpa){
                        b->charnode = Tmp;
                        break;
                    }
                    else b = b->next;
                }
            }
        }
        p->next->charnode = Tmp->Back;  //����������ȡ�¸ýڵ�
        if (!Tmp->Back){
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else Tmp->Back->Front = NULL;
        }
        Tmp->weight++;  //����+1
        Tmp->Back = Tmp->Front = NULL;
        InserWeight(Tmp);
        Tmp = Tmp->parent;
    }
}
void AddChar(unsigned char letter){
        /*��Huffman�������һ���*/
        Node *Tmpa, *Tmpb, *Tmpc;
        LeafNode* q;
        Tmpa = leaf->charnode;
        Tmpb = (Node *) malloc(sizeof(Node));
        Tmpc = (Node *) malloc(sizeof(Node));
        Tmpb->parent = Tmpc->parent = Tmpa;
        Tmpb->lchild = Tmpc->lchild = Tmpb->rchild = Tmpc->rchild = NULL;
        Tmpb->Front = Tmpc->Front = NULL;
        Tmpb->Back = Tmpc->Back = NULL;
        Tmpb->letter = 0; Tmpc->letter = letter;
        Tmpb->weight = 0; Tmpc->weight = 1;
        Tmpc->order = Tmpa->order-1;
        Tmpb->order = Tmpa->order-2;
        Tmpa->lchild = Tmpb; Tmpa->rchild = Tmpc;
        q = (LeafNode*) malloc(sizeof(LeafNode));
        q->charnode = Tmpc;
        leaf->charnode = Tmpb;
        q->next = leaf->next;
        leaf->next = q;
        InserWeight(Tmpc);
}
void ProduceCode(Node* Pointer){
/*��������*/
    char code[50];
    int count = 0, i;
    if (Pointer!=root){ //��Ҷ�ڵ㵽���ڵ����
        while (Pointer != root){
            if (Pointer == Pointer->parent->lchild) code[count] = '0';
            else code[count] = '1';
            count++;
            Pointer = Pointer->parent;
        }
        for (i=count-1; i>=0; i--) tmpout<<code[i];
    }
}
unsigned char ReadChar(void){
/*���ļ��ж�ȡһ���ַ��Ķ�����ASCII�벢����ת��Ϊ�ַ�*/
    unsigned char letter = 0x00, bit;
    for (int i=0; i<8; i++){
        in>>bit;
        bit -= 48;
        letter = (letter | (bit<<(7-i)));
    }
    return letter;
}
