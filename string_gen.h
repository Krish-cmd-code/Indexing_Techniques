#include<stdio.h>
#include<stdlib.h>
#include"N.h"


void init_alpha(char alpha[SIZE])
{
	int j=97,i=0;	
	while(j<123)
	alpha[i++]=j++;
}

void make_str(char *name,char alpha[SIZE])
{
	int str_length = 1+(int)(MAX_LENGTH*(rand()/(RAND_MAX+1.0)));
	name[str_length]='\0';
	int x;
	int i=0;
	while(i<str_length)
	{
		x=(int)(26*(rand()/(RAND_MAX+1.0)));
		name[i++]=alpha[x];
	}
}

void make_age(int *age)
{
	*age = rand()%AGE_LIMIT+1;
}



