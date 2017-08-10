#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINKS 1000
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


LINKS *head=NULL;
typedef struct hashNode{
	
	LINKS *head;
	int total;

	
}HashTable;

int getHashCode(int n){

	return (n)%MAX_HASH_SIZE;

}


void insertItAfter(LINKS *first,LINKS *node,int total){

	LINKS *second = first;
	for(int i=0;i<total;i++)
		second = second->next;
	
	node->prev = first;
	node->next = second;
	first->next = node;
	if(second!=NULL)
	second->prev = node;

}
void insertInList(char *link,char *seedUrl,int depth,HashTable ht[]){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	node->seedUrl = seedUrl;
	node->depth = depth;
	node->isVisited = 0;
	node->next = NULL;
	
	int index = getHashCode(strlen(link));
	if(!ht[index].total){
		ht[index].total += 1;
		ht[index].head=node;
		node->next = head;
		node->prev=NULL;
		if(head!=NULL)
			head->prev=node;
		head=node;
		return;
	
	
	}
	
	
	
	
	LINKS *ptr;
	ptr = ht[index].head;
	printf("\nnode %s existes\n",ptr->link);
	insertItAfter(ptr,node,ht[index].total);
	ht[index].total += 1;


}

int isUniqueInList(int key,char *url,HashTable ht[]){
	
	int index = getHashCode(key);
	int total = ht[index].total;
	LINKS *ptr = ht[index].head;
	for(int i=0;i<total;i++){
		printf("\n##%s # %s#\n",url,ptr->link);
		if(!strcmp(ptr->link,url))
			return 0;
		ptr = ptr->next;
	
	}
	return 1;


}

int main(){

	char *link;
	char *seedUrl;
	int depth;
	
	
	HashTable ht[100];
	
	
	for(int i=0;i<100;i++)
		ht[i].total=0;
	
	link="jmit.ac.in";
 	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,ht);
	
	
	link="mmu";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,ht);
	
	
	
	link="nit";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,ht);
	
	
	
	link="kitm";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,ht);
	
	
	for(LINKS *ptr=head;ptr!=NULL;ptr=ptr->next)
		printf("\n%s\n",ptr->link);
	//printf("\n\n%s\n\n",ht[getHashCode(strlen(link))]->link);
	link="jmit.ac.in";
	printf("\n%d\n" ,isUniqueInList(strlen(link),link,ht));
	
	
	
	
}