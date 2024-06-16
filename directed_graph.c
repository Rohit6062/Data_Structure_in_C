#include<stdio.h>
#include<stdlib.h>
#include"stack.c"
typedef struct tuple{
    void * link;
    int weight;
}tuple;

typedef struct dnode{
    int data;
    tuple* adj;
    int adj_cnt;
}dnode;

dnode* init_dnode(int data){
    dnode * tmp = malloc(sizeof(dnode));
    tmp->data = data;
    tmp->adj_cnt=0;
    tmp->adj= NULL;
    return tmp;
}

void pnode(dnode* root){
    printf("data-> %d \n",root->data);
}

void connect_nodes(dnode* node1,dnode* node2,int weight){
    node1->adj_cnt = node1->adj_cnt + 1;
    node2->adj_cnt = node2->adj_cnt + 1;
    node1->adj = realloc(node1->adj,sizeof(tuple)*node1->adj_cnt);
    node2->adj = realloc(node2->adj,sizeof(tuple)*node2->adj_cnt);
    // i dont know why . is working here instead of ->
    node1->adj[node1->adj_cnt-1].link=node2;
    node1->adj[node1->adj_cnt-1].weight=weight;
    node2->adj[node2->adj_cnt-1].link=node1;
    node2->adj[node2->adj_cnt-1].weight=weight;
}
void addAdjNode(dnode* root,int data,int weight){
    dnode * tmp= init_dnode(data);
    connect_nodes(root,tmp,weight);
}

void dfs_dgraph_helper(dnode* root,stack* visited, stack* naighbours){
    if(isempty(*naighbours))return;
    if(isInStack(*visited,root->data))return;
    pnode(root);
    push(visited,root->data);
    for(int i=0;i<root->adj_cnt;i++){
        dnode* tmp= root->adj[i].link;
        push(naighbours,tmp->data);
    }
    for(int i=0;i<root->adj_cnt;i++){
        dfs_dgraph_helper(root->adj[i].link,visited,naighbours);
    }
}

void dfs_dgraph(dnode* root){
    stack visited;
    visited.top=0;
    visited.a = NULL;
    stack naighbours;
    naighbours.top=0;
    naighbours.a=NULL;
    for(int i=0;i<root->adj_cnt;i++){
        dnode* tmp= root->adj[i].link;
        push(&naighbours,tmp->data);
    }
    dfs_dgraph_helper(root,&visited,&naighbours); 
}
/*
int main(){
    dnode* root=init_dnode(10);
    addAdjNode(root,11,2);
    addAdjNode(root,12,5);
    dfs_dgraph(root);
    return 0;
}
*/
