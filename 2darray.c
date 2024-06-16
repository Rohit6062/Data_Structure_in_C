#include<stdio.h>
#include<stdlib.h>
void pa(int *a,int n){
  int i=1;
  while(i<=n){
    printf("%d ",a[i-1]);
    i++;
  }
  printf("\n");
}

void pm(int *a,int n,int m){
  int i=0,j=0;
  while(i<n){
    j=0;
    while(j<m){
      printf("%d ",*(a+i*m+j));
      j++;
    }
    printf("\n");
    i++;
  }

}

void fun(int *a,int n,int l){
  int k=-1;
  int x=n+1;
  int i=0;
  while(i<n*n){
    a[i]=1;
    i++;
  }

  pm(a,n,n);
}

int main(){
  int n=4;
  //scanf("%d",&n);
  int *a=malloc(sizeof(int[n*n]));
  int b[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
  //int *p=&a;
  pm(b,n,n);
  fun(b,4,2*n-1);
  return 0;
}
