#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINK_SIZE 100
#define MAX_LINKS_ALLOWED 20
#define MAX_HASH_SIZE 100
#define MAX_WORD 50


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



int isValidDir(char *dir){

	struct stat statbuf;
	if ( stat(dir, &statbuf) == -1 ){
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "Invalid directory\n");
		fprintf(stderr, "-----------------\n");
		return 0;
	}

	//Both check if there's a directory and if it's writable
	if ( !S_ISDIR(statbuf.st_mode) ){
		fprintf(stderr, "-----------------------------------------------------\n");
		fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
		fprintf(stderr, "-----------------------------------------------------\n");
		return 0;
	}

	if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ){
		fprintf(stderr, "------------------------------------------\n");
		fprintf(stderr, "Invalid directory entry. It isn't writable\n");
		fprintf(stderr, "------------------------------------------\n");
		return 0;
	}
	return 1;

	
}

char* readTheFile(char *fileName){
	
    FILE *fp;
    char *buffer;
    long long int length;

    fp = fopen(fileName,"rb");

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
        printf("\n\n######################Error in reading the file %s$\n\n",fileName);

	
    return buffer;

}

int getAllTheFiles(char *dir,char *files[500]){
	
	//char *files[500];
	int counter=0;
	struct dirent *de;  // Pointer for directory entry
 
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir(dir);
	
 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        
    }
 
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL){
		
		int len = strlen(de->d_name);
		//printf("\n%d ",len);
		if(len >12){
			char *fileName = (char *)malloc(sizeof(char)*len+50);
			sprintf(fileName,"%s",de->d_name);
			files[counter++]=fileName;
			//printf("%s\n", files[counter-1]);
 
		}
		
			
	}
         // printf("%s\n", de->d_name);
 
    closedir(dr);   
	return counter;
	

}
int findOpenAnchorTag(char *ch,int *i){

    int j=*i;

    while(!(ch[j]=='<' && ch[j+1]=='t' && ch[j+2]=='i' && ch[j+3]=='t' && ch[j+4]=='l' && ch[j+5]=='e' && ch[j+6]=='>')){
        if(ch[j]==null){
            *i=j;
            return 0;
        }

        j++;

    }
	j=j+7;
    *i = j;
    return 1;




}
void traverseSpaces(char ch[],int *j){
    while(ch[*j]==' ')
        *j = *j + 1;
}
char *getTheWord(char *ch,int *i){

	int j=*i;
	traverseSpaces(ch,&j);
	
	char *word = (char *)malloc(sizeof(char)*MAX_WORD);
	int counter=0;
	while(ch[j]!='<' && ch[j]!=null && ch[j]!=' ' && ch[j]!='-' && ch[j]!='_' && ch[j]!='/'){
		word[counter++]=ch[j++];
		if(counter==MAX_WORD)
			break;
		
	}
	word[counter]=null;
	*i=j+1;
	
	//printf("the word is %ld\n\n",strlen(word));
	return word;
	

}
int isThereWord(char *buffer,int *i){
	
	int j=*i;
	traverseSpaces(buffer,&j);
//	printf("\nchecking for %c\n\n",buffer[j]);
	if(buffer[j]==null || buffer[j]=='<' || buffer[j]=='/'){
		*i=j;
		return 0;
	}
	return 1;
	


}
int isWordValid(char *word ){
	if(!strlen(word))
		return 0;
	
	int i=0;
	while(word[i]!=null){
		if((word[i]>='0' && word[i]<='9'))
			return 0;
		i++;
	}
	return 1;


}
int getHashValue(char *word){
	
	int ascii=0,i=0;
	while(word[i]!=null){
		
		ascii += word[i++];
	}
	
	//printf("ascii %d",ascii);
	return ascii%100;

}

theWords *getNewNode(char *word,char *url){

	theWords *node = (theWords *)malloc(sizeof(theWords));
	node->keyword = word;
	node->freq = 1;
	node->url = url;
	return node;
	

}
theWords *isSameWordOnUrl(char *word,char *url,hashTable ht[]){
	//printf("url = %s word = %s",url,word);
	int index = getHashValue(word);
//	printf("%d",index);
	theWords *ptr;
	if((ptr=ht[index].head)==NULL)
		return ptr;
	
	theWords *last = ht[index].last;
	
	do{
		if(strcmp(ptr->keyword,word) && strcmp(ptr->url,url)){
		
			return ptr;
		}
			
		ptr = ptr->next;
	}while(ptr!=last);
	
	return ptr=NULL;

}
void insertIntoList(char *word,char *url,theWords ***head,hashTable ht[]){
	
	//theWords *ptr = **head;
	theWords *ptr;
//	printf("checking");
	
	if(ptr = isSameWordOnUrl(word,url,ht)){
		ptr->freq += 1;
		return;
	
	}
	//return;
	else{
	printf("not same");
	}
	theWords *node = getNewNode(word,url);
	int index =  getHashValue(word);
	if(ht[index].head==NULL){
		ht[index].head = node;
	}
	else{
		
		ptr = **head;
		theWords *last;
		last = ht[index].last;
		do{
		
			ptr = ptr->next;
		}while(ptr!=last);
		
		//theWords *nextNode = ptr->next;
		node->next = ptr->next;
		ptr->next = node;
		
	
	}
	
	


}

char *getTheUrl(char *buffer){
	int i=0;
	int counter=0;
	while(!(buffer[i]=='U' && buffer[i+1]=='R' && buffer[i+2]=='L')){
		i++;
	}
	i += 6;
//	printf("\n##  %c  %c #\n\n",buffer[i],buffer[i+1]);
	char *url = (char *)malloc(sizeof(char)*100);
	while(buffer[i]!=' ')
		url[counter++]=buffer[i++];
	
	url[counter]=null;
	
	return url;
	

}
int extractTheWords(char *buffer,theWords **head,hashTable ht[]){

    int i=0;
  
	int counter=0;
	
	char *url;
	
	url = getTheUrl(buffer);
	printf("\n%s\n",url);
   
        if(findOpenAnchorTag(buffer,&i) ){
			
			while(isThereWord(buffer,&i)){
				
               int j=0;
				
         	   char *word;
			
			
         	   word = getTheWord(buffer,&i);
				
         	   if(isWordValid(word) ){
				 
			printf("%s \n",word);
				   insertIntoList(word,url,&head,ht);
				   
         	       counter++;
				   
					if(counter==MAX_LINKS_ALLOWED){
					
						break;
					}
			 	
				//  free(word);

          	  }
              else{//printf("err");
				 // printf("word invalid");
                free(word);}
				
			//	i += strlen(word)-1;
				
			
			}
			

        }
	else{
	//printf("err");
	}
		

		
    return counter;

}


void main(int argc,char *argv[]){
	
	hashTable ht[100];
	
	for(int i=0;i<100;i++)
		ht[i].head=NULL;
	
	
	theWords *head = NULL;
	char *files[500];
	
	int n; //n denotes number of files
	if(isValidDir(argv[1])){
		n=getAllTheFiles(argv[1],files);
		
		for(int i=0;i<n;i++){
		
			char fileName[100];
			sprintf(fileName,"%s/%s",argv[1],files[i]);
			printf("Reading File %s\n",fileName);
			
			free(files[i]);
			char *buffer;
			buffer = readTheFile(fileName);
			
			extractTheWords(buffer,&head,ht);
	
			printf("\n\n\n\n\n");
			
			free(buffer);
			break;
		
		}
		
		if(head==NULL)
			printf("head is null");
		theWords *ptr = head;
		for(;ptr!=NULL;ptr=ptr->next)
			printf("%-70s %s",ptr->url,ptr->keyword);
			
		
		
	
	}
	else{
	
		printf("\ninvalid directory");
	}





}
