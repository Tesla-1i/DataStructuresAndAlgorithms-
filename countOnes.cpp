#include<iostream>
using namespace std;

//ͳ������n�ж�����չ����1�ĸ���
int countOnes(unsigned int n){
    int ones=0;
    while(0<n){
        //������λ����Ϊ1�����
        ones += (1&n);
        //����һλ
        n>>=1;
    }
    return ones;
}

int main(){
    int ones = countOnes(3);
    cout<<"3��1�ĸ��� "<<ones;
    return 0;
}
