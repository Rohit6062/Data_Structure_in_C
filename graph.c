#include<stdio.h>
#include<stdlib.h>
#include"stack.c" 

typedef struct graph{
    int data;  // data of current node
    struct graph **adj; // address of naighbour nodes
    int adj_cnt;  // count of naighbours
}graph;

// initalize graph 
graph* init_graph(int data){
    graph* tmp;
    tmp= malloc(sizeof(graph));
    tmp->data=data;
    tmp->adj = NULL;
    tmp->adj_cnt=0;
    return tmp;
}


// insert data at naighbour of perticular node
void graph_insert(graph* graph,int data){
    graph->adj = realloc(graph->adj, sizeof(graph)*graph->adj_cnt+1);
    graph->adj[graph->adj_cnt] = init_graph(data);
    graph->adj[graph->adj_cnt]->adj_cnt=0;
    graph->adj_cnt=graph->adj_cnt + 1;
}

// insert node at naighbour of any perticular node
void add_adj_node(graph* graph, int adj_to, int data){
    if(graph->data==adj_to){
        graph_insert(graph,data);
//        printf("data inserted succesfull!\n");
        return ;
    } 
    if(graph->adj_cnt==0){
        return;
    }
    for(int i=0; i<graph->adj_cnt ; i++){
        add_adj_node(graph->adj[i],adj_to,data);
    }

}

// normal print graph  thiss will goes in infinite loop for cycles. 
void p_graph(graph* root){
    printf("data-> %d ",root->data);
    if(root->adj_cnt == 0){
        return ;
    }
    for(int i=0;i<root->adj_cnt;i++){
        p_graph(root->adj[i]);
    }
}

// finde node with perticular data and retrun address
graph* find_return_node(graph* root , int data){
    if(root->data==data){
        return root;
    }
    if(root->adj_cnt==0)return NULL;
    graph* tmp;
    for(int i=0;i<root->adj_cnt;i++){
        tmp=find_return_node(root->adj[i], data);
        if(tmp!=NULL) return tmp;
    }
    return NULL;
}

// connect to two existing nodes
void connect_to_existing(graph* root, graph* curr,int from, int to){
    if( curr->data == from){
        curr->adj = realloc(curr->adj, sizeof(graph)* curr->adj_cnt+1);
        graph* tmp =  find_return_node(root,to);
        if(tmp==NULL){
            printf("element %d not found \n",to);
        }else{
            curr->adj = realloc(curr->adj,sizeof(graph)*curr->adj_cnt+1);
            curr->adj[curr->adj_cnt] = tmp;
            curr->adj_cnt= curr->adj_cnt + 1;
            printf("connection succesfull. This is a process of creating cycle \n");
        }

        return ;
    }
    if(curr->adj_cnt==0){
        return;
    }
    for(int i=0;i<curr->adj_cnt;i++){
        connect_to_existing(root,curr->adj[i],from,to);
    } 
}

// helper function for dfs search in graph
void dfshelper(graph* root,stack* visited, stack* naighbours){
    if(isempty(*naighbours))return;
    if(isInStack(*visited,root->data))return;
    printf(" %d ",root->data);
    push(visited,root->data);
    for(int i=0;i<root->adj_cnt;i++){
        push(naighbours,root->adj[i]->data);
    }
    for(int i=0;i<root->adj_cnt;i++){
        dfshelper(root->adj[i],visited,naighbours);
    }
}

// dfs search in graph
void dfs_graph(graph* root){
    stack visited;
    visited.top = 0;
    visited.a =NULL;
    stack naighbours;
    naighbours.top = 0;
    naighbours.a =NULL;
    for(int i=0;i<root->adj_cnt;i++){
        push(&naighbours,root->adj[i]->data);
    }
    dfshelper(root,&visited,&naighbours);
    printf("\n");
} 

void bfs_graph_helper(graph* root, stack* visited, stack* naighbours){
    for(int i=0;i<root->adj_cnt;i++){
        if(isInStack(*visited,root->adj[i]->data)==false){ 
            printf(" %d ",root->adj[i]->data);
            push(visited,root->adj[i]->data);
            push(naighbours,root->adj[i]->data);
        }
    }
    for(int i=0;i<root->adj_cnt;i++)
        bfs_graph_helper(root->adj[i],visited,naighbours);
    
}

void bfs_graph(graph* root){
    stack visited;
    visited.top=0;
    visited.a=NULL;
    stack naighbours;
    naighbours.top=0;
    naighbours.a=NULL;
    push(&visited,root->data);
    printf(" %d ",root->data);
    for(int i=0;i<root->adj_cnt;i++){
        printf(" %d ",root->adj[i]->data);
        push(&visited,root->adj[i]->data);
        push(&naighbours,root->adj[i]->data);
    }
    for(int i=0;i<root->adj_cnt;i++){
        bfs_graph_helper(root->adj[i],&visited,&naighbours);
    }
    printf("\n");
}
/*
int main(){
    graph* root = init_graph(1); 
    add_adj_node(root,1,4);
    add_adj_node(root,1,2);
    add_adj_node(root,4,3);
    add_adj_node(root,3,10);
    add_adj_node(root,3,9);
    add_adj_node(root,2,3);
    add_adj_node(root,3,2);
    add_adj_node(root,2,8);
    add_adj_node(root,2,5);
    add_adj_node(root,2,7);
    add_adj_node(root,5,8);
    add_adj_node(root,5,7);
    add_adj_node(root,5,6);
    printf("--> Death First Search <-- \n");
    dfs_graph(root);
    printf("--> Breath First Search <-- \n");
    bfs_graph(root);
    return 0;
}
*/
