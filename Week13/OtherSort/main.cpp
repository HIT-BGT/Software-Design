#include <cstdio>
#include <cstring>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

typedef struct buckect{
    vector<int> nodes;
    int count;
}buckect;
void CountingSort(int *A, int *B, int k, int n);   //������A���м������򣬽������B������
int GetDigit(int data, int k);  //��ȡdata�ĵ�kλ��
void RadixSort(int *A, int *C, int d, int n);  //������A���л������� �����������C��
void BucketSort(int *A, int n); //������A����Ͱ����
int main(){
    clock_t start, finish;
    int len, max_num = 0, d =1; //���ڴ洢���鳤��
    printf("���������鳤�ȣ�");
    scanf("%d",&len);
    int* A = new int[len], *B = new int[len+1], *C = new int[len];
    for (int i=0; i<len; i++){
        printf("�����������е�%d��Ԫ�ص�ֵ��", i+1);
        scanf("%d", A+i);
        if (A[i] > max_num) max_num = A[i];
        int leftnum = A[i], another_d = 0;
        while (leftnum != 0){
            another_d++;
            leftnum/=10;
        }
        if (another_d > d) d = another_d;
    }
    start = clock();
    CountingSort(A, B, max_num, len); //��A[0, 1, ..., len-1]���п�������
    finish = clock();
    printf("����ִ��ʱ���� %d ms\n", (int)((double)(finish - start) / CLOCKS_PER_SEC * 1000));
    printf("��������������������ʾ��\n");
    for (int i=1; i<len+1; i++){
        printf("%d ", B[i]);
    }
    printf("\n");
    printf("��������������������ʾ��\n");
    start = clock();
    RadixSort(A, C, d, len);
    finish = clock();
    printf("����ִ��ʱ���� %d ms\n", (int)((double)(finish - start) / CLOCKS_PER_SEC * 1000));
    printf("��������������������ʾ��\n");
    for (int i=0; i<len; i++){
        printf("%d ", C[i]);
    }
    printf("\n");
    start = clock();
    BucketSort(A, len);
    finish = clock();
    printf("Ͱִ��ʱ���� %d ms\n", (int)((double)(finish - start) / CLOCKS_PER_SEC * 1000));
    printf("Ͱ����������������ʾ��\n");
    for (int i=0; i<len; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
void CountingSort(int *A, int *B, int k, int n){
    /*������A���м������򣬽������B������*/
    int *C = new int[k+1], i;
    for (i=0; i<=k; i++) C[i] = 0;
    for (i=0; i<n; i++) C[A[i]]++;
    for (i=1; i<=k; i++) C[i]+=C[i-1];
    for (i=n-1; i>=0; i--){
        B[C[A[i]]] = A[i];
        C[A[i]]--;
    }
}
int GetDigit(int data, int k){
    /*��ȡdata�ĵ�kλ��*/
    int a[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    return (data / a[k-1]) % 10;
}

void RadixSort(int *A, int *C, int d, int n){
    /*������A���л������� �����������C��*/
    const int radix = 10;
    int *count = new int[radix], i, j, k;
    for (i=0; i<n; i++) C[i] = A[i];
    int *bucket = new int[n];
    for (k=1; k<=d; k++){//��λ����
        for (i=0; i<radix; i++) count[i] = 0;   //ÿ��Ͱ�ﶼû������
        for (i=0; i<n; i++) count[GetDigit(C[i], k)]++; //ͳ�Ƶ�kλ��0-9���Գ��ֵĴ���
        for (i=1; i<radix; i++) count[i] += count[i-1]; //count[i]�洢��kλ������Ϊi��Ԫ����Ͱ�е��ұ߽�
        for (i=n-1; i>=0; i--){
            j = GetDigit(C[i], k);
            bucket[--count[j]] = C[i];
        }
        for (i=0; i<n; i++) C[i] = bucket[i];
    }
    free(count);
    free(bucket);
}
void InsertSort(vector<int> &A, int low, int high){
    /*��A[low, low+1, ... high]���в�������*/
    int i, j, tmp;
    for (i=low+1; i<=high; i++){
        if (A[i-1] > A[i]){
            tmp = A[i];
            for (j=i; (j>0) && (tmp < A[j-1]); j--)
                A[j] = A[j-1];
        A[j] = tmp;
        }
    }
}
void BucketSort(int *A, int n){
    /*������A����Ͱ����*/
    int min_, max_, num, pos, i, j, k;
    buckect *ArrBuckets;
    min_ = max_ = A[0]; //�������е���СԪ�غ����Ԫ��
    for (i=1; i<n; i++){
        if (A[i] < min_) min_ = A[i];
        if (A[i] > max_) max_ = A[i];
    }
    num = (max_ - min_) / 10 + 1;
    ArrBuckets = new buckect[num];
    for (i=0; i<num; i++){
        ArrBuckets[i].nodes.clear();
        ArrBuckets[i].count = 0;
    }
    for (i=0; i<n; i++){    //��Ԫ�ط����ӦͰ��
        k = (A[i] - min_) / 10; //��ȡ��Ӧ��Ͱ�ı��
        ArrBuckets[k].nodes.push_back(A[i]);
        ArrBuckets[k].count++;
    }
    pos = 0;
    for (i=0; i<num; i++){
        int *nodes = new int[ArrBuckets[i].count];
        for (j=0; j<ArrBuckets[i].count;j++) nodes[j] = ArrBuckets[i].nodes[j];
        sort(nodes, nodes+ArrBuckets[i].count);
        for (j=0; j<ArrBuckets[i].count; j++){
            A[pos++] = nodes[j];
        }
    }
}
