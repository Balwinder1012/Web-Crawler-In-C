#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include<math.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINK_SIZE 100
#define MAX_WORDS_ALLOWED 300
#define MAX_HASH_SIZE 100
#define MAX_WORD 200

typedef struct lists{
	
	char *keyword;
	char *url;
	int freq;
	
	struct lists *next;

}theWords;

typedef struct hash{

	theWords *head;
	theWords *last;
}hashTable;

void traverseSpaces(char ch[],int *j){
    while(ch[*j]==' ')
        *j = *j + 1;
}

int pow_(int n,int p){
	if(p==0) return 1;
	if(p==1) return n;
	return pow_(n,p-1)*n;
}
int getHashValue(char *word){
	
	int ascii=0,i=0;
	while(word[i]!=null){
		
		ascii += word[i++];
	}
	
	
	return ascii%300;

}
char* readTheFile(){
	
    FILE *fp;
    char *buffer;
    long long int length;
	
    fp = fopen("indexerOutput.txt","rb");

    if(fp){

        fseek(fp,0,SEEK_END);
        length = ftell(fp);
        fseek(fp,0,SEEK_SET);
        buffer = (char *)malloc(sizeof(char)*(length+1));
        if (buffer)
            fread(buffer,1,length,fp);
        fclose(fp);
        buffer[length]=null;
		

    }
    else
        printf("\nError in reading the file \n\n");

	
    return buffer;

}




theWords *getNewNode(char *word,char *url,int freq){

	theWords *node = (theWords *)malloc(sizeof(theWords));
	node->keyword = word;
	//sprintf(node->keyword,"%s",word);
//	free(word);
	node->freq = freq;
	node->url = url;

	return node;
	

}
void insertIntoList(char *word,char *url,int freq,theWords ***head,hashTable ht[]){
	

	theWords *ptr;
	
	theWords *node = getNewNode(word,url,freq);
	int index =  getHashValue(word);
	if(ht[index].head==NULL){
		ht[index].head = node;
		ht[index].last=node;
		
		theWords *temp = **head;
		
		if(temp==NULL){
			**head = node;
			node->next=NULL;
		}
		else{
			node->next = **head;
			**head = node;
			ht[index].last=node;
		
		}
		
		if(0)
		while(temp!=NULL){
			printf("list is %s\n",temp->keyword);
			temp=temp->next;
		}
	}
	else{
		
		//return;
		ptr = ht[index].head;
		theWords *last;
	
		last = ht[index].last;
			
		while(ptr!=NULL && ptr!=last){
		
			ptr = ptr->next;
			
		}
		
	//return;
		node->next = ptr->next;
		ptr->next = node;
		ht[index].last = node;
		
		
	
	}
	
	


}



void makeTheList(char *buffer,theWords **head,hashTable ht[]){


	int i=0;
	while(buffer[i]!=null){
		
		while(buffer[i]!='\n'){
		
			i = i+5;
			traverseSpaces(buffer,&i);
		
			char *word = malloc(sizeof(char)*MAX_WORD);
			char *url = malloc(sizeof(char)*MAX_LINK_SIZE);
			int freq;
			int counter=0;
			
			
			
			while(buffer[i]!=' ')
				word[counter++] = buffer[i++];
			word[counter]=null;

			traverseSpaces(buffer,&i);
			
			counter=0;
			
			while(buffer[i]!=' ')
				url[counter++] = buffer[i++];
			url[counter]=null;
	
			traverseSpaces(buffer,&i);
						   
			int freqLen = 0;
			int j=i;
			while(buffer[j++]!='\n')
				freqLen++;
				
			int sum=0;
			
			while(freqLen>0){
				int n = buffer[i]-'0';
				sum +=  n * pow_(10,freqLen-1);
				freqLen--;
				i++;
			
			}
			
			freq = sum;
			insertIntoList(word,url,freq,&head,ht);
	//		printf("%-20s %-100s\n ",word,url);
		
		}
	
	
	
	
	i++;
	
	
	
	
	
	}

}/*
void qsort(theWords *arr,int l,int r){

	if(l<r){
	
		int mid = partition(arr,l,r);
		qsort(arr,l,mid-1);
		qsort(arr,mid+1,r);
	
	
	}


}
int pa*/
void bubbleSort(theWords *arr,int n){

	for(int i=0;i<n-1;i++)
	
		for(int j=0;j<n-i-1;j++)
		
			if(arr[j+1].freq>arr[j].freq){
				theWords temp;
				temp.url = arr[j+1].url;
				temp.freq = arr[j+1].freq;
				arr[j+1].url = arr[j].url;
				arr[j+1].freq = arr[j].freq;
				arr[j].url = temp.url;
				arr[j].freq = temp.freq;
			}


}
void printResultFor(char *word,hashTable *ht){

	int index = getHashValue(word);
	theWords *head = ht[index].head;
	theWords *tail = ht[index].last;
	
	theWords arr[300];
	int i=0;
	
	printf("%s",word);
	
	while(head!=tail ){
		
		if(!strcmp(head->keyword,word)){
		//arr[i].keyword = head->keyword;
		arr[i].url = head->url;
		arr[i].freq = head->freq;
		i++;
		}
		head=head->next;
		
	}
	
	
	bubbleSort(arr,i);
	if(1){
	for(int j=0;j<i;j++)
		printf("%-100s %d\n",arr[j].url,arr[j].freq);
	
	}

}
int isDoneAlready(char *url,theWords *arr,int n){
	for(int i=0;i<n;i++)
		if(!strcmp(arr[i].url,url)) 
			return 1;
	return 0;

}
int isPresentInAll(int freq,char *word,theWords *urls[],int n,int k,theWords *finalArr,int finalIndex){

	
	
	int f=freq;
	if(isDoneAlready(word,finalArr,finalIndex))
		return 0;
	
	if(n==k+1) return f;
	

//	printf("##n= %d k=%d##",n,k);
	for(int i=k+1;i<n;i++ ){
	
			for(int j=0;j<100;j++)
				
				if(urls[i][j].url!=NULL && !strcmp(word,urls[i][j].url)){
					f= f*10 + urls[i][j].freq;
					
					break;
				}
			
	
	
	
	}
	return f;
	

}
				   
void printTheResult(char *query[10],int n,hashTable ht[]){
	
	theWords *urls[n];
	int i=n;
	
	
	
	for(int j=0;j<i;j++){
		urls[j] = (theWords*)malloc(sizeof(theWords)*100);
	}
	
	for(int k=0;k<i;k++)
	
		for(int j=0;j<100;j++)
			urls[k][j].url=NULL;
	
	
	int arrySize=0;
	for(int k=0;k<i;k++){
	
	int index = getHashValue(query[k]);
	theWords *head = ht[index].head;
	theWords *tail = ht[index].last;
	
	int j=0;
		
	
	while(head!=tail){
		
		if(!strcmp(head->keyword,query[k])){
	
		urls[k][j].url = head->url;
		urls[k][j].freq = head->freq;
		urls[k][j].keyword = head->keyword;
		j++;
		arrySize++;
			if(j==100) break;
		}
		head=head->next;
		
	}
		
	}
	int p=0;
	theWords finalArr[arrySize];
	
	if(0)
	for(int k=0;k<i;k++)
	{
		for(int j=0;j<100;j++)
			if(urls[k][j].url!=NULL)
				printf("###%-100s  %-10s %d\n",urls[k][j].url,query[k],urls[k][j].freq);
			printf("\n");
		}
	
	
	
	for(int k=0;k<i;k++){
		
		for(int j=0;j<100;j++)
			if(urls[k][j].url!=NULL){
				int f=0;
			
				if(   f=isPresentInAll(urls[k][j].freq,urls[k][j].url,urls,i,k,finalArr,p)){
					finalArr[p].url=urls[k][j].url;
					finalArr[p].freq=f;
					
					p++;
				
				}
		
			
	
		}
		else break;
	
	
	
	}

	bubbleSort(finalArr,p);
	if(1){
	for(int j=0;j<p;j++)
		printf("%02d %-100s \n",j,finalArr[j].url);
	
	}
	for(int j=0;j<i;j++){
		free(urls[j]);
	}
	
	
//	printf("%s %s",urls[0]->url,urls[1]->url);
	
	
	

}
void main(int argc,char *argv[]){
	
	char *buffer;
	theWords *head=NULL;
	hashTable ht[300];
	
	
	
	for(int i=0;i<300;i++)
		ht[i].head=NULL;
	
	
	
	
	printf("\n################################SIMPLE SEARCH ENGINE######################\n");
	FILE *fp = fopen("indexerOutput1.txt","w");
	fclose(fp);
	
	buffer = readTheFile();
	makeTheList(buffer,&head,ht);

	free(buffer);
	
	
	printf("\n\n\n########LOADING RESULT#######\n\n\n");
	char *query[10];
	int i=0;
	int j=1;
	while(argc-->1)
		query[i++]=argv[j++];


	printTheResult(query,i,ht);
	
	
	if(1)
	for(theWords * temp=head;;){
	
		if(temp==NULL)
			break;
		free(temp->url);
		free(temp->keyword);
		theWords *p = temp;
		
		temp=temp->next;
		
		free(p);
		
	
	}
	
		

	
}