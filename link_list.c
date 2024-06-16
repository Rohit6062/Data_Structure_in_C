#include<stdio.h>
#include<stdlib.h>
struct node //link list structure
{
    int data;
    struct node *link;
};

void pNode(struct node* tmp){
    if(tmp==NULL)return;
    printf("%d\t",tmp->data);
}

void travers(struct node* head)//travers complete link list
{
    if(head==NULL){
        printf("List is empty\n");
        return;
    }
    struct node *it=head;
    while(it)
    {
        pNode(it);
        it=it->link;
    }
    printf("\n");
}

void insert(struct node* head,int data)// insert element at the last of link list in  O(N)
{ 
    if(!head){
        *(&head) = (struct node*)malloc(sizeof(struct node));
        printf("why nor %p\n",*(&head));
        head->data  = data;
        return ;
    }
    struct node* it=head;
	while(it->link){
		it=it->link;
	}
	it->link=(struct node *)malloc(sizeof(struct node *));
	it->link->data =data;
	it->link->link=NULL;
}

void add_at_end(struct node** tail,int data)// take the tail element and insert data into it
// fastest method for larg data item set work in O(1)
{
	(*tail)->link=(struct node*)malloc(sizeof(struct node *));
	(*tail)->link->data=data;
	(*tail)->link->link=NULL;
	*tail=(*tail)->link;
}



// insert data at start of list
void insert_at_start(struct node **head,int data){
	struct node* temp=(struct node *)malloc(sizeof(struct node*));
	temp->data=data;
	temp->link=*head;
	*head=temp;
}

int valueAt(struct node* head,int pos){
    int i=0;
}

void insertAtPos(struct node* head,int pos,int data){
//insert data at given position
	struct node* ptr=head;
	while(pos>1 && ptr->link!=NULL){
        ptr=ptr->link;
        pos--;
	}
	if(ptr->link == NULL){
        printf("Index out of range\n");	
        return;
    }
	struct node* temp=(struct node*)malloc(sizeof(struct node*));
	temp->data=data;
	temp->link=ptr->link;
	ptr->link=temp;
}





void deleteNode(struct node** head,int data)
//delete given data
{
	struct node * temp;
	if ((*head)->data == data)	// check if data is present at first node
	{
		(*head)->data=0;
		temp=*head;
		*head=(*head)->link;
		free(temp); //making that memory location empty
		temp=NULL;
		return;
	}
	struct node* ptr=*head;
	while(ptr->link) //increamenting iterator until we found our data
	{
        if(ptr->link->data == data)break;
        ptr=ptr->link;	
	}
	if(ptr->link!=NULL){
        temp=ptr->link;
        ptr->link=ptr->link->link;
        free(temp); // making that memory location empty
        temp=NULL;
	}
	else{
        printf("Data Is not Present In linked list\n");
        }
    }
 	
void deleteList(struct node** head){
//delete complete link list
    struct node* tmp2=*head;
    struct node* temp;	
    while((*head)->link!=NULL){
        temp=*head;
        *head=(*head)->link;
        free(temp);
    }
    free(*head);
    *head=NULL;
}

int linkLength(struct node* head){
// return length of link list
	int cnt=0;
	struct node *tmp=head;
	while(tmp){
        cnt++;
        tmp=tmp->link;
    }
    return cnt;
}	




void reverseLink(struct node** head){
//reverse the link list
    struct node* prev=NULL,*next=NULL;
    while(*head){
        next=(*head)->link;
        (*head)->link=prev;
        prev=*head;
        *head=next;
    }
    *head=prev;
}


/*

//driver code for link-list usage
int main()
{
    struct node *head,*tail;
    head = (struct node *)malloc(sizeof(struct node));
    head->data =0;
    tail=head;
    int i=1;
    while(i<101)
    {
    add_at_end(&tail,i);
    i++;
    }
    travers(head);
    reverseLink(&head);
    travers(head);
    return 0;
}*/
