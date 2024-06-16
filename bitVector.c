#include<stdio.h>
#include<stdlib.h>
int mxa(int *a,int n){
    int output=0;
    for(int i=0;i<n;i++){
        if(a[i]>output)output=a[i];
    }
    return output;
}

void calCnt(int* a,int n){
    int k=2;
    int mx=mxa(a,n);
    int *bv = malloc(sizeof(int)*mx+1);
    int i=0;
    for(i=0;i<mx;i++){
        bv[i]=0;
    }
    for(i=0;i<n;i++){
        bv[a[i]]++;
    }
    i=0;
    int output=1;
    while(i<=k){
        if(bv[i]!=0)output=output*bv[i];
        i++;
    } 
    printf("ans=> %d\n",output);
}

int main(){
    int a[]={0,0,1,4,1,2};
    int n=sizeof(a)/sizeof(a[0]);
    calCnt(a,n);
    return 0;
}
