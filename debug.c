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



typedef struct node{

	int isVisited;
	char *link;
	char *seedUrl;
	int depth;
	struct node *next;
	struct node *prev;


}LINKS;

LINKS *head=NULL;

void insertIntoHash(LINKS *HashTable[100],int index){

	index %= 100;
	if(HashTable[index]!=NULL){
	
		LINKS *temp;
		temp=HashTable[index];
		while(temp->)
	
	
	}
	

}
void insertInList(char *link,char *seedUrl,int depth,LINKS *HashTable[100]){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	node->seedUrl = seedUrl;
	node->depth = depth;
	node->isVisited = 0;
	node->next = NULL;
	if(head==NULL){
		head = node;
		
		node->prev = NULL;
	
	}
	else{
		temp = head;
		
		while(temp->next!=NULL)
			temp = temp->next;
		
		
		temp->next = node;
		node->prev = temp;

	}
	int index=strlen(link)%100;
	while(HashTable[index]!=NULL){
		index++;
	}
	
	insertIntoHash(HashTable,strlen(link));
	
	


}


int printAll(){
	
	LINKS *ptr;
	int noOfLinks=0;
	ptr = head;
	while(ptr!=NULL){
		printf("link = %-50s  depth = %d    isVisited=%d\n",ptr->link,ptr->depth,ptr->isVisited);
		noOfLinks++;
		ptr=ptr->next;
	}

	return noOfLinks;
	
}
int main(){

	char *link;
	char *seedUrl;
	int depth;
	
	bhgy
	
	for(int i=0;i<100;i++)
		HashTable[i]=NULL;
	
 	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,HashTable);
	
	
	link="mmu";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,HashTable);
	
	
	
	link="nit";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,HashTable);
	
	
	
	link="kitm";
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,HashTable);
	
	printf("\n%d\n",printAll());
	
	link = "jmit.ac.in";
	printf("\n\n%s\n\n",HashTable[strlen(link)%100]->link);
	
	
	
	
}