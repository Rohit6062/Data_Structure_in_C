#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct bstack *bstack;

typedef struct barray{
    int* a;
    int len;
    int size;
}*barray;
//97630 89948

struct bstack{
    barray ba;
    void (*push) (bstack, int);
    int(*pop) (bstack);
};

bstack buildStack();

void cleanStack(bstack);

void barray_push(bstack this,int data){
    barray tmp = this->ba;
    int* a = tmp->a;
    int len = tmp->len;
    if(len == tmp->size){
        a= realloc(a, sizeof(int)*len*2);
        tmp->size = tmp->size*2;
    }
    a[len] = data;
    len++;
    tmp->len = len;
    tmp->a = a;
}
int barray_pop(bstack this){
    barray ba = this->ba;
    int output=-1;
    int* a = ba->a;
    int len = ba->len;
    if(len > 0){
        len--;
        output = a[len];
    }
    ba->len=len;
    ba->a=a;
    return output;
}

bstack buildStack(){
    bstack output = (bstack) malloc(sizeof(bstack));
    barray a = malloc(sizeof(barray));
    output->push = barray_push;
    output->pop  = barray_pop;
    a->a=malloc(sizeof(int)*10);
    a->len=0;
    a->size=10;
    output->ba=a;
    return output;
}

void pstack(bstack this){
    barray a= this->ba;
    for(int i=0;i<a->len;i++){
        printf("%d ",a->a[i]);
    }
    printf("\n");
}

void cleanStack(bstack bs){
    free(bs->ba);
    free(bs);
}
/*
int main(){
    bstack b = buildStack();
    int br[]={0,1,0,0,1,0,0,0,1,1,1,0,0,1,1,0,1,0,1,0,0,1,1};
    int len=sizeof(br)/sizeof(br[0]);
    int i=0;
    char output=1;
    while(i<len){
        if(br[i]==1){
            if(b->pop(b)==-1){
                output=0;
                i=len;
            }
        }
        else{
            b->push(b,0);
        }
        i++;
    }
    if(b->pop(b)!=-1)output=0;
    printf("Output-> %d\n",output);
    return 0;
}
*/
