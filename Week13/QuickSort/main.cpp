/**
��ʵ����3��ѡ����Ԫ�ķ�����
1. ѡ���±�����Ԫ����Ϊ��Ԫ
2. ���ѡ��һ��Ԫ����Ϊ��Ԫ
3. ѡ������Ԫ�أ��м�Ԫ���Լ����һ��Ԫ�ص���λ����Ϊ��Ԫ
��������3���Ż���
1. ���鳤��С��10ʱʹ�ò�������
2. ÿ������ʱ����ͬ��Ԫ�ؾۼ�����Ԫ��Χ
3. ���ٵݹ����
**/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

void InsertSort(long long int *A, int low, int high);  //��A[low, low+1, ... high]���в�������
void QuickSort(long long int *A, int low, int high); //������������ ��A[low, low+1, ... high]��������
void QuickSort2(long long int *A, int low, int high); //�Ż�����ź������ۼ���ͬԪ��
int Partition(long long int *A, int low, int high); //���ֺ�������A[low, low+1, ... high]���л��֣���A[high]��Ϊ��Ԫ
long long int FindPivot_High(long long int *A, int low, int high);  //���������±�����Ԫ����Ϊ��Ԫ
long long int FindPivot_Random(long long int *A, int low, int high);   //�����������ѡȡһ��Ԫ����Ϊ��Ԫ
long long int FindPivot_ThreeMid(long long int *A, int low, int high);  //ѡȡ�����������м��Լ����ҵ�����Ԫ�ص���λ����Ϊ��Ԫ
int main()
{
    int len; //���ڴ洢���鳤��
    printf("���������鳤�ȣ�");
    scanf("%d",&len);
    long long int* A = new long long  int[len];
    for (int i=0; i<len; i++){
        printf("�����������е�%d��Ԫ�ص�ֵ��", i+1);
        scanf("%lld", A+i);
    }
    clock_t start, finish;
    start = clock();
    QuickSort2(A, 0, len-1); //��A[0, 1, ..., len-1]���п�������
    finish = clock();
    printf("ִ��ʱ���� %d ms", (int)((double)(finish - start) / CLOCKS_PER_SEC * 1000));
    printf("����������������ʾ��\n");
    for (int i=0; i<len; i++){
        printf("%lld ", A[i]);
    }
    printf("\n");
    return 0;
}
void InsertSort(long long int *A, int low, int high){
    /*��A[low, low+1, ... high]���в�������*/
    int i, j;
    long long int tmp;
    for (i=low+1; i<=high; i++){
        if (A[i-1] > A[i]){
            tmp = A[i];
            for (j=i; (j>0) && (tmp < A[j-1]); j--)
                A[j] = A[j-1];
        A[j] = tmp;
        }
    }
}
void QuickSort2(long long int *A, int low, int high){
    /*�Ż�����ź������ۼ���ͬԪ��*/
    if (low < high){
        if (high-low+1 < 10)
            InsertSort(A, low, high);   //��Ԫ�ظ���С��10ʱ��ʹ�ò�������
        else{
            int first = low, left = low,
                last = high, right = high,
                leftlen = 0, rightlen = 0;
            long long int pivot = FindPivot_ThreeMid(A, low, high);   //����ȡ�з�����Ԫ
            while (low < high){
                while (low < high && A[low] <= pivot){
                    if (A[low] == pivot){   //������ͬԪ��
                        swap(A[left], A[low]);
                        left++; leftlen++;
                    }
                    low++;
                }
                A[high] = A[low];
                while (low < high && A[high] >= pivot){
                    if (A[high] == pivot){  //������ͬԪ��
                        swap(A[right], A[high]);
                        right--; rightlen++;
                    }
                    high--;
                }
                A[low] = A[high];
            }
            A[high] = pivot;
            //������Ԫ��ͬ��Ԫ���Ƶ���Ԫ��Χ
            int i = low-1, j = first;
            while (j<left && A[i]!=pivot){
                swap(A[j], A[i]);
                j++; i--;
            }
            i = low+1, j = last;
            while (j>right && A[i]!=pivot){
                swap(A[i], A[j]);
                j--; i++;
            }
            QuickSort2(A, first, low-1-leftlen);
            QuickSort2(A, low+1+rightlen, last);
        }
    }

}
void QuickSort(long long int *A, int low, int high){
    /*������������ ��A[low, low+1, ... high]��������*/
    if (low < high){
//        if (high-low+1 < 10)
//            InsertSort(A, low, high);   //��Ԫ�ظ���С��10ʱ��ʹ�ò�������
//        else{ //��������������һ������Ԫ�أ���ô��Ҫ����
//            while (low < high){
//                int mid = Partition(A, low, high);
//                QuickSort(A, low, mid-1);   //�ݹ�ض��󲿷�ִ�п�������
//                low = mid + 1;
//            }
//        }
//        if (high-low+1 < 10)
//            InsertSort(A, low, high);   //��Ԫ�ظ���С��10ʱ��ʹ�ò�������
//        else{
            int mid = Partition(A, low, high);
            QuickSort(A, low, mid-1);
            QuickSort(A, mid+1, high);
        }
//    }
}
int Partition(long long int *A, int low, int high){
    /*���ֺ�������A[low, low+1, ... high]���л��֣���A[high]��Ϊ��Ԫ*/
    long long int pivot =
    //FindPivot_High(A, low, high);    //�ҵ���Ԫ
    //FindPivot_Random(A, low, high);
    FindPivot_ThreeMid(A, low, high);
    int i = low-1;
    for (int j=low; j<high; j++){
        if (A[j] <= pivot){
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[high]);
    return i+1;
}
long long int FindPivot_High(long long int *A, int low, int high){
    /*���������±�����Ԫ����Ϊ��Ԫ*/
    return A[high];
}
long long int FindPivot_Random(long long int *A, int low, int high){
    /*�����������ѡȡһ��Ԫ����Ϊ��Ԫ*/
    srand((unsigned)time(NULL));    //�������������
    int pos = rand()%(high-low+1) + low;
    swap(A[pos], A[high]);
    return A[high];
}
long long int FindPivot_ThreeMid(long long int *A, int low, int high){
    /*ѡȡ�����������м��Լ����ҵ�����Ԫ�ص���λ����Ϊ��Ԫ*/
    int mid = (low + high) / 2;
    if (A[low] > A[mid]) swap(A[low], A[mid]); //A[low] <= A[mid]
    if (A[low] > A[high]) swap(A[low], A[high]); //A[low] <= A[high]
    if (A[high] > A[mid]) swap(A[high], A[mid]); //A[low] <= A[high] <= A[mid]
    return A[high];
}
