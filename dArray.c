#include<stdio.h>
#include<stdlib.h>
typedef struct darray{
    int *a;
    int len;
}darray;

darray* createArray(int data){
    darray* tmp=(darray*)malloc(sizeof(darray));
    tmp->a=malloc(sizeof(int));
    tmp->a[0]=data;
    tmp->len=1;
    return tmp; 
}

darray* dArrayInsert(darray* da,int data){
    da->a=realloc(da->a, sizeof(int)*da->len+1);
    da->a[da->len]=data;
    da->len=da->len+1;
    return da;
}

void printda(darray* da){
    int i=0;
    while(i<da->len){
        printf("%d ",da->a[i]);
        i++;
    }
    printf("\n");
}

int main(){
    darray *da=createArray(0);
    for(int i=1;i<200000;i++)
    {
        da=dArrayInsert(da,i);
    }
    return 0;
}
