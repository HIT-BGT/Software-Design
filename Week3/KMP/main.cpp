#include <iostream>
#include <string.h>
#include <stdio.h>
#define MAX_LEN 100
using namespace std;
int next[MAX_LEN+1];
class SString{
    public:
        SString(char pStr[]){
        //���Ĺ��췽��
            for (int i=0; i<strlen(pStr); i++) str[i+1] = pStr[i];
            length = strlen(pStr);
        }
        char* getString(void){
        //��ô�
            return str;
        }
        int getLength(void){
        //��ô��ĳ���
            return length;
        } 
    private:
        int length;             //�洢������
        char str[MAX_LEN+1];     //�洢��
};
void getNext(SString str, int next[]){
    int i=1, j = 0;
    next[i] = 0;
    while (i<str.getLength()){  //����δ������ĩβʱ
        if (j==0 || str.getString()[i] == str.getString()[j]) {i++; j++; next[i]=j;}
        else j=next[j];
    }
}
int KMP(SString S, SString T){
    //����KMP�㷨����ģʽƥ�䣬 ����ΪS�� ģʽ��ΪT
    int i = 1, j = 1;
    while ((i<=S.getLength())&& (j<= T.getLength())){
        if (j==0 || S.getString()[i] == T.getString()[j]) {i++; j++;}
        else j = next[j];
    }
    if (j>T.getLength()) return i-T.getLength();
    else return 0;
}
int main()
{
    char str[MAX_LEN+1];
    int result;
    printf("������������");
    gets(str);
    SString S(str);
    printf("������ģʽ����");
    gets(str);
    SString T(str);
    result = KMP(S, T);
    if (!result) printf("ģʽδ���������гɹ�ƥ�䣡");
    else printf("ƥ��ɹ���ƥ��λ��Ϊ��%d", result);
    return 0;
}
