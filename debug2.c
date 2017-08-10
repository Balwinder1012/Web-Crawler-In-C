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


typedef struct hashNode{
	
	LINKS *head;
	int total;

	
}HashTable;

int getHashCode(int n){

	return (n)%100;

}

void insertAtBeg(LINKS ***head,LINKS *node){

	node->next = **head;
	node->prev = NULL;
	**head = node;
}

void insertItAfter(LINKS *node,LINKS *head,int total){

	LINKS *NextNode;
	LINKS *prev = NULL;
	NextNode = head;
	printf("\nv## alue of t is %d\n",total);
	for(int i=0;i<total;i++){
		prev = NextNode;
		NextNode = NextNode->next;
	}
	
	
	node->prev = prev;
	node->next = NextNode;
	prev->next = node;
	if(NextNode!=NULL)
	NextNode->prev = node;
	
		


}
void insertInList(char *link,char *seedUrl,int depth,LINKS **head,HashTable ht[100]){

	LINKS *node = (LINKS *)malloc(sizeof(LINKS));
	LINKS *temp;
	node->link = link;
	node->seedUrl = seedUrl;
	node->depth = depth;
	node->isVisited = 0;
	node->next = NULL;
	
	int index  = getHashCode(strlen(link));
	if(!ht[index].total){
		ht[index].head=node;
		ht[index].total +=1;
		insertAtBeg(&head,node);
		//printf("%s",(*head)->link);
		return;
	}
	
	while(ht[index].total==0)
		index++;
	
	index = getHashCode(index);
	
//	ht[index].total += 1;
	
	insertItAfter(node,ht[index].head,ht[index].total);
	
	ht[index].total +=1;
	
	
	
	
	
	

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
int isUnique(char *url,HashTable ht[100]){
	
	int index = getHashCode(strlen(url));
	LINKS *ptr = ht[index].head;
	int t = ht[index].total;
	
	printf("\nvalue of t is %d\n",t);
	for(int i=0;i<t;i++){
		printf("\n## %s %s ##\n",ptr->link,url);
		if(!strcmp(ptr->link,url))
			return 0;
		ptr=ptr->next;
	}
	return 1;

}
int main(){

	LINKS *head;
	char *seedUrl;
	int depth;
	
	head=NULL;
	HashTable ht[100];
	
	
	for(int i=0;i<100;i++)
		ht[i].total=0;

	

	 char *link = (char *)malloc(sizeof(char)*50);
	
	sprintf(link,"kitm");
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,&head,ht);	
	
	
	
	link = (char *)malloc(sizeof(char)*50);
	
	sprintf(link,"jmit");
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,&head,ht);	
	
	
	link = (char *)malloc(sizeof(char)*50);
	
	sprintf(link,"kkr");
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,&head,ht);	
	
	link = (char *)malloc(sizeof(char)*50);
	
	sprintf(link,"nir");
	seedUrl="abc";
	depth=2;
	insertInList(link,seedUrl,depth,&head,ht);	
	
	
	
	printf("\n\n");
	for(LINKS *temp=head;temp!=NULL;temp=temp->next)
printf("%s ",temp->link);

	
	link = "kitm";
	printf("\n\n%d\n\n",isUnique(link,ht));
	

	
	
	
	
}