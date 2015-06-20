#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <conio.h>
using namespace std;

class PriorityQueue{             //���ȶ�����
private:
    int *elements;      //����������ȶ�����Ԫ�ص�����
    int n;              //����������ȶ�����Ԫ�صĸ���
    int maxSize;        //���ȶ��е��������
public:
    PriorityQueue(int pMaxSize){
        /*���캯������ʼ��һ�����ȶ���*/
        maxSize = pMaxSize+1;
        elements = new int[maxSize];
        n = 0;
    }
    bool isEmpty(){
        /*�������ж����ȶ����Ƿ�Ϊ��*/
        return !(n); 
    }
    bool isFull(){
        /*�������ж����ȶ����Ƿ���*/
        return (n==(maxSize-1));
    }
    int searchElem(void){
        /*���������Ҳ���*/
        return elements[1];
    }
    void insertElem(int elem){
        /*�����������ȶ����в���һ��Ԫ��*/
        int i = n+1;
        if (this->isFull()) return; //������ȶ����������򷵻�
        if (this->isEmpty()) elements[1] = elem;    //������ȶ���Ϊ�գ���ô��Ԫ�ز��뵽��һ��λ��
        else{
            while((i!=1) && (elem<elements[i/2])){  //Ѱ�Ҳ���ĺ���λ��
                elements[i] = elements[i/2];
                i/=2;
            }
        }
        elements[i] = elem;
        n++;    //���ȶ�����Ԫ�ظ�����һ
    }
    int deleteElem(int index){
        /*�����������ȶ�����ɾ����index��Ԫ��*/
        if (this->isEmpty()|| index>n) return INT_MIN;
        int result = elements[index], parent = index, child = 2*parent, tmp = elements[n--];
        while (child <= n){
            if ((child<n)&&(elements[child] > elements[child+1])) child++;
            if (tmp < elements[child]) break;
            elements[parent] = elements[child];
            parent = child; child*=2;
        }
        elements[parent] = tmp;
        return result;
    }
    void displayQueue(int index, int space){
        /*��������ӡ���ȶ���*/
        if (index <= n){
            displayQueue(index*2+1, space+1);    //�ݹ��ӡ������
            for (int i=0; i<2*space;i++) printf(" ");
            printf("%d\n", elements[index]);
            displayQueue(index*2, space+1);      //�ݹ��ӡ������
        }
    }
};
int main()
{
    int max, ch = 0, elem, result;
    printf("���������ȶ���Ԫ�ص���������");
    scanf("%d", &max);
    PriorityQueue pq(max);
    while (ch!='0'){
        printf("==========���ȶ���==========\n");
        printf("���������ִ�ж�Ӧ������\n1.����һ��Ԫ��\n2.�������ȼ�����Ԫ��\n3.ɾ��ָ������ָ��λ�õ�Ԫ��\n4.��ʾ���ȶ���\n0.�˳�\n");
        ch = getch();
        printf("=====================\n");
        switch(ch){
        case '1':
            printf("��������������Ԫ�أ�");
            scanf("%d", &elem);
            pq.insertElem(elem);
            printf("����ɹ���\n");
            break;
        case '2':
            printf("���ȼ���ߵ�Ԫ���ǣ�%d\n", pq.searchElem());
            break;
        case '3':
            printf("����������ɾ����Ԫ�ر�ţ�");
            scanf("%d", &elem);
            result = pq.deleteElem(elem);
            if (result==INT_MIN) printf("ɾ��ʧ�ܣ�δ�ҵ���Ԫ�أ�\n");
            else printf("ɾ���ɹ�����ɾ����Ԫ��Ϊ��%d\n", result);
            break;
        case '4':
            printf("���ȶ���������ʾ��\n");
            pq.displayQueue(1, 0);
            break;
    }
    printf("=====================\n");
    }
    return 0;
}
