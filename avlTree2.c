/* tree is balanced */ 
/* abs(heigh of left sub tree - height of right sub tree) = 1 , 0 ,-1  */
 /**/

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    int rightc;
    int leftc;
    int height;
    struct node* left; 
    struct node* right;
}node;

int mx(int a,int b){
    if(a>b)return a;
    return b;
}

node* createNode(int data){
    node *tmp=  (node*)malloc(sizeof(node));
    tmp->height = 1;
    tmp->data   = data;
    tmp->left   = NULL;
    tmp->right  = NULL;
    tmp->rightc = 0;
    tmp->leftc  = 0;
    return tmp;
}

// print node of node tree
void pnode(node *node){
    printf("data => %d height => %d  leftc-> %d rightc-> %d\n",node->data,node->height,node->leftc,node->rightc);
}

void print2DAVL(node* root, int space, int count){
    if(root==NULL)return;
    space += count;
    print2DAVL(root->right,space,count);
    for(int i=count;i<space;i++){
        printf(" ");
    }
    printf("%d(%d)(%d %d)\n",root->data,root->height,root->leftc,root->rightc);
    print2DAVL(root->left,space,count);
}
// print complete node tree
void pavl(node *root){
    print2DAVL(root,0,5);
}

void inorder(node * root){
    if(root->left)inorder(root->left);
    pnode(root);
    if(root->right)inorder(root->right);
}

int height(node* root){
    return (root==NULL) ? 0: root->height;
}
int Count(node * root){
    return (root==NULL) ? 0: root->leftc+1+root->rightc;
} 

// right shift
node* rightShift(node* root){
    node* lr = root->left; // left of root
    root->left= lr->right;  // right of left
    lr->right=root;
    root->rightc =Count(root->right);
    root->leftc = Count(root->left);
    lr->rightc = Count(lr->right);
    return lr;
}
node* leftShift(node* root){
    node* rr = root->right; // right of root
    root->right= rr->left;   // left of right
    rr->left=root;
    root->rightc =Count(root->right);
    root->leftc = Count(root->left);
    rr->leftc  = Count(rr->left);
    return rr;
}

node *balanceIt(node * root){
    if(root == NULL)return NULL;
    if(height(root->left)-height(root->right) > 1)
    {
        if(height(root->left->left)-height(root->left->right)<0){
            root->left=leftShift(root->left);
            node* root_left = root->left->left;
            root_left->height = 1+mx(height(root_left->right),height(root_left->left));
       }
        root=rightShift(root);
        root->right->height = 1+mx(height(root->right->right),height(root->right->left));
        root->height = 1 + mx(height(root->left),height(root->right));
    }
    else if(height(root->left)-height(root->right) < -1)
    {
        if(height(root->right->left)-height(root->right->right)>0){
            root->right=rightShift(root->right);
            node* root_right = root->right->right;
            root_right->height = 1+mx(height(root_right->right),height(root_right->left));
        }
        root=leftShift(root);
        root->left->height = 1+mx(height(root->left->right),height(root->left->left));
        root->height = 1 + mx(height(root->left),height(root->right));
    }
    return root;
}

node* minNode(node* root){
    node* t=root;
    while(t->left!=NULL){
        t=t->left;
    }
    return t;
}

node* insertInAvl(node* root, int data, int pos){
    if(root==NULL)return createNode(data);
    int rh = height(root);
    if(root->leftc+1<pos){
        root->rightc = root->rightc +1;
        root->right=insertInAvl(root->right,data,pos-(root->leftc+1));
    }
    else{
        root->leftc = root->leftc +1;
        root->left=insertInAvl(root->left,data,pos);
    }
    root->height = 1 + mx(height(root->left),height(root->right));
    if(rh!=root->height)
        root=balanceIt(root);
    return root;
}

node* deleteInAvl(node* root,int pos){
    if(root->leftc + 1 < pos)
        root->rightc = root->rightc -1,
        root->right = deleteInAvl(root->right,pos - (1+root->leftc));
    else if(root->leftc + 1 > pos)
        root->leftc = root->leftc -1,
        root->left =  deleteInAvl(root->left,pos);
    else if(root->left && root->right){
        node* tmp = minNode(root->right);
        root->data = tmp->data;
        root->right = deleteInAvl(root->right,1);
    }
    else if(root->left){
        node * tmp = root;
        root = root->left;
        free(tmp);
    }
    else if(root->right){
        node* tmp = root;
        root = root->right;
        free(tmp);
    }
    else{
        free(root);
        root = NULL;
        return root;
    }
    if(root){
        root->height =1+mx(height(root->left),height(root->right));
        root = balanceIt(root);
    }
    return root;
}     


node* valueAt(node* root,int pos){
    if(pos < 1)
        return valueAt(root,1);
    else if(pos > root->leftc + root->rightc + 1)
        return valueAt(root,root->leftc+root->rightc+1);
    else if(pos > root->leftc + 1)
            return valueAt(root->right,pos - (root->leftc + 1));
    else if(pos < root->leftc+1)
            return valueAt(root->left,pos);
    else 
        return root;
}
