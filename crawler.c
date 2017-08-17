#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
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
void insertInList(char *link,char *seedUrl,int depth,LINKS ***head,HashTable ht[]){

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
		node->next = **head;
		node->prev=NULL;
		if((**head)!=NULL)
		(**head)->prev=node;
		**head=node;
		return;
	
	
	}
	
	
	
	
	LINKS *ptr;
	ptr = ht[index].head;
	
	insertItAfter(ptr,node,ht[index].total);
	ht[index].total += 1;


}
int printAll(LINKS **head){
	
	LINKS *ptr;
	int noOfLinks=0;
	ptr = *head;
	while(ptr!=NULL){
		printf("link = %-70s  depth = %d  %s\n",ptr->link,ptr->depth,ptr->seedUrl);
		noOfLinks++;
		ptr=ptr->next;
	}

	return noOfLinks;
	
}

int isValidUrl(char *url){
	
	char *command = (char *)malloc(sizeof(char)*1000);
	char *first;
	first = "wget --spider ";
	strcpy(command,first);
	strcat(command,url);
	if(!system(command)){
		free(command);
		return 1;
	}
	else{
		
		free(command);
		return 0;
	}

}
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
int isValidDepth(char *depth){
	
	int length = strlen(depth);
	if(length>2)
		return 0;
	else{
		if( depth[0] >='1' && depth[0]<=MAX_DEPTH)
			return depth[0]-'0';
		
		else
			return 0;
	}


}

/*##########################################################################################################################################*/



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


int isFile(char *ch,int i){

	if(  (ch[i]=='p' && ch[i+1]=='d' && ch[i+2]=='f' && ch[i+3]==null && printf("\n####PDF FOUND#####\n")) || (ch[i]=='p' && ch[i+1]=='n' && ch[i+2]=='g' && ch[i+3]==null && printf("\n####PNG FOUND#####\n")) ||
	     
	   		(ch[i]=='j' && ch[i+1]=='p' && ch[i+2]=='g' && ch[i+3]==null && printf("\n####JPG FOUND#####\n")) || (ch[i]=='g' && ch[i+1]=='i' && ch[i+2]=='f' && ch[i+3]==null && printf("\n####GIF FOUND#####\n")) ||
     	    (ch[i]=='j' && ch[i+1]=='p' && ch[i+2]=='e' && ch[i+3]=='g' && ch[i+4]==null && printf("\n####PDF FOUND#####\n")) || 
	  		(ch[i]=='z' && ch[i+1]=='i' && ch[i+2]=='p' && ch[i+3]==null && printf("\n####ZIP FOUND#####\n"))	||
	  		(ch[i]=='r' && ch[i+1]=='a' && ch[i+2]=='r' && ch[i+3]==null && printf("\n####RAR FOUND#####\n")) )
		return 1;
	return 0;

}
int findOpenAnchorTag(char *ch,int *i){

    int j=*i;

    while(!(ch[j]=='<' && ch[j+1]=='a')){
        if(ch[j]==null){
            *i=j;
            return 0;
        }

        j++;

    }
    *i = j;
    return 1;



}

void traverseSpaces(char ch[],int *j){
    while(ch[*j]==' ')
        *j = *j + 1;
}
int traverseUntilHref(char ch[],int *i){
    int j=*i;
    while(ch[j]!=null){

        if(ch[j]=='h' && ch[j+1]=='r' && ch[j+2]=='e' && ch[j+3]=='f'){
            j=j+4;
            traverseSpaces(ch,&j);

            if(ch[j]=='='){
                j++;
                traverseSpaces(ch,&j);
                if(ch[j]=='"'){
                    j++;
                    *i=j;
                    return j;

                }
                else
                    return 0;



            }
            else
                return 0;

        }
        j++;

    }




}
char* getTheLink(char *ch,int *i){

    char *word = malloc(sizeof(char)*MAX_LINK_SIZE);
    int index=0;

    while(ch[*i]!=null && ch[*i]!='"'){

        word[index++]=ch[*i];
        *i = *i +1;
		if(index==MAX_LINK_SIZE){
			word[0]='\0';
			return word;
		}
    }
    if(ch[*i]=='"'){
        word[index]=null;

        *i=*i+1;

        return word;
    }
    else{

        word=null;
        return word;
    }
}

int isLinkValid(char *ch){

    if(ch[0]==null)
        return 0;
    int i=0;
    while(ch[i]!=null){

         if(!((ch[i]>='a' && ch[i]<='z') || (ch[i]>='A' && ch[i]<='Z') || ch[i]=='.' || ch[i]==':' || ch[i]=='-' || ch[i]=='/' || (ch[i]>='0' && ch[i]<='9')) || isFile(ch,i)){

            return 0;
         }
         i++;
    }
    return 1;


}
int closingAnchorTagPresent(char *ch,int i){

    while(ch[i]!=null && !(ch[i]=='<' && ch[i+1]=='/' && ch[i+2]=='a' && ch[i+3]=='>')){

        if((ch[i]=='<' && ch[i+1]=='a' )|| (ch[i]=='b' && ch[i+1]=='o' && ch[i+2]=='d' && ch[i+3]=='y' ))
            return 0;

        i++;
    }
    if(ch[i]==null)
        return 0;

    //this will move the index to a position right after closing tag
    return i+4;


}

int isUniqueInList(int key,char *url,HashTable ht[]){
	
	int index = getHashCode(key);
	int total = ht[index].total;
	LINKS *ptr = ht[index].head;
	for(int i=0;i<total;i++){
		
		if(!strcmp(ptr->link,url))
			return 0;
		ptr = ptr->next;
	
	}
	return 1;


}

int isBaseCorrect(char *word,char *base){
	
	int i=0;
	int k=0;
	while((word[i]!=null && word[i]!='/' && word[i+1]!='/' ))
		i++;
	k=i;
	
	i=i+3;

	
	if(word[i]=='w' && word[i+1]=='w' && word[i+2]=='w' && word[i+3]=='.')
		i = i +4;
	
	
	for(int j=0;base[j]!=null;j++){
		if(word[i++]!=base[j] || abs(strlen(base)+7-strlen(word))<2)
			return 0;
	}
	return 1;

}
int extractTheLinks(char *buffer,char *linkArr[MAX_LINKS_ALLOWED],char *seedUrl,HashTable ht[]){

    int i=0;
  
	int counter=0;
	
    while(buffer[i]!=null){

        if(findOpenAnchorTag(buffer,&i) && traverseUntilHref(buffer,&i)){

            int j=0;
            char *word;
			
			
            word = getTheLink(buffer,&i);
            if(isLinkValid(word) && (j=closingAnchorTagPresent(buffer,i))  && isBaseCorrect(word,seedUrl) && isUniqueInList(strlen(word),word,ht)){
				
                i=j;

                linkArr[counter] =  word;
				   
                counter++;
				if(counter==MAX_LINKS_ALLOWED){
					
					break;
				}
				
				

            }
            else
                free(word);

        }


		if(buffer[i]==null)
			break;
        i++;
    }

    return counter;

}



/*##########################################################################################################################################*/
char *downloadTheHtmlFile(char *url,char *dir,int depth,char *seedUrl){
	
	static int fileCounter=0;
	printf("############DOWNLOADING FILE####################\n");
	char *command = malloc(sizeof(char)*200);
	
	char *fileName;
	
	char *space = " ";
	
	
	fileName = (char *)malloc(sizeof(char)*130);
	sprintf(fileName,"%s/temp.txt",dir);
	
	
	sprintf(command,"wget -O ");

	strcat(command,fileName);
	strcat(command,space);
	strcat(command,url);
	system(command);
	
	
	FILE *fp;
	fp = fopen(fileName,"r");
	
		sprintf(fileName,"%s/index%d_%d.html",dir,(++fileCounter),depth);
	
	
	char *appendThisString = (char *)malloc(sizeof(char)*300);
	sprintf(appendThisString,"<!--URL - %s ## Depth - %d ## SeedUrl - %s-->\n\n",url,depth,seedUrl);
	if(fp){
		
		FILE *newFile;

		newFile = fopen(fileName,"w");
		
		char ch;
		int i=0;
		while(appendThisString[i]!=null)
			fputc(appendThisString[i++],newFile);
		
		while((ch=fgetc(fp))!=EOF)
			fputc(ch,newFile);
		
		free(appendThisString);
		fclose(newFile);
		fclose(fp);
	
	}
	else{
		printf("\nerror in opening file\n");
		
	}
	
	
	free(command);

	
	printf("############ FILE %-20s DOWNLOADED	####################\n",fileName);
	
	return fileName;

}
char *downloadTheHtmlFile1(char *url,char *dir,int depth,char *seedUrl){
	
	static int fileCounter=0;
	printf("############DOWNLOADING FILE####################\n");
	char *command = malloc(sizeof(char)*200);
	
	char *fileName;
	
	char *space = " ";
	
	
	fileName = (char *)malloc(sizeof(char)*130);
	sprintf(fileName,"%s/temp.txt",dir);
	
	
	sprintf(command,"wget -b -O ");

	strcat(command,fileName);
	strcat(command,space);
	//strcat(command,);
	strcat(command,url);
	system(command);
	
	
	FILE *fp;
	fp = fopen(fileName,"r");
	
		sprintf(fileName,"%s/index%d_%d.html",dir,(++fileCounter),depth);
	
	
	char *appendThisString = (char *)malloc(sizeof(char)*300);
	sprintf(appendThisString,"<!--URL - %s ## Depth - %d ## SeedUrl - %s-->\n\n",url,depth,seedUrl);
	if(fp){
		
		FILE *newFile;

		newFile = fopen(fileName,"w");
		
		char ch;
		int i=0;
		while(appendThisString[i]!=null)
			fputc(appendThisString[i++],newFile);
		
		while((ch=fgetc(fp))!=EOF)
			fputc(ch,newFile);
		
		free(appendThisString);
		fclose(newFile);
		fclose(fp);
	
	}
	else{
		printf("\nerror in opening file\n");
		
	}
	
	
	free(command);

	
	printf("############ FILE %-20s DOWNLOADED	####################\n",fileName);
	
	return fileName;

}


void crawlItBaby(char *seedUrl,char *url,char *dir,int depth,LINKS **head,HashTable ht[],char *baseUrl){

	char *linksArr[MAX_LINKS_ALLOWED];
	if(!depth){
		return;
		
	}
	printf("#########################CRAWLING START for %s with depth %d##############################\n",url,depth);
	char *ch;
	char *file;
	char *html;
	int success=0;
	
	
	file=downloadTheHtmlFile(url,dir,depth,seedUrl);

	

	html = readTheFile(file);
	
	free(file);


	
    success = extractTheLinks(html,linksArr,baseUrl,ht);

	for(int i=0;i<success;i++){
			printf("\n\n%-60s %s",linksArr[i],seedUrl);
			insertInList(linksArr[i],url,depth,&head,ht);
	}
	
	
	
	free(html);
    printf("\n\n\nlinks found were %d  \n\n",success);

    if(!success){
        printf("\nno links were found\n");
    }
	
	if(depth==1){
	
		for(int i=0;i<success;i++){
			char *n = downloadTheHtmlFile(linksArr[i],dir,depth,url);
			free(n);
			
			
		}
		return;
	
	}
	
	for(int i=0;i<success;i++){
		crawlItBaby(url,linksArr[i],dir,depth-1,head,ht,baseUrl);
	}
	
	
	
	
}
void main(int argc,char *argv[]){
	
	//clock_t t;
    //t = clock();
	
	int depth;
	char linkCounter=0;
	HashTable ht[MAX_HASH_SIZE];
	LINKS *head=NULL;
	
	for(int i=0;i<MAX_HASH_SIZE;i++)
		ht[i].total=0;

	if(isValidUrl(argv[1])){
		
		if(isValidDir(argv[2])){
			
			if(depth=isValidDepth(argv[3])){
			
				printf("###################ENGINE STARTING######################################\n\n\n");
				crawlItBaby(argv[1],argv[1],argv[2],depth,&head,ht,argv[1]);
				printf("LINKS FOUND %d\n\n",printAll(&head));
				/*
				for(LINKS *ptr=head;ptr!=NULL;){
					LINKS *temp = ptr;
					free(temp->link);
					ptr = ptr->next;
					free(temp);
				}
				*/
				/* t = clock() - t;
   				 double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
   				 printf("\n\nCrawler took %f seconds to execute \n", time_taken);*/
				exit(1);
			}
			else
				printf("\ninvalid depth --Depth should be greater than 0 and less than %d\n",(MAX_DEPTH-'0') + 1);
			
		
		}
		else
			printf("\ninvalid directory");
		
		
	}
	else
		printf("\nurl is not valid");

}
