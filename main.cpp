#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

class Node{ 
    public:
        Node(int pData){
        //���췽��1�����������  �ڵ�����
            data = pData;
            downNode = NULL;
            nextNode = NULL;
        }
        Node(int pData, Node* pDownNode, Node* pNextNode){
        //���췽��2������������ڵ����ݣ�ָ��ýڵ�֮�½ڵ��ָ�룬ָ��ýڵ�֮��ڵ��ָ��
            data = pData;
            downNode = pDownNode;
            nextNode = pNextNode;
        }
        void setData(int pData){
        //���ýڵ�洢������
            data = pData;
        }
        int getData(void){
        //��ý��洢����
            return data;
        }
        void setPos(int pPos){
        //���ýڵ��������е����λ��
            pos = pPos;
        }
        int getPos(void){
        //��ýڵ��������е����λ��
            return pos;
        }
        void setDownNode(Node* pDownNode){
        //���õ�ǰ�ڵ�����ڽڵ�
            downNode = pDownNode;
        }
        Node* getDownNode(void){
        //��õ�ǰ�ڵ�����ڽڵ�
            return downNode;
        }
        void setNextNode(Node* pNextNode){
        //���õ�ǰ�ڵ�ĺ��ڽڵ�
            nextNode = pNextNode;
        }
        Node* getNextNode(void){
        ////��õ�ǰ�ڵ�ĺ��ڽڵ�
            return nextNode;
        }
    private:
        int data;                    //�洢�ڵ������
        int pos;                    //�洢�ڵ�����λ��
        Node* downNode;            //ָ��ýڵ�֮�µĽڵ��ָ��
        Node* nextNode;               //ָ��ýڵ�֮��ڵ��ָ��
};

class SkipList{
    //������
    public:
        SkipList(){ //����Ĺ��췽��
            top = new Node(INT_MIN);    //���ڵ�洢������Ϊ��С������
            tail = new Node(INT_MAX);   //β���洢������Ϊ��������
            top->setNextNode(tail);     //�����ڵ��β�����������
            height = 1;
            width = 2;
        }
        int randomValue(){              //���ա���Ӳ�ҡ���������һ�������
            int result = 1;
            srand(time(NULL));
            while ((rand() * 1.0 / RAND_MAX) > 0.5) result++;
            return result;
        }
        void updatePos(){               //���µײ�ڵ��λ�ñ��
            Node* tmp = top;
            while (tmp->getDownNode()) tmp = tmp->getDownNode();
            for (int i=0;i<width;i++) {tmp->setPos(i); tmp = tmp->getNextNode(); }
        }
        void insertNode(int data){
            //�������в���һ������Ϊdata�Ľ��
            int floor = randomValue();
            if (floor > height){    //���Ҫ����ڵ���ռ�߶ȴ�������߶�ʱ���Ƚ�����β�ڵ㲹����Ӧ�߶�
                for (int i = 0; i < floor - height; i++){
                    Node* newTop = new Node(INT_MIN);
                    Node* newTail = new Node(INT_MAX);
                    newTop->setDownNode(top);
                    newTail->setDownNode(tail);
                    newTop->setNextNode(newTail);
                    top = newTop;
                    tail = newTail;
                    height++;
                }
            }
            Node* preserveTop = top;
            for (int i=0;i < height - floor;i++) top = top->getDownNode();  //��top�³���ָ���߶�
            Node* above = NULL;     //�����洢�ڵ�����ڽڵ㣬�Ա�����
            while(top){
                Node* current = top->getNextNode();
                Node* previous = top;
                while (!((data >= previous->getData()) && (data <= current->getData())))
                    {previous = current; current = current->getNextNode();}
                Node* my = new Node(data);
                previous->setNextNode(my);
                my->setNextNode(current);
                if (above)  above->setDownNode(my);
                above = my;
                top = top->getDownNode();
            }
            top = preserveTop;
            width++;
            this->updatePos();  //���ú��������µײ�ڵ��λ�ñ��
    }
    int searchNode(int data){
        //�������в�������Ϊdata�Ľڵ�
        Node* tmp = top;
        while (1){
            while ( tmp->getNextNode()->getData() < data)  tmp = tmp->getNextNode();
            if (!(tmp->getDownNode())){     //�ж��Ƿ񵽴�ײ�
                if ( tmp->getNextNode()->getData() == data)  return (tmp->getNextNode()->getPos()+1);
                else return 0;
            }
            tmp = tmp->getDownNode();
        }
    }
    bool deleteNode(int data){
        //��������ɾ������Ϊdata�Ľڵ㣬���صĲ���ֵ�����Ƿ�ɾ���ɹ�
        if (this->searchNode(data)){    //����ȷ�������д��ڴ˽ڵ�
            Node* lPre = top;
            while(lPre){
                Node* pre = lPre, * tmp = lPre->getNextNode();
                while ((tmp->getNextNode()) && (tmp->getNextNode()->getData() <= data)) {
                    pre = tmp;
                    tmp = tmp->getNextNode();
                }
                if (tmp->getData() == data){
                    pre->setNextNode(tmp->getNextNode());
                    delete tmp;
            }
            lPre = lPre->getDownNode();
        }
        width--;
        return true;
        }
        return false;
    }
    void showList(){
        //��ӡ����
        int *datas = new int[width], *counts = new int[width];
        int **graph;    //����һ��width*height�����飬���ڴ洢�������Ϣ
        graph = new int*[width];
        for (int i=0;i<width;i++) graph[i] = new int[height];
        for (int i=0;i<width;i++) for (int j=0;j<height;j++) graph[i][j] = 0;
        Node* tmp = top;
        while (tmp->getDownNode()) tmp = tmp->getDownNode();
        for (int i=0;i<width;i++) {datas[i] = tmp->getData();tmp = tmp->getNextNode(); }
        for(int i=0;i<width;i++) counts[i]=0;
        updatePos();
        tmp = top;
        while(tmp){
            Node* tmp2 = tmp;
            while (tmp2){
                Node* tmp3 = tmp2;
                while (tmp3->getDownNode()) tmp3 = tmp3->getDownNode();
                counts[tmp3->getPos()]++;
                tmp2 = tmp2->getNextNode();
            }
            tmp = tmp->getDownNode();
        }
        for (int i=0;i<width;i++){
            for (int j=0;j<counts[i];j++){
                graph[i][j] = datas[i];
            }
        }
        for (int i = height-1;i>=0;i--){
            for (int j=0;j<width;j++){
                if (graph[j][i]) printf("%d\t", graph[j][i]);
                else printf(" \t");
            }
            printf("\n");
        }
    }
    private:
        Node *tail;     //ָ��β����ָ��
        Node *top;      //ָ�򶥽ڵ��ָ��
        int height;     //����ĸ߶�
        int width;      //����Ŀ��
};

int main()
{
    SkipList sl;
    int ch = 0;
    int data;
    while (ch!='0'){
        printf("==========����==========\n");
        printf("���������ִ�ж�Ӧ������\n1.����һ���ڵ�\n2.����ָ������\n3.ɾ��ָ���ڵ�\n4.��ʾ����\n0.�˳�\n");
        ch = getch();
        printf("=====================\n");
        switch(ch){
            case '1':
                printf("�����������������ݣ�");
                scanf("%d", &data);
                sl.insertNode(data);
                printf("����ɹ���\n");
                break;
            case '2':
                printf("������������ҵ����ݣ�");
                scanf("%d", &data);
                if (sl.searchNode(data)) printf("�������ҵ������������е�λ���ǣ�%d\n", sl.searchNode(data));
                else printf("������δ�ҵ�����Ҫ���ҵ����ݣ�\n");
                break;
            case '3':
                printf("����������ɾ�������ݣ�");
                scanf("%d", &data);
                if (sl.deleteNode(data)) printf("ɾ���ɹ���\n");
                else printf("ɾ��ʧ�ܣ�δ�ҵ��ýڵ㣡\n");
                break;
        case '4':
                printf("����������ʾ��\n");
                sl.showList();
                break;
        }
        printf("=====================\n");
    }
    return 0;
}
