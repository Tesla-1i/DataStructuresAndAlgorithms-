#include <iostream>
#include <cstring>
#include <string>
#include <assert.h>
using namespace std;
//计算特征向量
int *Next(string P){
    cout<<"第一个\n";
    int m=P.length();   //P的长度
    //assert(m>0);
    int *N=new int[m];
    //assert(N!=0);
    N[0]=0;
    for(int i=0;i<m;i++){
        int k=N[i-1];
        while (k>0&&P[i]!=P[k])
            k=N[k-1];
        if(P[i]==P[k])
            N[i]=k+1;
        else
            N[i]=0;
    }
    return N;
}
//KMP模式匹配
int KMPStrMatching(string T,string P,int* N,int startIndex){
    cout<<"第二个\n";
    int lastIndex=T.length()-P.length();
    if((lastIndex-startIndex)<0)
        return -1;

    int i;
    int j=0;
    for ( i = startIndex; i < T.length(); ++i) {
        while (P[j]!=T[i]&&j>0)
            j=N[j-1];
        if(P[j]==T[i])
            j++;
        if (j==P.length())
            return (i-j+1);
    }
    return -1;
}

int main(){
    cout<<"输入目标串\n";
    string T;
    cin>>T;
    cout<<"输入模式串\n";
    string P;
    cin>>P;
    int *N=Next(P);
    int i=KMPStrMatching(T,P,N,1);
    cout<<"第一个匹配位置："<<i<<endl;
    return 0;
}