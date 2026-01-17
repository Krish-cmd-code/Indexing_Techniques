//delete operation.
/*
 Steps to delete a Node
 1)if it is leaf node make it NULL or free.
 2)if it has one child left or right make it appropriate.
 3)if it has two children then replace it with inorder predecessor & free its inorder predecessor.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"N.h"

typedef struct Element_info{
	KEY_TYPE ele;
	long int record_ptr;
}Ele_i;
typedef struct node{
	//int ele;
	char ele[MAX_LENGTH+1];
	Ele_i entry;
	//KEY_TYPE ele;
	struct node *left;
	struct node *right;
}Node;

typedef struct tree{
	Node *root;
}Bintree;

Node* NewNode(KEY_TYPE data);
void insert(Bintree *b,Ele_i *data);

Bintree init(KEY_TYPE data)
{
	Node *newnode=NewNode(data);
	Bintree *B= (Bintree*)malloc(sizeof(Bintree));
	B->root=newnode;
	return *B;
}

void CopyNodeData(Node *target,Node *src)
{
	strcpy(target->ele,src->ele); //as key_type is char*

	strcpy(target->entry.ele,src->entry.ele); //as key_type of ele is char*
	target->entry.record_ptr=src->entry.record_ptr;
}


/*
void insert(Bintree *b,KEY_TYPE data)
{
	Node *parent;
	Node *newnode=NewNode(data);
	Node *temp=b->root;
	parent = NULL;
	while(temp!=NULL)
	{
		parent=temp;
		//if(temp->ele>=data)
		if(strcmp(temp->ele,data)>=0)
		{temp=temp->left;}
		//else if(temp->ele<data)
		else if(strcmp(temp->ele,data)<0)
		{temp=temp->right;}
		//else if(temp->ele==data)
		else if(strcmp(temp->ele,data)==0)
		{printf("\nduplicate");return;}
	}
	if(parent==NULL)
	{
		b->root=newnode;//printf("\ninserted at root %d",newnode->ele);
	}
	//else if(data < parent->ele)
	else if(strcmp(data,parent->ele)<0)
	{
		parent->left=newnode;//printf("\ninserted at left %d",newnode->ele);
	}
	//else if(data > parent->ele)
	else if(strcmp(data,parent->ele)>=0)
	{
		parent->right=newnode;//printf("\ninserted at right %d",newnode->ele);
	}
	return;
}
*/

void insert(Bintree *b,Ele_i *data)
{
	Node *parent;

	Node *newnode=NewNode(data->ele);
	newnode->entry.record_ptr=data->record_ptr;

	Node *temp=b->root;
	parent = NULL;
	while(temp!=NULL)
	{
		parent=temp;
		//if(temp->ele>=data)
		if(strcmp(temp->entry.ele,data->ele)>=0)
		{temp=temp->left;}
		//else if(temp->ele<data)
		else if(strcmp(temp->entry.ele,data->ele)<0)
		{temp=temp->right;}
		//else if(temp->ele==data)
		else if(strcmp(temp->entry.ele,data->ele)==0)
		{printf("\nduplicate");return;}
	}
	if(parent==NULL)
	{
		b->root=newnode;//printf("\ninserted at root %d",newnode->ele);
	}
	//else if(data < parent->ele)
	else if(strcmp(data->ele,parent->entry.ele)<0)
	{
		parent->left=newnode;//printf("\ninserted at left %d",newnode->ele);
	}
	//else if(data > parent->ele)
	else if(strcmp(data->ele,parent->entry.ele)>=0)
	{
		parent->right=newnode;//printf("\ninserted at right %d",newnode->ele);
	}
	return;
}

/*
int search(Bintree *b,KEY_TYPE data)
{
	Node *parent;
//	Node *newnode=NewNode(data);
	Node *temp=b->root;
	parent = NULL;
	while(temp!=NULL)
	{
		parent=temp;
		//if(temp->ele>data)
		if(strcmp(temp->ele,data)>0)
		{temp=temp->left;}
		//else if(temp->ele<data)
		else if(strcmp(temp->ele,data)<0)
		{temp=temp->right;}
		//else if(temp->ele==data)
		else if(strcmp(temp->ele,data)==0)
		{
		//	printf("\nfound");
			return 1;
		}
		else 
		return 0;
	}
	//printf("\nnotfound");
	return 0;
}
*/

long int search(Bintree *b,KEY_TYPE data)  //on success it will return record_ptr., otherwise -1.
{
	Node *parent;
	Node *temp=b->root;
	parent = NULL;
	while(temp!=NULL)
	{
		parent=temp;
		//if(temp->ele>data)
		if(strcmp(temp->entry.ele,data)>0)
		{temp=temp->left;}
		//else if(temp->ele<data)
		else if(strcmp(temp->entry.ele,data)<0)
		{temp=temp->right;}
		//else if(temp->ele==data)
		else if(strcmp(temp->entry.ele,data)==0)
		{
		//	printf("\nfound");
			//return 1;
			return temp->entry.record_ptr;
		}
		else 
		return -1;
	}
	//printf("\nnotfound");
	return -1;
}

void inorder(Node *temp)
{
	if(temp!=NULL)
	{	
	inorder(temp->left);
	//printf(" %s",temp->ele);
	printf(" %s",temp->entry.ele);
	inorder(temp->right);
	}
	printf("\n");
	return;
}
int max(int a,int b)
{
	if(a>b)
	return a;
	else
	return b;
}

int height(Node *root)
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		return 1+max(height(root->left),height(root->right));
	}
}

Node* NewNode(KEY_TYPE data)
{
	Node *temp=(Node*)malloc(sizeof(Node));
	//strcpy(temp->ele,data);

	temp->entry.ele=(char*)malloc(MAX_LENGTH+1);  //only if KEY_TYPE is char* ; otherwise (KEY_TYPE*)malloc(sizeof(KEY_TYPE));
	strcpy(temp->entry.ele,data);
	temp->entry.record_ptr=-1;

	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

Node* GetPredecessor(Node *temp)
{
	temp = temp->left;
	while(temp!=NULL && temp->right!=NULL)
	{
		temp=temp->right;
	}
	return temp;
}

Node* GetPredecessorParent(Node *temp)
{
	Node* parent=temp;
	temp = temp->left;
	while(temp!=NULL && temp->right!=NULL)
	{ 
		parent=temp;
		temp=temp->right;
	}
	return parent;
}

void delete(Bintree *b,KEY_TYPE data)
{
	Node* curr=b->root;
	Node *parent=NULL;
	Node *pred;
	Node *predP;
	while(curr!=NULL)
	{
		//if(data<curr->ele)
		if(strcmp(data,curr->entry.ele)<0)
		{parent=curr;curr=curr->left;}
		//else if(curr->ele<data)
		else if(strcmp(curr->entry.ele,data)<0)
		{parent=curr;curr=curr->right;}
		//else if(curr->ele==data)
		else if(strcmp(curr->entry.ele,data)==0)
		{
			printf("\nelement found!\n");
			if(parent!=NULL)
			{
				if(curr->left==NULL || curr->right==NULL)
				{
					if(curr->left==NULL)
					{
						if(curr==parent->left)
						{parent->left=curr->right;/*free(curr);*/free(curr->ele);free(curr);}
						else if(curr==parent->right)
						{parent->right=curr->right;/*free(curr);*/free(curr->ele);free(curr);}
					}
					else if(curr->right==NULL)
					{
						if(curr==parent->left)
						{parent->left=curr->left;/*free(curr);*/free(curr->ele);free(curr);}
						else if(curr==parent->right)
						{parent->right=curr->left;/*free(curr);*/free(curr->ele);free(curr);}
					}
					break;
				}
				else
				{
					pred=GetPredecessor(curr);
					CopyNodeData(curr,pred);
					predP=GetPredecessorParent(curr);
					if(pred==predP->right)
					{
						predP->right=NULL;
						//free(pred);
						free(pred->ele);
						free(pred);
					}
					else if(pred==predP->left)
					{
						predP->left=NULL;
						//free(pred);

						free(pred->ele);
						free(pred);
					}
					break;
					
				}
			}
			else if(parent==NULL)
			{
				pred=GetPredecessor(curr);
				if(pred!=NULL)
				{
				  CopyNodeData(curr,pred);
				  predP=GetPredecessorParent(curr);
				  if(pred==predP->right)
			       	  {
					predP->right=pred->left;
					//free(pred);
					free(pred->ele);
					free(pred);
				  }
				  else if(pred==predP->left)
			     	  {
					predP->left=pred->left;
					//free(pred);
					free(pred->ele);
					free(pred);
				  }
				 }
				 else
				 {
					 printf("\ndelete last element which is root");
					 if(curr->right==NULL)
					 {b->root=NULL;/*free(curr);*/free(curr->ele);free(curr);}
					 else
					 {b->root=curr->right;/*free(curr);*/free(curr->ele);free(curr);}
				 }
				  break;
			}
		}

	}	
}
