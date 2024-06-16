/*  properties of Btree
 *  All leaf node should be at same level.
 *  every node have range of keys (min - max)
 *  at insertion split smaller half keys in one node and other greater half in another node and push middle key to parent.
*/

#include<stdio.h>
#include<stdlib.h>

struct container;
struct node;

typedef struct node{
    int key;
    void* link;
    // type container
}node;

typedef struct container{
    struct node* a;
    int len;
}container;



int main(){
    return 0;
}

