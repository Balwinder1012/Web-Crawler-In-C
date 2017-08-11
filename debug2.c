#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINK_SIZE 100
#define MAX_LINKS_ALLOWED 5
#define MAX_HASH_SIZE 100

typedef struct node{

	int isVisited;
	char *link;
	char *seedUrl;
	int depth;
	struct node *next;
	struct node *prev;


}LINKS;



typedef struct hashNode{
	
	LINKS *head;
	int total;

	
}HashTable;

int getHashCode(int n){

	return (n)%MAX_HASH_SIZE;

}


void insertItAfter(LINKS *first,LINKS *node,int total){

	LINKS *second = first;
	LINKS *temp=NULL;
	for(int i=0;i<total;i++){
		temp=second;
		second = second->next;
	}
	
	node->prev = temp;
	node->next = second;
	temp->next = node;
	if(second!=NULL)
	second->prev = node;




}
void insertInList(char *link,LINKS **head,HashTable ht[]){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	
	node->isVisited = 0;
	node->next = NULL;
	
	int index = getHashCode(strlen(link));
	if(!ht[index].total){
		ht[index].total += 1;
		ht[index].head=node;
		node->next = *head;
		node->prev=NULL;
		if((*head)!=NULL)
		(*head)->prev=node;
		*head=node;
		return;
	
	
	}
	
	
	
	
	LINKS *ptr;
	ptr = ht[index].head;
	
	insertItAfter(ptr,node,ht[index].total);
	ht[index].total += 1;


}


int main(){

	char *link;
	int counter=0;
	LINKS *head = NULL;
	int size=3;
	HashTable ht[100];
	
	for(int i=0;i<100;i++)
		ht[i].total=0;
	for(int counter=0;counter<size;counter++){
		link = (char *)malloc(sizeof(char)*20);
		sprintf(link,"abc%d",counter);
		insertInList(link,&head,ht);
	}
		int c=0;
	for(LINKS *ptr=head;ptr!=NULL;ptr=ptr->next)
		printf("\n\n%s %d\n",ptr->link,++c);
	/*
	for(LINKS *ptr=head;ptr!=NULL;)
	{
		LINKS *t = ptr;
		ptr=ptr->next;
		free(t->link);
		free(t);
	}
	*/


}