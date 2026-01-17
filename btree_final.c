#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include"N.h"
#include"btree_insert.h"
#include"string_gen.h"



int main()
{
	int ch;
	char name[MAX_LENGTH+1],alpha[26];
	char city[MAX_LENGTH+1];
	int age;
	long int record_ptr;
	int count;
	BTree *T;
	T=(BTree*)malloc(sizeof(BTree));
	pair *find=(pair*)malloc(sizeof(pair));
	Node *x=(Node*)malloc(sizeof(Node));
	B_Tree_Create(T);
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
	start=clock();
	printf("\ninsertion started\n");
	printf("\nrand_Max:%d",RAND_MAX);

	count=0;
	while(!feof(fdata))
	{
		//k=rand()%1000000+1;//range between 1 to 1000000
		//k=rand();
//		printf(" insert:%d,",k);
		entry=(Ele_i*)malloc(sizeof(Ele_i));
		entry->key=(char*)malloc(MAX_LENGTH+1);
		entry->record_ptr=ftell(fdata);
		fscanf(fdata,"%s %d %s\n",name,&age,city);
		strcpy(entry->key,name);

		B_Tree_Insert(T,entry);
		free(entry->key);
		free(entry);
		count++;
	}
	end = clock();

	double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\ntime taken for %d random number insertions = %f seconds\n",count,time_taken);
	printf("\nheight of BTree is: %d\n\n",T->height);

	if(!(fsearch=fopen("search.txt","w")))
	{	
		printf("\nfailed to open search.txt file\n");
		return 0;
	}
	if(!(fdata=fopen("sample.txt","r")))
	{
		printf("\nfailed to open sample.txt file for reading\n");
		return 0;
	}
	start=clock();
	printf("\nNow for searches\n");
	for(int i=0;i<count;i++)
	{
	//	k=rand()%1000000+1;
		make_str(name,alpha);
		find=B_Tree_Search(T->root,name);
		if(find!=NULL)
		{
			record_ptr=find->x->entry[find->i].record_ptr;
			fseek(fdata,record_ptr,SEEK_SET);
			fscanf(fdata,"%s %d %s\n",name,&age,city);
			fprintf(fsearch,"%s %d %s\n",name,age,city);
		}
		
	}
	end =clock();
	time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\ntime taken for %d random number searches = %f seconds\n",count,time_taken);
	printf("\nheight of BTree is: %d\n\n",T->height);
/*
	B_Tree_Traversal(T->root);
*/


	/*
	printf("\nbrefore insert x->n:%d\n",T->root->n);
	B_Tree_Insert(T,23);
	printf("\nafter insert x->n:%d\n",T->root->n);
        Delete_B_Tree(T,23);
	printf("\nafter deletion x->n:%d\n",T->root->n);
	B_Tree_Insert(T,53);
	*/
	/*
	do{
		printf("\n1.insert\n2.search\n3.traversal\n4.delete\n5.exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("\nenter key to insert:");
			       scanf("%d",&k);
			       B_Tree_Insert(T,k);
			       break;

			case 2:printf("\nenter key to be searched:");
			       scanf("%d",&k);
			       find=B_Tree_Search(T->root,k);
			       if(find==NULL)
				       printf("\nnot found...");
			       else
				printf("\nfound!!!");
			       break;
			case 3:printf("\ntraversing:");
			       B_Tree_Traversal(T->root);
			       break;
			case 4:printf("\nenter key to be deleted:");
			       scanf("%d",&k);
			       Delete_B_Tree(T,k);
			       
			       break;
			case 5:printf("\nprogram gets terminated\n");
			       break;
	   	}
	}while(ch!=5);
	*/
	return 0;

}
