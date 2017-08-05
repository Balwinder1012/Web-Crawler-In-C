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

char *downloadTheHtmlFile(int counter){
	
	printf("############DOWNLOADING FILE####################\n");
	char *command = malloc(sizeof(char)*200);
	printf("\ngibving add t caommand\n");
	char *fileName;
	
	char *space = " ";
	fileName = (char *)malloc(sizeof(char)*100);
	printf("\ngiving ch add \n");
	sprintf(fileName,"/index%d.html",counter);
	
	

	sprintf(command,"wget -O ");
	
	//strcat(command,dir);
	
	//printf("url in download function is %s",url);
	
	strcat(command,fileName);
	strcat(command,space);
	//strcat(command,url);
//	system(command);
	printf("\nfreeing command \n");
	free(command);
	printf("\n freed command\n");
	
	printf("############ FILE DOWNLOADED	####################\n");
	
	return fileName;

}

int main(){

	char *u;
	u = downloadTheHtmlFile(1);
	free(u);
	u = downloadTheHtmlFile(2);
	free(u);
	u = downloadTheHtmlFile(1);
	free(u);
	u = downloadTheHtmlFile(2);
	free(u);
	u = downloadTheHtmlFile(1);
	free(u);
	u = downloadTheHtmlFile(2);
	free(u);
	u = downloadTheHtmlFile(1);
	free(u);
	u = downloadTheHtmlFile(2);
	free(u);
	return 0;
	
}