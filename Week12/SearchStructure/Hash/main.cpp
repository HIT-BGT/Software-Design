#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#define ELEM_NUM 10
#define LENGTH 16
#define B 1009          //ȡ��ELEM_NUM��ӽ���������Ϊɢ�б�Ĵ�С
using namespace std;
//����Ѱַ����ϣ��Ĵ洢�ṹ����
struct open_records{    //����Ѱַ��һ����¼�Ĵ洢�ṹ�Ķ���
    char key[LENGTH+1];
};
typedef open_records OPEN_HASH[B];
//��������ϣ��Ĵ洢�ṹ����
struct celltype{        //������һ����¼�Ĵ洢�ṹ�Ķ���
    char key[LENGTH+1]; //������
    celltype *next;     //ָ����
};
typedef celltype * cellptr;
typedef cellptr LINKED_HASH[B];
char keys[ELEM_NUM][LENGTH+1];  //�ַ����ؼ�������
char emp[LENGTH+1] = "";        //���ַ����������ж��ַ����Ƿ�Ϊ��
char *rand_str(char *str,const int len);    //��������ַ����ĺ�������
unsigned int Hash(char *str);   //�ַ�����ϣ����������
void Open_Insert(char *str, OPEN_HASH F);   //����Ѱַ�����뺯��������
int Open_Search(char *str, OPEN_HASH F);    //����Ѱַ�����Һ���������
int Linked_Search(char *str, LINKED_HASH F);//���������뺯��������
void Linked_Insert(char *str, LINKED_HASH F);//���������Һ���������
int main()
{
    srand(time(NULL));           //��ʼ�������������
    OPEN_HASH OpenHashTable;     //����һ������ΪB��open_records����������Ϊ��ɢ�б�
    LINKED_HASH LinkedHashTable;
    for (int i=0;i<B;i++)        //��ɢ�б�������λ�õĹؼ��ֳ�ʼ��Ϊ���ַ���
    {
        strcpy(OpenHashTable[i].key, emp);
    }
    for (int i=0;i<ELEM_NUM;i++)
    {
        rand_str(keys[i], LENGTH);  //��������ַ���������洢��keys[i]��
        Open_Insert(keys[i], OpenHashTable);    //�Ѹոն����һ���ַ�����ӵ�����Ѱַ��ʵ�ֵ�Hash����
        Linked_Insert(keys[i], LinkedHashTable);    //���ַ�����ӵ�������ʵ�ֵ�Hash����
    }
    cout<<"���ÿ���Ѱַ��ʵ��Hash�㷨����ӡ��ÿ���ַ��������ڹ�ϣ���е�λ��"<<endl;
    cout<<"===================="<<endl;
    for (int i=0;i<ELEM_NUM;i++)
    {
        //�ڿ���Ѱַ��ʵ�ֵĹ�ϣ���в���ÿһ���ַ�������ӡ���ַ��������ڹ�ϣ���е�λ��
        cout<<keys[i]<<'\t'<<Open_Search(keys[i], OpenHashTable)<<endl;
    }
    cout<<"===================="<<endl;
    cout<<"����������ʵ��Hash�㷨����ӡ��ÿ���ַ��������ڹ�ϣ���е�λ��"<<endl;
    cout<<"===================="<<endl;
    for (int i=0;i<ELEM_NUM;i++)
    {
        //��������ʵ�ֵĹ�ϣ���в��Ҹող�����ַ�������ӡ���ַ��������ڹ�ϣ���е�λ��
        cout<<keys[i]<<'\t'<<Hash(keys[i])<<'\t'<<Linked_Search(keys[i], LinkedHashTable)<<endl;
    }
    cout<<"===================="<<endl;
}
char *rand_str(char *str,const int len)
/*������ɳ�Ϊlen���ַ����������ַ������׵�ַ*/
{
    int i;
    for(i=0;i<len;i++)
        str[i]='A'+rand()%26;
    str[i]='\0';
    return str;
}
// �ַ�����ϣ����
unsigned int Hash(char *str)
{
    unsigned int seed = 1; // ����31 131 1313 13131 131313�ȵ�
    unsigned int h = 0;
    for (;*str;str++)
    {
        h = seed * h + *str;
    }
    return (h % B);
}
void Open_Insert(char *str, OPEN_HASH F)
{
    int locate = Hash(str), first = Hash(str), rehash = 0;
    //firstΪstr��ɢ�е�ַ��locate��¼��ǰ���ڲ�ѯ�ĵ�ַ��rehashΪ����̽��Ĵ���
    while ((rehash<B) && strcmp(F[locate].key, str))           //����û���ұ��ϣ���е����е�ַʱѭ������
    {
        locate = (first+rehash)%B;
        if(!strcmp(F[locate].key, emp))     //����ҵ���һ���յ�Ͱ
            strcpy(F[locate].key, str);     //���ؼ����ַ��������Ͱ��
        else
            rehash++;                      //�������Ѱ�ҿ�Ͱ
        if (rehash>=B)
            cout<<"Hash Table is full!"<<endl;  //����ұ����еĵ�ַ��û���ֿ�Ͱ�����ϣ������
    }
}
int Open_Search(char *str, OPEN_HASH F)
/*�ڹ�ϣ���в���str�ؼ��֣����ҵ��򷵻�str���ڵĵ�ַ�����򷵻�-1*/
{
    int locate = Hash(str), first = Hash(str), rehash = 0;
    //firstΪstr��ɢ�е�ַ��locate��¼��ǰ���ڲ�ѯ�ĵ�ַ��rehashΪ����̽��Ĵ���
    while((rehash<B) && strcmp(F[locate].key, emp))
    //�����û�в�ѯ���ϣ�����е�λ�ò��һ�δ������Ͱ
    {
        if (!strcmp(F[locate].key, str))    //����ҵ�str�ؼ����򷵻ص�ǰ��ѯ�ĵ�ַ
            return locate;
        else
            rehash++;                       //�������Ѱ�ҹؼ���
        locate = (first+rehash) % B;
    }
    return -1;  //���δ�ҵ��ؼ���str�򷵻�-1
}
int Linked_Search(char *str, LINKED_HASH F)
/*�����������洢�Ĺ�ϣ���в���str�ؼ��֣�����ҵ��򷵻�str��ͬ����ӱ�
�е�λ�ã�δ�ҵ��򷵻�-1*/
{
    cellptr tmpptr = F[Hash(str)];
    int locate = 1; //locate��¼str�����Ӧͬ��ʱ��е����λ��
    while (tmpptr)
    {
        if (!strcmp(tmpptr->key, str))  //�����ͬ��ʱ����ҵ���str�ؼ���
            return locate;
        else{
            tmpptr = tmpptr->next;      //������tmpptrָ��ͬ��ʱ��е���һ��Ԫ��
            locate++;
        }
    }
    return -1;
}
void Linked_Insert(char *str, LINKED_HASH F)
/*���������洢�ṹʵ�ֵĹ�ϣ���в���һ����strΪ�ؼ��ֵļ�¼*/
{
    int bucket;
    cellptr oldheader;
    if (Linked_Search(str, F)==-1)  //����ڹ�ϣ����û�в��ҵ���strΪ�ؼ��ֵļ�¼
    {
        bucket = Hash(str);         //��str��ɢ�е�ַ��ֵ��bucket
        oldheader = F[bucket];      //oldheaderָ��ͬ��ʱ�ĵ�һ�����
        F[bucket] = new celltype;   //����һ���µĽ��
        strcpy(F[bucket]->key, str); //ʹ���½����������Źؼ���
        F[bucket]->next = oldheader;//���½���ָ����ָ��ԭ����ͷ���
    }
}
