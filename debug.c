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

char* readTheFile(){
	
    FILE *fp;
    char *buffer;
    long long int length;
//	printf("\n\nfileread  $$$$%s add is %u\n\n ",fileName,fileName);
	
	
    fp = fopen("theDir/seedForDepth2.html","rb");
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
        printf("\n\n######################Error in reading the file $\n\n");

	
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
int extractTheLinks(char *buffer,char *linkArr[MAX_LINKS],char *seedUrl){

    int i=0;
  
	int counter=0;
	
    while(buffer[i]!=null){

        if(findOpenAnchorTag(buffer,&i) && traverseUntilHref(buffer,&i)){

            int j=0;
            char *word;
			
			
            word = getTheLink(buffer,&i);
            if(isLinkValid(word) && (j=closingAnchorTagPresent(buffer,i))  && isBaseCorrect(word,seedUrl)){
				
                i=j;

                linkArr[counter] =  word;
				   
                counter++;
				if(counter==MAX_LINKS_ALLOWED){
					printf("\nbreaking %d\n",MAX_LINKS_ALLOWED);
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



int main(){

	char *s = (char *)malloc(sizeof(char)*100);
	char *links[MAX_LINKS];
	char *buffer;
	sprintf(s,"mmumullana.org");
	buffer = readTheFile();
	//puts(buffer);
	printf("%d",extractTheLinks(buffer,links,s));
	//puts(s);
}