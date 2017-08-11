#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define null '\0'
#define MAX_DEPTH '3' 
#define MAX_LINK_SIZE 80
#define MAX_LINKS_ALLOWED 3
#define MAX_HASH_SIZE 100

int main(){

	char *a = malloc(sizeof(char)*10);
	
	a[12]='b';

}