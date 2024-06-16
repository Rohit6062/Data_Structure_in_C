#include<stdio.h>
#include<stdlib.h>


/*
 * Complexity For Two sided Buffer array
 * ascess Element O(1);
 * insert_last O(1);
 * insert_first O(1);
 * insterAtIndex  less than O(n);
 * delete less than O(n);
 * */

typedef struct buffArray{
    int* a;
    int start;  // starting index of data
    int len;    // length of current data
    int size;   // size of total Array;
}buffArray;

int mod(int x, int y){
    if(x < y)return x;
    return mod(x-y,y);
}

void norPrint(buffArray* ba){
    for(int i=0;i<ba->size;i++){
        printf(" %d",ba->a[i]);
        }
    printf("\n");
}

buffArray* newBuffArray(int data){
    buffArray* tmp=(buffArray*)malloc(sizeof(buffArray));
    tmp->a=malloc(sizeof(int)*10);
    tmp->len =1;
    tmp->size = 10;
    tmp->a[5]=data;
    tmp->start=4;
    return tmp;
}

buffArray* expand(buffArray* ba){
    buffArray* tmp = (buffArray*)malloc(sizeof(buffArray)); 
    tmp->a = malloc(sizeof(int)* ba->size*2);
    int j=ba->size/2;
    tmp->size=ba->size*2;
    for(int i=0;i<ba->size;i++){
        tmp->a[j]=ba->a[mod(ba->size+ba->start+1+i,ba->size)];
        j++;
    }
    tmp->len=ba->len;
    tmp->start=ba->size/2-1;
    free(ba);
    ba=NULL;
    return tmp;
}

buffArray* shrink(buffArray* ba){
    buffArray* tmp = (buffArray*)malloc(sizeof(buffArray));
    tmp->a=malloc(sizeof(int)*ba->size/2);
    tmp->size=ba->size/2;
    for(int i=0;i<tmp->size;i++){
        tmp->a[i]=ba->a[mod(ba->size+ba->start+1+i,ba->size)];
    }
    tmp->len=ba->len;
    tmp->start=-1;
    free(ba);
    ba=NULL;
    return tmp;
}

// add data at last 
buffArray* baAppend(buffArray *ba, int data){
    if(ba->len==ba->size){
        ba=expand(ba);
    }
    ba->a[mod(ba->size+ba->start+ba->len+1,ba->size)]=data;
    ba->len = ba->len + 1;
    return ba;
}

buffArray* baInsert(buffArray *ba, int data){
    if(ba->len == ba->size ){
        ba=expand(ba);
    }
    ba->a[mod(ba->start+ba->size,ba->size)]=data;
    ba->start=ba->start - 1;
    ba->len = ba->len + 1;
    return ba;
}

void printba(buffArray* ba){
    printf("Lenght and Size Of Array => %d , %d \n",ba->len,ba->size);
    for(int i=0;i<ba->len;i++){
        printf("%d ",ba->a[mod(ba->size+ba->start+1+i,ba->size)]);
    }
    printf("\n");
}

buffArray* shiftElementsLeft(buffArray * ba,int fromPos ,int toPos){
    if(ba->size==ba->len){
        ba=expand(ba);
    }
    for(int i=fromPos;i<toPos;i++)
        ba->a[ba->start+i]=ba->a[ba->start+1+i];
    return ba;
}

buffArray* shiftElementsRight(buffArray * ba,int fromPos ,int toPos){
    if(ba->len==ba->size){
        ba=expand(ba);
    }
    for(int i=toPos;i>=fromPos;i--)
        ba->a[ba->start+i+1]=ba->a[ba->start+i];
    return ba;
}

buffArray* insertAt(buffArray* ba, int pos, int data){
    if(pos <= 0){
        return baInsert(ba,data);
    }
    if(pos >= ba->len){
        return baAppend(ba,data);
    }
    if(pos <= ba->len/2){
        printf("left\n");
        ba=shiftElementsLeft(ba,0,pos-1);
        ba->start=ba->start-1;
    }
    else{
        printf("right\n");
        ba=shiftElementsRight(ba,pos-1,ba->len);
    }
    ba->a[ba->start+pos]=data;
    ba->len = ba->len + 1;
    return ba;
}

buffArray* deleteAtPos(buffArray* ba, int Index){
    if(Index <= 0){
        ba->start=ba->start+1;
    }
    else if(Index >= ba->len-1){
        // Eat 5 Star and do nothing
    }
    else if(Index < ba->len/2){
        printf("left\n");
        ba=shiftElementsRight(ba,0,Index);
        ba->start = ba->start + 1;
    }
    else{
        printf("right\n");
        ba=shiftElementsLeft(ba,Index+1,ba->len);
    }
    ba->len = ba->len - 1;
    if(ba->len<=ba->size/2)
    {
        ba=shrink(ba);
    }
    return ba;
}

int valueAtIndex(buffArray* ba,int index){
    if(ba==NULL)return -1;
    if(index<0)return ba->a[ba->start+1];
    return ba->a[mod(ba->size+ba->start+index+1,ba->size)];
}
/* Code for testing */
/*
int main(){ 
    buffArray *ba = newBuffArray(-1);
    for(int i = 1; i <=19; i++){
        ba=baInsert(ba,i);
    } 
        printba(ba);
    printf("%d \n",valueAtIndex(ba,17));
    ba=deleteAtPos(ba,17);
        printba(ba);
    norPrint(ba);
    return 0;
}*/
