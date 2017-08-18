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
	
		
		}
	
	
	
	
	i++;
	
	
	
	
	
	}

}
void main(){
	
	char *buffer;
	theWords *head=NULL;
	hashTable ht[300];
	
	for(int i=0;i<300;i++)
		ht[i].head=NULL;
	
	buffer = readTheFile();
	makeTheList(buffer,&head,ht);
	free(buffer);
	/*for(theWords *ptr=head;ptr;ptr=ptr->next)
		printf("%-90s %-40s %d\n",ptr->url,ptr->keyword,ptr->freq);*/
	printf("%s\n",ht[getHashValue("hygienists")].head->url);
	
	
}