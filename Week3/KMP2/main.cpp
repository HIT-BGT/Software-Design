#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
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
void KMP(SString S, SString T){
    //����KMP�㷨����ģʽƥ�䣬 ����ΪS�� ģʽ��ΪT
    int i = 1, j = 1;
    vector<int> results;
    while (i<=S.getLength()){
        {
            while (j<= T.getLength()){
                if (j==0 || S.getString()[i] == T.getString()[j]) {i++; j++;}
                else j = next[j];
            }
            if (j>T.getLength()) {
               results.push_back(i-T.getLength());
               j=next[j-1];
               if (i>S.getLength()) break;
               else i--;
            }

        }
    }
    if (!results.size()) printf("û����������ƥ�䵽ģʽ����");
    else{
        printf("��������ƥ�䵽ģʽ����λ���У�");
        for (int i=0;i<results.size();i++) printf("%d ", results[i]);
    }
    printf("\n");
}
int main()
{
    char str[MAX_LEN+1];
    printf("������������");
    gets(str);
    SString S(str);
    printf("������ģʽ����");
    gets(str);
    SString T(str);
    getNext(T, next);

    KMP(S, T);
    system("pause");
    return 0;
}
