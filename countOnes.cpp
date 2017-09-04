#include<iostream>
using namespace std;

//统计整数n中二进制展开中1的个数
int countOnes(unsigned int n){
    int ones=0;
    while(0<n){
        //检查最低位，若为1则计数
        ones += (1&n);
        //右移一位
        n>>=1;
    }
    return ones;
}

int main(){
    int ones = countOnes(3);
    cout<<"3中1的个数 "<<ones;
    return 0;
}
