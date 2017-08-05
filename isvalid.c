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

int isValidUrl(char *url){
	
	char *command = (char *)malloc(sizeof(char)*1000);
	char *first;
	//printf(\n"url in isValidUrl"\n);
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

         if(!((ch[i]>='a' && ch[i]<='z') || (ch[i]>='A' && ch[i]<='Z') || ch[i]=='.' || ch[i]==':' || ch[i]=='-' || ch[i]=='/' || (ch[i]>='0' && ch[i]<='9')) ){

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

int isUnique(char *links[MAX_LINKS],int linkCounter,char *word){


    for(int i=0;i<linkCounter;i++)
	if(!strcmp(links[i],word))
		return 0;
	
    return 1;

    

}
int isBaseCorrect(char *word,char *base){
	for(int i=0;base[i]!=null;i++){
		if(word[i]!=base[i])
			return 0;
	}
	return 1;

}
int extractTheLinks(char *buffer,char *link[MAX_LINKS],int linkCounter){

    int i=0;
    int c=1;
    while(buffer[i]!=null){

        if(findOpenAnchorTag(buffer,&i) && traverseUntilHref(buffer,&i)){

            int j=0;
            char *word=(char *)malloc(sizeof(char)*MAX_LINK_SIZE);
            word = getTheLink(buffer,&i);
            if(isLinkValid(word) && (j=closingAnchorTagPresent(buffer,i)) && isUnique(link,linkCounter,word) && ( linkCounter? isBaseCorrect(word,link[0]): 1)){

                i=j;

                link[linkCounter] =  word;
                linkCounter++;

            }
            else{}
             //   free(word);

        }


        i++;
    }
    return linkCounter;



}



/*##########################################################################################################################################*/
char *downloadTheHtmlFile(char *url,char *dir,int counter){
	
	printf("############DOWNLOADING FILE####################\n");
	char *command = malloc(sizeof(char)*200);
	printf("\ngibving add t caommand %u\n",command);
	char *fileName;
	
	char *space = " ";
	fileName = (char *)malloc(sizeof(char)*100);
	printf("\ngiving ch add %u\n",fileName);
	sprintf(fileName,"/index%d.html",counter);
	
	

	sprintf(command,"wget -O ");
	
	strcat(command,dir);
	
	//printf("url in download function is %s",url);
	
	strcat(command,fileName);
	strcat(command,space);
	strcat(command,url);
	system(command);
	
	free(command);

	
	printf("############ FILE DOWNLOADED	####################\n");
	
	return fileName;

}

void crawlItBaby(char *url,char *dir,int depth,char *links[MAX_LINKS],int counter){

	if(!depth){
		for(int i=0;i<counter;i++)
      printf("%3d %s\n",i+1,links[i]);
		return;

	}
	printf("#########################CRAWLING START for url %s##############################\n",url);
	char *ch;
	char *file;
	char *html;
	int success=0;
	
	ch=downloadTheHtmlFile(url,dir,depth);

	file = malloc(sizeof(char)*(strlen(ch)+strlen(dir)+10));
    
	sprintf(file,"%s",dir);
	strcat(file,ch);

	
	
	printf("\nfile saved %s\n ",file);
	

	printf("calling readFunction %s \n",file);
	
	html = readTheFile(file);
	printf("\nfffreeing file\n");
	free(file);
	printf("\nfffreed file\n");	   
		   
	
	printf("called readFunction");

	
    success = extractTheLinks(html,links,counter);
printf("\nfreeing html\n");
	free(html);
	   printf("\nfreed html\n");
    printf("links found++++++ were %d\n\n",success);


    if(!success){
        printf("no links were found");
    }

		printf("\nfreeing ch\n");
	printf("\ngiving ch add %u\n",ch);
	free(ch);
		   printf("\nffffreed ch\n");
	
	//fflush(stdin);
	crawlItBaby(links[counter+1],dir,depth-1,links,success);
	

	
	
	
}
void main(int argc,char *argv[]){
	
	int depth;
	char linkCounter=0,*links[MAX_LINKS];


	
	if(isValidUrl(argv[1])){
		
		if(isValidDir(argv[2])){
			
			if(depth=isValidDepth(argv[3])){
				printf("###################ENGINE STARTING######################################\n\n\n");
				crawlItBaby(argv[1],argv[2],depth,links,linkCounter);
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