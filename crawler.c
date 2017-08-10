#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINKS 1000
#define MAX_LINK_SIZE 200
#define MAX_LINKS_ALLOWED 5
#define MAX_SIZE_FOR_HASH 100

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

	return (n)%MAX_SIZE_FOR_HASH;

}

void insertAtBeg(LINKS ****head,LINKS *node){

	node->next = ***head;
	node->prev = NULL;
	***head = node;
}

void insertItAfter(LINKS *node,LINKS *head,int total){

	LINKS *NextNode;
	LINKS *prev = NULL;
	NextNode = head;
	//printf("\nv## alue of t is %d\n",total);
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

int isUnique(char *url,HashTable ht[MAX_SIZE_FOR_HASH]){
	
	int index = getHashCode(strlen(url));
	LINKS *ptr = ht[index].head;
	int t = ht[index].total;
	
	//printf("\nvalue of t is %d\n",t);
	for(int i=0;i<t;i++){
	//	printf("\n## %s %s ##\n",ptr->link,url);
		if(!strcmp(ptr->link,url))
			return 0;
		ptr=ptr->next;
	}
	return 1;

}
void insertInList(char *link,char *seedUrl,int depth,LINKS ***head,HashTable ht[MAX_SIZE_FOR_HASH]){

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
		printf("\nlink %-60s isVisited %d \n",node->link,node->isVisited);
		//printf("%s",(*head)->link);
		return;
	}
	

	
	
	
//	ht[index].total += 1;
	
	insertItAfter(node,ht[index].head,ht[index].total);
	
	ht[index].total +=1;
	
	
	
	printf("\nlink %-60s isVisited %d \n",node->link,node->isVisited);
	
	

}


int printAll(LINKS **head){
	
	LINKS *ptr;
	int noOfLinks=0;
	ptr = *head;
	while(ptr!=NULL){
		printf("link = %-100s  depth = %d    isVisited=%d\n",ptr->link,ptr->depth,ptr->isVisited);
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
//	printf("\n\nfileread  $$$$%s add is %u\n\n ",fileName,fileName);
	
	
    fp = fopen(fileName,"rb");
	//printf("\n\nfileread  $$$$%s add is %u\n\n ",fileName,fileName);
	//	printf("fileread");

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

         if(!((ch[i]>='a' && ch[i]<='z') || (ch[i]>='A' && ch[i]<='Z') || ch[i]=='.' || ch[i]==':' || ch[i]=='-' || ch[i]=='/' || (ch[i]>='0' && ch[i]<='9')) || 
				ch[i]=='p' && ch[i+1]=='d' && ch[i+2]=='f' && ch[i+3]==null && printf("\n####PDF FOUND#####\n") || (ch[i]=='j' && ch[i+1]=='p' && ch[i+2]=='g' && ch[i+3]==null) ||
		   		(ch[i]=='j' && ch[i+1]=='p' && ch[i+2]=='e' && ch[i+3]=='g' && ch[i+4]==null)|| (ch[i]=='p' && ch[i+1]=='n' && ch[i+2]=='g' && ch[i+3]==null)){

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
int extractTheLinks(char *buffer,char *seedUrl,int depth,char *linkArr[],HashTable ht[]){

    int i=0;
  
	int counter=0;
	
    while(buffer[i]!=null){

        if(findOpenAnchorTag(buffer,&i) && traverseUntilHref(buffer,&i)){

            int j=0;
            char *word;
			
			
            word = getTheLink(buffer,&i);
            if(isLinkValid(word) && (j=closingAnchorTagPresent(buffer,i))  && isBaseCorrect(word,seedUrl) &&  isUnique(word,ht)){
				
                i=j;

                linkArr[counter] =  word;
				
				//insertInList(word,seedUrl,depth,&head,ht);
				
				
                counter++;
				if(counter==MAX_LINKS_ALLOWED){
					
					break;
				}
				
				

            }
            else
                free(word);

        }


        i++;
    }

    return counter;

}



/*##########################################################################################################################################*/
char *downloadTheHtmlFile(char *url,char *dir,int depth,int isSeed,char *seedUrl,int flag){
	
	static int fileCounter=0;
	printf("############DOWNLOADING FILE####################\n");
	char *command = malloc(sizeof(char)*200);
	
	char *fileName;
	
	char *space = " ";
	
	
	fileName = (char *)malloc(sizeof(char)*130);
	sprintf(fileName,"%s/temp.txt",dir);
	
	//if(!flag)
		sprintf(command,"wget -O ");
	//else
		//sprintf(command,"wget -b -O ");
	
	//strcat(command,dir);
	
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
	//	sprintf(fileName,"%s/index%d_%d.html",dir,fileCounter,depth);
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
/*
void downloadFilesFromList(char *dir,LINKS **head){
	
	LINKS *temp = *head;
	LINKS *temp2;

	char *fname;
	while(temp!=NULL){
		if(!temp->isVisited){
		    fname = downloadTheHtmlFile(temp->link,dir,temp->depth,0,temp->seedUrl);
			free(fname);
		}
		temp=temp->next;
		
		
	}
	temp=*head;
	while(temp!=NULL){
		temp2=temp;
		free(temp->link);
		temp=temp->next;
		
		free(temp2);
	}


}*/
void crawlItBaby(char *seedUrl,char *url,char *dir,int depth,LINKS **head,HashTable ht[]){

	char *linksArr[MAX_LINKS_ALLOWED];
	if(!depth){
		return;
		
	}
	printf("#########################CRAWLING START for %s with depth %d##############################\n",url,depth);
	char *ch;
	char *file;
	char *html;
	int success=0;
	
	// 1 is for seed url and 0 is  a neccessary evil
	file=downloadTheHtmlFile(url,dir,depth,1,seedUrl,0);

	

	html = readTheFile(file);
	
	free(file);


	
    success = extractTheLinks(html,seedUrl,depth,linksArr,ht);

	for(int i=0;i<success;i++)
		insertInList(linksArr[i],url,depth,&head,ht);	
	

	
	
	free(html);
    printf("\nlinks found++++++ were %d\n\n",success);

    if(!success){
        printf("\nno links were found\n");
    }

	
	LINKS *temp;
	temp = *head;
	
	char *name;
	
	if(depth==1){
		
		for(int i=0;i<success;i++){
			name = downloadTheHtmlFile(linksArr[i],dir,depth,0,url,1);
			free(name);
		}
		return;
	}
	
	while(temp!=NULL){
		if(temp->isVisited==0){
			if((temp->depth)-1>=1 && temp->depth==depth){
				temp->isVisited=1;
			
			crawlItBaby(seedUrl,temp->link,dir,depth-1,head,ht);
			
			}
		}
		temp=temp->next;
	
	}
	
	

	
	
	
}
void main(int argc,char *argv[]){
	
	int depth;
	char linkCounter=0;
	LINKS *head = NULL;
	HashTable ht[MAX_SIZE_FOR_HASH];
	
	for(int i=0;i<MAX_SIZE_FOR_HASH;i++)
		ht[i].total=0;

	if(isValidUrl(argv[1])){
		
		if(isValidDir(argv[2])){
			
			if(depth=isValidDepth(argv[3])){
			
				printf("###################ENGINE STARTING######################################\n\n\n");
				crawlItBaby(argv[1],argv[1],argv[2],depth,&head,ht);
				printf("\n\nLINKS FOUND %d\n\n",printAll(&head));
			//	downloadFilesFromList(argv[2],&head);
				int counter=0;
				for(int i=0;i<MAX_SIZE_FOR_HASH;i++)
					if(ht[i].total>0)
						counter++;
				printf("\n\n_______________%d______________\n",counter);
				FILE *fp;
				fp = fopen("fileLINKS.txt","w");
			/*	for(LINKS *temp=head;temp!=NULL;temp=temp->next){
					
					char *link = temp->link;
					char ch;
					int i=0;
					while((ch=link[i++])!='\0')
						fputc(ch,fp);
					
					
					
					fputc('\n',fp);
					
				
						  
						  }
					
					*/
				fclose(fp);
				LINKS *t = head;
				for(LINKS *temp=head;temp!=NULL;){
					t=temp;
					temp=temp->next;
					free(t->link);
					free(t);
					
				}
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
