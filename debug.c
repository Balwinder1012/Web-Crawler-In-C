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


void swap(char *a,char *b){

	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
	

}
void permute(char ch[],int l,int r){

		if(l==r)
			printf("%s \n",ch);
		else{
		
			for(int i=l;i<=r;i++){
				swap(&ch[l],&ch[i]);
				permute(ch,l+1,r);
				swap(&ch[l],&ch[i]);
			
			}
		}
		

}
int main(){

	char ch[80];
	scanf("%s",ch);
	
	permute(ch,0,strlen(ch)-1);

}