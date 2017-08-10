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



int getHashCode(int n){

	return (n)%100;

}


LINKS *getNode(char *link,char *seedUrl,int depth,LINKS *HashTable[100]){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	node->seedUrl = seedUrl;
	node->depth = depth;
	node->isVisited = 0;
	node->next = NULL;
		
	//node->prev = NULL;
	
	
	
	return node;
	


}

void insertIntoHash(char *link,char *seedUrl,int depth,LINKS *HashTable[100]){

	LINKS *node = getNode(link,seedUrl,depth,HashTable);
	int index = getHashCode(strlen(link));
	
	if(HashTable[index]==NULL){
		HashTable[index] = node;
		return;
	}
	
	LINKS *ptr = HashTable[index];
	
	while(ptr->next!=NULL)
		ptr = ptr->next;
	
	ptr->next = node;
	
	
	

}

int isUnique(LINKS *HashTable[100],char *link){


	int index = getHashCode(strlen(link));
	
	LINKS *temp = HashTable[index];
	while(temp!=NULL){
		if(!strcmp(link,temp->link))
			return 0;
	
		temp=temp->next;
	}
	return 1;


}
/*

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
	
}*/
int main(){

	char *link;
	char *seedUrl;
	int depth;
	
	
	LINKS *HashTable[100];
	
	for(int i=0;i<100;i++)
		HashTable[i]=NULL;
	
	link="jmit.ac.in";
 	seedUrl="abc";
	depth=2;
	insertIntoHash(link,seedUrl,depth,HashTable);
	
	
	link="mmu";
	seedUrl="abc";
	depth=2;
	insertIntoHash(link,seedUrl,depth,HashTable);
	
	
	
	link="nit";
	seedUrl="abc";
	depth=2;
	insertIntoHash(link,seedUrl,depth,HashTable);
	
	
	
	link="kitm";
	seedUrl="abc";
	depth=2;
	insertIntoHash(link,seedUrl,depth,HashTable);
	
	
	
	link = "nit";
	printf("\n\n%s\n\n",HashTable[getHashCode(strlen(link))]->link);
	
	printf("%d" ,isUnique(HashTable,"jmit.ac.i"));
	
	
	
	
}