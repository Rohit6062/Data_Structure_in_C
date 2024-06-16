#include<stdio.h>
#include<stdlib.h>
struct dnode{
int data;
struct dnode* next;
struct dnode* prev;
};
void insert(struct dnode** head,int data){
	struct dnode* ptr=*head;
	while(*head){
printf("inseide loop");
	*head=(*head)->next;
}
*head=(struct dnode*)malloc(sizeof(struct dnode*));
(*head)->data=data;
(*head)->next=NULL;
head=&ptr;
}



void traverse(struct dnode* head){
//traverse the doubly link list
struct dnode* ptr=head;
while(ptr){
printf("%d\t",ptr->data);
ptr=ptr->next;
}
printf("\n");
}
















int main()
{
struct dnode* head=(struct dnode*)malloc(sizeof(struct dnode*));
head->prev=NULL;
head->data=0;
int i=1;
while(i<10){
insert(&head,i);i++;
}
printf("%p\n",head->next);

return 0;
}
