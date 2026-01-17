//delete operation.
/*
 Steps to delete a Node
 1)if it is leaf node make it NULL or free.
 2)if it has one child left or right make it appropriate.
 3)if it has two children then replace it with inorder predecessor & free its inorder predecessor.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"bst.h"
#include"N.h"
#include"string_gen.h"

int main()
{
	Bintree b;
	char alpha[26],name[MAX_LENGTH+1],city[MAX_LENGTH+1];
	int age;
	int ch,k,count;
	long int record_ptr;
	clock_t start,end;

	Ele_i *entry;
	FILE *fdata;
	FILE *fsearch;
	
	if(!(fdata=fopen("sample.txt","r")))
	{
		printf("\nfailed to open data.txt file\n");
		return 0;
	}

	init_alpha(alpha);
	start = clock();
	printf("\ninsertion started i\n");
	printf("\nRand_max:%d\n",RAND_MAX);

	while(!feof(fdata))
	{
	//	k=rand()%1000000+1;//range between 1 to 1000000
		//k=rand();
	//	printf(" insert:%d ,",k);
		//printf(" insert:%s ,",name);
		//insert(&b,name);
		entry=(Ele_i*)malloc(sizeof(Ele_i));
		entry->ele=(char *)malloc(MAX_LENGTH+1);
		entry->record_ptr=ftell(fdata);
		fscanf(fdata,"%s %d %s\n",name,&age,city);
		strcpy(entry->ele,name);
		insert(&b,entry);
	
		//fprintf(fdata,"%s %d %s\n",name,age,city);
		free(entry->ele);
		free(entry);
		count++;
		if(count==N)
		break;
	}
	end  = clock();
	double time_taken =  ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\n\ntime taken for %d random number insertions  = %f seconds\n",count,time_taken);

	if(!(fsearch=fopen("search.txt","w")))
	{
		printf("\nfailed to open search.txt file\n");
		return 0;
	}
	if(!(fdata=fopen("sample.txt","r")))
	{
		printf("\nfailed to open data.txt file\n");
		return 0;
	}
	printf("\n height of tree:%d\n",height(b.root));

	start = clock();
	printf("\nNow for search:\n");
	for(int i=0;i<N;i++)
	{
		//k=rand()%1000000+1;//range between 1 to 1000000
		make_str(name,alpha);
		record_ptr=search(&b,name);
		if(record_ptr!=-1)
		{
			fseek(fdata,record_ptr,SEEK_SET);
			fscanf(fdata,"%s %d %s\n",name,&age,city);
			fprintf(fsearch,"%s %d %s\n",name,age,city);
		}	
	}
	end =clock();

	time_taken =  ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\ntime taken for %d random number searches  = %f seconds\n",count,time_taken);
	printf("\n height of tree:%d\n",height(b.root));

	/*
	do
	{
		printf("\n1)Insert:");
		printf("\n2)Delete:");
		printf("\n3)Traverse(Inorder):");
		printf("\n4)Exit:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("\nenter data to insert:\n");
			       scanf("%d",&n);
			       insert(&b,n);
			       break;
			case 2:printf("\nenter data to delete:\n");
			       scanf("%d",&n);
			       delete(&b,n);
			       break;
			case 3:inorder(b.root);
			       break;
			case 4:break;
		}
	}while(ch!=4);
*/

/*	insert(&b,4);
	printf("\nOH=%d\n",b.root->right==NULL);
	delete(b.root,4);
	printf("\nOH root=%d\n",b.root->ele);
*/
	return 0;

}
