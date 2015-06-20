#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Tuple3{   //��Ԫ����
private:
    int row;    //����
    int column; //����
    int data;   //����
public:
    Tuple3(int pRow, int pColumn, int pData){
    /*���캯��*/
        row = pRow; column = pColumn; data = pData;
    }
    int getRow(void){
        /*��������������*/
        return row;
    }
    int getColumn(void){
        /*��������������*/
        return column;
    }
    int getData(void){
        /*��������������*/
        return data;
    }
};
class Matrix{   //������
private:
    vector<Tuple3> elems;   //��ž���Ԫ��
    int rowNum; //���������
    int columnNum;  //���������
    int totalNum;    //�������Ԫ�صĸ���
public:
    Matrix(){
        rowNum = 0;
        columnNum = 0;
        totalNum = 0;
    }
    void insertElem(int row, int column, int data){
        Tuple3 t3(row, column, data);
        this->elems.push_back(t3);
        if (row > rowNum) rowNum = row;
        if (column > columnNum) columnNum = column;
        totalNum += 1;
    }
    void setColumnNumber(int pColumnNumber){
        columnNum = pColumnNumber;
    }
    int getColumnNumber(void){
        /*���������ؾ��������*/
        return columnNum;
    }
    void setRowNumber(int pRowNumber){
        /*���������þ��������*/
        rowNum = pRowNumber;
    }
    int getRowNumber(void){
        /*���������ؾ��������*/
        return rowNum;
    }
    void setTotalNumber(int pTotalNumber){
        /*���������þ����Ԫ�ظ���*/
        totalNum = pTotalNumber;
    }
    int getTotalNumber(void){
        /*���������ؾ��������*/
        return totalNum;
    }
    void setElem(int index, int row, int col, int data){
        Tuple3 tmp(row, col, data);
        elems[index] = tmp;
    }
    vector<Tuple3> getElems(void){
        /*����������Ԫ���б�*/
        return elems;
    }
    void showMatrix(void){
        /*��������ʾ����*/
        int **array;
        array = new int*[rowNum];
        for (int i=0; i<rowNum; i++) array[i] = new int[columnNum];
        for (int i=0; i<rowNum; i++) for (int j=0; j<columnNum; j++) \
            array[i][j] = 0;
        for (int i=0; i<totalNum; i++){     //���Ƚ�Ԫ��װ��һ��������
            Tuple3 elem = elems[i];
            array[elem.getRow()-1][elem.getColumn()-1] = elem.getData();
        }
        for (int i=0; i<rowNum; i++){
            for (int j=0; j<columnNum; j++){
                printf("%d\t", array[i][j]);
            }
            printf("\n");
        }
    }
};
void Transpose(Matrix* matrixA, Matrix* matrixB){
    /*��������matrixAָ��ľ���ת�ú�����matrixBָ��ľ�����*/
    for (int i=1; i <= matrixA->getColumnNumber(); i++){
        for (int j=0; j < matrixA->getTotalNumber(); j++){
            if (matrixA->getElems()[j].getColumn() == i){
                matrixB->insertElem(matrixA->getElems()[j].getColumn(), \
                                    matrixA->getElems()[j].getRow(), \
                                    matrixA->getElems()[j].getData());
            }
        }
    }
}
void FastTranspose(Matrix* A, Matrix* B){
    /*����ת�ú���*/
    int column, i, j;
    int *number = new int[A->getColumnNumber()+1], *position = new int[A->getColumnNumber()+1];
    B->setRowNumber(A->getColumnNumber());B->setColumnNumber(A->getRowNumber());
    for (i=0; i<A->getTotalNumber(); i++) B->insertElem(0, 0, 0);
    for (column=1; column<=A->getColumnNumber(); column++) number[column] = 0;
    for (i=0;i<A->getTotalNumber();i++) number[A->getElems()[i].getColumn()]++;
    position[1] = 0;
    for (column=2;column<=A->getColumnNumber();column++)
        position[column] = position[column-1] + number[column-1];
    for (i=0; i<A->getTotalNumber(); i++){
        j = position[A->getElems()[i].getColumn()];
        B->setElem(j, A->getElems()[i].getColumn(), A->getElems()[i].getRow(), \
                   A->getElems()[i].getData());
        position[A->getElems()[i].getColumn()]++;
    }
}
int main()
{
    Matrix A, B, C;
    string inputStr;        //����û�������ַ���
    int row, column, data;  //����û����������������������
    bool contin = true;    //�����ж��Ƿ�����������Ԫ��
    do{
        printf("���������Ԫ�أ����롮0����������");
        getline(cin, inputStr); //����û��������������
        char* inputStr2 = new char[inputStr.length()+1];
        strcpy(inputStr2,inputStr.c_str());
        if (!strcmp(inputStr2, "0")) {
            printf("���������\n");
            contin  = false;
        }
        else{
            row = atoi(strtok(inputStr2, " "));     //���տո񻮷��û�������ַ���
            column = atoi(strtok(NULL, " "));
            for (int i=0;i<A.getTotalNumber();i++){
                if ((A.getElems()[i].getRow()==row)&&(A.getElems()[i].getColumn()==column)){
                    printf("�Բ��𣬾����ڸ�λ������Ԫ�أ����������룡\n");
                    continue;
                }

            }
            data = atoi(strtok(NULL, " "));
            A.insertElem(row, column, data);
        }
    }while(contin);
    printf("����������ʾ��\n");
    A.showMatrix();
    Transpose(&A, &B);
    printf("ת�ú�ľ���������ʾ��\n");
    B.showMatrix();
    FastTranspose(&A, &C);
    printf("����ת�ú�ľ���������ʾ��\n");
    C.showMatrix();
    return 0;
}
