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

typedef struct node{

	int isVisited;
	char *link;
	char *seedUrl;
	struct node *next;
	struct node *prev;


}LINKS;

LINKS *head=NULL;

void insertInList(char *link,char *seedUrl){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	node->seedUrl = seedUrl;
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


}
void printAll(){
	
	LINKS *ptr;
	ptr = head;
	while(ptr!=NULL){
		printf("link = %s seedLink = %s\n",ptr->link,ptr->seedUrl);
		ptr=ptr->next;
	}

	
}
int main(){
	
	char *link;
	char *seedUrl;
	
	
	link = (char *)malloc(sizeof(char)*100);
	seedUrl  = (char *)malloc(sizeof(char)*100);
	sprintf(link,"google.com");
	sprintf(seedUrl,"sgoogle.com");
	insertInList(link,seedUrl);
	//free(link);
	//free(seedUrl);
	
	link = (char *)malloc(sizeof(char)*100);
	seedUrl = (char *)malloc(sizeof(char)*100);
	sprintf(link,"yahoo.com");
	sprintf(seedUrl,"syahoo.com");
	insertInList(link,seedUrl);
//	free(link);
//	free(seedUrl);
	
	
	link = (char *)malloc(sizeof(char)*100);
	seedUrl  = (char *)malloc(sizeof(char)*100);
	sprintf(link,"orkut.com");
	sprintf(seedUrl,"sorkut.com");
	insertInList(link,seedUrl);
//	//free(link);
//	free(seedUrl);
	
	
	
	link = (char *)malloc(sizeof(char)*100);
	seedUrl = (char *)malloc(sizeof(char)*100);
	sprintf(link,"fb.com");
	sprintf(seedUrl,"sfb.com");
	insertInList(link,seedUrl);
//	free(link);
//	free(seedUrl);
	
	
	
	
	printAll();
	


}

