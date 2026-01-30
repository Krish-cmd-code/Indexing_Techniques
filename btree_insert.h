#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"N.h"

#define t 5 //t is degree of btree.

typedef struct Element_info{
	KEY_TYPE key;
	long int record_ptr;
}Ele_i;

typedef struct BTreeNode{
	int n;    //n=> key count.
	//int key[2*t-1];
//	char  key[2*t-1][MAX_LENGTH+1]; //keytype is char[]
	Ele_i entry[2*t-1];
	struct BTreeNode *child[2*t];
	bool leaf;
}Node;

typedef struct BTree{
	Node *root;
	int height;
}BTree;

typedef struct pair{
	Node *x; //x is the node where key to be search is present.
	int i;   //i is the index of key in node x.
}pair;


void Delete_B_Tree(BTree *T,KEY_TYPE k);
void Delete_Non_Null(Node *x,KEY_TYPE k);
void Delete_At_Leaf(Node *x,KEY_TYPE);
void CopyNodeData(Node *a,Node*b); //NO USE in b_tree operations till now.
void B_Tree_Traversal(Node *root);
Node* NewNode();
pair* Create_Pair(Node *x,int i);
void B_Tree_Create(BTree *T);
pair* B_Tree_Search(Node *x,KEY_TYPE k);
void B_Tree_Split_Child(Node *x,int i); //x represents the node.i represents the index of child of node x that is to be split.
//void B_Tree_Insert(BTree *T,KEY_TYPE k);
//void B_Tree_Insert_NonFull(Node *x,KEY_TYPE k);
void B_Tree_Insert(BTree *T,Ele_i *k);
void B_Tree_Insert_NonFull(Node *x,Ele_i *k);

/*
KEY_TYPE Rightmost(Node *x);
KEY_TYPE Leftmost(Node *x);
*/
Ele_i* Rightmost(Node *x);
Ele_i* Leftmost(Node *x);
int Is_Present(Node *x,KEY_TYPE k);
int Determine_Child(Node *x,KEY_TYPE k);

//void merge(Node *x,KEY_TYPE k,Node *y);
void merge(Node *x,Ele_i *k,Node *y);//this will merge x,k,y in x.

Node* NewNode()
{
	Node* temp=(Node*)malloc(sizeof(Node));
	
	
//	printf("\nnode created..");
	return temp;
}
pair* Create_Pair(Node *x,int i)
{
	pair* p = (pair*)malloc(sizeof(pair));
	p->x=x;
	p->i=i;
	return p;
}

pair* B_Tree_Search(Node *x,KEY_TYPE k)
{
	int i=0;

	//while(i<x->n && k>x->key[i])  //version1 for normal key of type int.
	//while(i<x->n && strcmp(k,x->key[i])>0) //version2 for key of type char*
	while(i<x->n && strcmp(k,x->entry[i].key)>0) //version3 for key of type char* as member of struct variable. similar pattern follows below...
	i++;
	//if(i<x->n && k==x->key[i])
	//if(i<x->n && strcmp(k,x->key[i])==0)
	if(i<x->n && strcmp(k,x->entry[i].key)==0)
	return Create_Pair(x,i);
	else if(x->leaf)
	return NULL;
	else
	{
		x=x->child[i];
		return B_Tree_Search(x,k);
	}
}

void CopyNodeData(Node *a,Node*b)
{
	a->leaf=b->leaf;
	a->n=b->n;
}
void B_Tree_Create(BTree *T)
{
	Node *x=NewNode();
	x->leaf=true;
	x->n=0;
	T->root=x;
	T->height=1;

//	printf("\nbtree_created");

}

void Copy_entry(Ele_i *dest,Ele_i *src)
{
	dest->key=(char*)malloc(sizeof(MAX_LENGTH+1));
	strcpy(dest->key,src->key); //as KEY_TYPE is char*. otherwise depends on KEY_TYPE .
	dest->record_ptr=src->record_ptr;
}
	
void B_Tree_Split_Child(Node *x,int i) //x represents the node.i represents the index of child of node x that is to be split.
{
	Node *z=NewNode();
	Node *y=x->child[i];
	z->leaf=y->leaf;
	z->n = t-1;

	for(int j=0;j<t-1;j++)	//give all keys greater than median of y to z.
	{
		//z->key[j]=y->key[j+t];
		//strcpy(z->key[j],y->key[j+t]);

		Copy_entry(&z->entry[j],&y->entry[j+t]);
		/* Alias for Copy_entry()
		strcpy(z->entry[j].key,y->entry[j+t].key);
		z->entry[j].record_ptr=y->entry[j+t].record_ptr;
		*/
	}

	if(!y->leaf)	//give all children right of median to z.
	{
		for(int j=0;j<t;j++)
		{
			z->child[j]=y->child[j+t];
		}
	}
	
	y->n=t-1;	//update y->n==>which is key count.

	for(int j=x->n;j>=i+1;j--)  //shift all children of parent x to by one position to right from i+1 position to x->n-1 index.
	{
		x->child[j+1]=x->child[j];
	}
	x->child[i+1]=z;

	for(int j=x->n-1;j>=i;j--)
	{
		//x->key[j+1]=x->key[j];
		//strcpy(x->key[j+1],x->key[j]);
		
		Copy_entry(&x->entry[j+1],&x->entry[j]);
	}
	//x->key[i]=y->key[t-1];
	//strcpy(x->key[i],y->key[t-1]);

	Copy_entry(&x->entry[i],&y->entry[t-1]);
	x->n++;

}


/*
void B_Tree_Insert(BTree *T,KEY_TYPE k)
{
	Node *r=T->root;
	if(r->n==2*t-1) //root node is full.
	{
		Node *s=NewNode();
		T->root=s;
		s->leaf=false;
		s->n=0;
		s->child[0]=r;
		B_Tree_Split_Child(s,0);
		B_Tree_Insert_NonFull(s,k);
		
		T->height++;
	}
	else
	B_Tree_Insert_NonFull(T->root,k);
}
*/

void B_Tree_Insert(BTree *T,Ele_i *k)
{
	Node *r=T->root;
	if(r->n==2*t-1) //root node is full.
	{
		Node *s=NewNode();
		T->root=s;
		s->leaf=false;
		s->n=0;
		s->child[0]=r;
		B_Tree_Split_Child(s,0);
		B_Tree_Insert_NonFull(s,k);
		
		T->height++;
	}
	else
	B_Tree_Insert_NonFull(T->root,k);
}
/*
void B_Tree_Insert_NonFull(Node *x,KEY_TYPE k)
{
	int i=x->n-1; //as indexing start from 0.
	if(x->leaf)
	{
		//while(i>=0 && k<x->key[i])
		//while(i>=0 && strcmp(k,x->key[i])<0)
		while(i>=0 && strcmp(k,x->entry[i].key)<0)
		{
			//x->key[i+1]=x->key[i];
			strcpy(x->key[i+1],x->key[i]);
			Copy_entry(&x->entry[i+1],&x->entry[i]);
			i--;
		}
		//x->key[i+1]=k;
		strcpy(x->key[i+1],k);
		
		x->n++;
//		printf("\ninserted..at %d ",i+1);
	}
	else
	{
		//while(i>=0 && k<x->key[i])
		while(i>=0 && strcmp(k,x->key[i])<0)
		i--;
		i++; //this indicates x.key[i]<k hence we need to insert at child at i+1.

		if(x->child[i]->n==2*t-1)
		{
			B_Tree_Split_Child(x,i);
			//if( k > x->key[i] )
			if(strcmp(k,x->key[i])>0)
			{
				i=i+1;
			}
		}
		B_Tree_Insert_NonFull(x->child[i],k);
	}
}
*/
void B_Tree_Insert_NonFull(Node *x,Ele_i *k)
{
	int i=x->n-1; //as indexing start from 0.
	if(x->leaf)
	{
		//while(i>=0 && k<x->key[i])
		//while(i>=0 && strcmp(k,x->key[i])<0)
		while(i>=0 && strcmp(k->key,x->entry[i].key)<0)
		{
			//x->key[i+1]=x->key[i];
			//strcpy(x->key[i+1],x->key[i]);
			Copy_entry(&x->entry[i+1],&x->entry[i]);
			i--;
		}
		//x->key[i+1]=k;
		//strcpy(x->key[i+1],k->key);
		Copy_entry(&x->entry[i+1],k);
		
		x->n++;
//		printf("\ninserted..at %d ",i+1);
	}
	else
	{
		//while(i>=0 && k<x->key[i])
		//while(i>=0 && strcmp(k->key,x->key[i])<0)
		while(i>=0 && strcmp(k->key,x->entry[i].key)<0)
		i--;
		i++; //this indicates x.key[i]<k->key hence we need to insert at child at i+1.

		if(x->child[i]->n==2*t-1)
		{
			B_Tree_Split_Child(x,i);
			//if( k > x->key[i] )
			//if(strcmp(k->key,x->key[i])>0)
			if(strcmp(k->key,x->entry[i].key)>0)
			{
				i=i+1;
			}
		}
		B_Tree_Insert_NonFull(x->child[i],k);
	}
}

void Delete_B_Tree(BTree *T,KEY_TYPE k)
{
	Node *r=T->root;
	if(r->n==0)
	{
		printf("\nempty btree\n");
		return;
		//T->root=r->child[0];
	}
	Delete_Non_Null(r,k);
	if(T->root->n==0 && !T->root->leaf)//root only updated only if it has zero no.of keys and it is internal node.
	{
		printf("\nroot updated\n");
		T->root=T->root->child[0];
		
		T->height--;
	}
	/*
	if(T->root->n==0)
	{
		r=T->root;
		if(r->n==0)
		T->root=r->child[0];
	}
	*/
}

void Delete_At_Leaf(Node *x,KEY_TYPE k)
{
	printf("\ndelete At leaf called.\n");
	int i=0;
	int j;
	bool isPresent=false;
	//while(i<x->n && k>=x->key[i])
	//while(i<x->n && strcmp(k,x->key[i])>=0)
	while(i<x->n && strcmp(k,x->entry[i].key)>=0)
	{
		//if(k==x->key[i])
/*
		if(strcmp(k,x->key[i])==0)
		{isPresent=true;printf("\n present at:%d\n",i);break;}
*/
		if(strcmp(k,x->entry[i].key)==0)
		{isPresent=true;printf("\n present at:%d\n",i);break;}
		i++;
	}
	if(isPresent==true)
	{
		i=i+1;
		while(i<x->n)
		{
			//x->key[i-1]=x->key[i];
			//strcpy(x->key[i-1],x->key[i]);
			
			Copy_entry(&x->entry[i-1],&x->entry[i]);
			i++;
		}
		x->n--;
//		printf("\nafter deletion x->n:%d\n",x->n);
//		printf("\nisLeaf:%d\n",x->leaf);
	}
}

int Is_Present(Node *x,KEY_TYPE k)
{
	int i=0;
	while(i<x->n)
	{
		//if(x->key[i]==k)
		//if(strcmp(x->key[i],k)==0)
		if(strcmp(x->entry[i].key,k)==0)
		return i;
		i++;
	}
	return -1;
}

/*
KEY_TYPE Rightmost(Node *x)
{
	int i=x->n-1;
	if(x->leaf==true)
	{
		return x->key[i];
	}
	else 
	{ 
		return Rightmost(x->child[i+1]);
	}
}
*/

Ele_i* Rightmost(Node *x)
{
	int i=x->n-1;
	if(x->leaf==true)
	{
		return &x->entry[i];
	}
	else 
	{ 
		return Rightmost(x->child[i+1]);
	}
}

/*
KEY_TYPE Leftmost(Node *x)
{
	int i=0;
	if(x->leaf==true)
	{
		return x->key[i];
	}
	else
	{
		return Leftmost(x->child[i]);
	}
}
*/

Ele_i* Leftmost(Node *x)
{
	int i=0;
	if(x->leaf==true)
	{
		return &x->entry[i];
	}
	else
	{
		return Leftmost(x->child[i]);
	}
}

/*
void merge(Node *x,KEY_TYPE k,Node *y)//this will merge x,k,y in x.
{
	int i=x->n;
	int j=0;
	//x->key[i++]=k;
	//strcpy(x->key[i++],k);
	Copy_entry(x->entry[i++],k);
	
	while(j<y->n)
	{
		//x->key[i]=y->key[j];
		strcpy(x->key[i],y->key[j]);
		i++;j++;
	}
	x->n=i;//update the count of keys in x.
}
*/

void merge(Node *x,Ele_i *k,Node *y)//this will merge x,k,y in x.
{
	int i=x->n;
	int j=0;
	//x->key[i++]=k;
	//strcpy(x->key[i++],k);
	Copy_entry(&x->entry[i++],k);
	
	while(j<y->n)
	{
		//x->key[i]=y->key[j];
		//strcpy(x->key[i],y->key[j]);
		Copy_entry(&x->entry[i],&y->entry[j]);
		i++;j++;
	}
	x->n=i;//update the count of keys in x.
}

int Determine_Child(Node *x,KEY_TYPE k)
{
	int i=x->n-1;
	//while(i>=0 && k<x->key[i])
	//while(i>=0 && strcmp(k,x->key[i])<0)
	while(i>=0 && strcmp(k,x->entry[i].key)<0)
	{
		i=i-1;
	}
	//if(k>=x->key[i])
	if(strcmp(k,x->entry[i].key)>=0)
	{
		i++;
	}
	return i;
}

void merge_3b(Node *x,int i,Node *left_child,KEY_TYPE k,Node *right_child)//i indicates position of a key  whose children are left_child& right_child in x.
{
	int j,l;

						//merge left_child with sibling  right_child in left_child.
						//x->child[i],x->key[i],x->child[i+1]

						//move all keys into x->child[i](left_child).
						j=left_child->n;//j=x->child[i]->n;
						//left_child->key[j++]=x->key[i];//x->child[i]->key[j]=x->key[i];//median to push in merge node.
						//strcpy(left_child->key[j++],x->key[i]);//x->child[i]->key[j]=x->key[i];//median to push in merge node.
						Copy_entry(&left_child->entry[j++],&x->entry[i]);
						l=0;
						while(l<right_child->n)//while(k<x->child[i+1]->n)
						{
							//left_child->key[j]=right_child->key[l];//x->child[i]->key[j]=x->child[i+1]->key[k];
							//strcpy(left_child->key[j],right_child->key[l]);//x->child[i]->key[j]=x->child[i+1]->key[k];
							Copy_entry(&left_child->entry[j],&right_child->entry[l]);
							j++;l++;
						}

						//move all children to x->child[i].
						j=left_child->n+1;//j=x->child[i]->n+1;
						l=0;
						while(l<=right_child->n)//while(k<=x->child[i+1]->n)
						{
							left_child->child[j]=right_child->child[l];//x->child[i]->child[j]=x->child[i+1]->child[k];
							l++;j++;
						}

						left_child->n = left_child->n+1+right_child->n;//x->child[i]->n += 1+x->child[i+1]->n;
						//left_child->n = j;

						//reduce key of x to left by one.
						j=i;
						while(j<x->n-1)
						{
							//x->key[j]=x->key[j+1];
							//strcpy(x->key[j],x->key[j+1]);
							Copy_entry(&x->entry[j],&x->entry[j+1]);
							j++;
						}
						//reduce children of x to left by one.
						j=i+1;
						while(j<x->n)
						{
							x->child[j]=x->child[j+1];
							j++;
						}
						x->n--;

}

void Delete_Non_Null(Node *root,KEY_TYPE k)
{
//	printf("\nenter into del_noN_nul\n");
	Ele_i *entry;
	if(root==NULL)
	return;
	Node *x=root;
	int i,j,l;
	if(x->leaf)//case 1
	{
		Delete_At_Leaf(x,k);//delete at leaf if k present.
	}
	else if(!x->leaf)//case 2 internal node x
	{
		if((i=Is_Present(x,k))!=-1)//k is present in internal node x.
		{
			if(x->child[i]->n>=t)//left child to replace.case 2a
			{
				//x->key[i]=Rightmost(x->child[i]);//search of predecessor.
				//strcpy(x->key[i],Rightmost(x->child[i]));//search of predecessor.
				entry=Rightmost(x->child[i]);
				//strcpy(x->key[i],entry->key);
				Copy_entry(&x->entry[i],entry);
				//Delete_Non_Null(x->child[i],x->key[i]);
				Delete_Non_Null(x->child[i],x->entry[i].key);
			}
			else if(x->child[i+1]->n>=t)//right child to replace.case 2b
			{
				//x->key[i]=Leftmost(x->child[i+1]);//search of successor.
				//strcpy(x->key[i],Leftmost(x->child[i+1]));//search of successor.
				entry=Leftmost(x->child[i+1]);
				//strcpy(x->key[i],entry->key);
				Copy_entry(&x->entry[i],entry);
				//Delete_Non_Null(x->child[i+1],x->key[i]);
				Delete_Non_Null(x->child[i+1],x->entry[i].key);

			}
			else//case 2c
			{
				//merge(x->child[i],k,x->child[i+1]);
				merge(x->child[i],&x->entry[i],x->child[i+1]);
				//shift keys to left by one.
				j=i;
				while(j<x->n-1)
				{
					//x->key[j]=x->key[j+1];
					//strcpy(x->key[j],x->key[j+1]);

					Copy_entry(&x->entry[j],&x->entry[j+1]);
					j++;
				}
				j=i+1;
				while(j<x->n)//shift children to left by one.
				{
					x->child[j]=x->child[j+1];
					j++;
				}
				Delete_Non_Null(x->child[i],k);
				x->n--;
			}
		}
		else//k is not in internal node x. case3
		{
	//		printf("\nnot present inNode\n");
			i=Determine_Child(x,k); //returns child where k may present.
			printf("\nchild would be:%d\n",i);
			printf("\nchild would be->n:%d\n",x->child[i]->n);
			if(x->child[i]->n==t-1)//first child
			{
				printf("\nyeas\n");
				if(i==0)//child 0
				{
					if(x->child[i+1]->n>=t)//case 3a ...move right_up_left
					{
						printf("\ncase 3a\n");
						//move up down key with respect to..
						//x->child[i]->key[x->n]=x->key[i];
						//strcpy(x->child[i]->key[x->n],x->key[i]);

						Copy_entry(&x->child[i]->entry[x->n],&x->entry[i]);
						x->child[i]->child[x->child[i]->n+1]=x->child[i+1]->child[0];
						x->child[i]->n++;

						//x->key[i]=x->child[i+1]->key[0];
						//strcpy(x->key[i],x->child[i+1]->key[0]);
						Copy_entry(&x->entry[i],&x->child[i+1]->entry[0]);

						//shift key x->child[i+1] by one to left.
						j=1;
						while(j<x->child[i+1]->n)
						{
							//x->child[i+1]->key[j-1]=x->child[i+1]->key[j];
							//strcpy(x->child[i+1]->key[j-1],x->child[i+1]->key[j]);
							Copy_entry(&x->child[i+1]->entry[j-1],&x->child[i+1]->entry[j]);
							j++;
						}

						//shift children of x->child[i+1] by one to left.
						j=1;
						while(j<=x->child[i+1]->n)
						{
							x->child[i+1]->child[j-1]=x->child[i+1]->child[j];
							j++;
						}
						x->child[i+1]->n--;
						Delete_Non_Null(x->child[i],k);

					}
					else//case 3b
					{
						printf("\ncase 3b\n");
						//merge it with sibling i+1.
						//x->child[i],x->key[i],x->child[i+1]
						merge_3b(x,i,x->child[i],k,x->child[i+1]);
						Delete_Non_Null(x->child[i],k);
					}
				}
				else if(i==x->n)
				{
					if(x->child[i-1]->n>=t)//case 3a..move left_up_right.
					{
						//move key right with respect to..
						j=x->n;
						while(j>0)
						{
							//x->child[i]->key[j]=x->child[i]->key[j-1];
							//strcpy(x->child[i]->key[j],x->child[i]->key[j-1]);
							Copy_entry(&x->child[i]->entry[j],&x->child[i]->entry[j-1]);
							j--;
						}
						//x->child[i]->key[0]=x->key[i-1];
						//strcpy(x->child[i]->key[0],x->key[i-1]);
						Copy_entry(&x->child[i]->entry[0],&x->entry[i-1]);

						//move child right with respect to i
						j=x->n+1;
						while(j>=0)
						{
							x->child[i]->child[j]=x->child[i]->child[j-1];
							j--;
						}
						x->child[i]->child[0]=x->child[i-1]->child[x->child[i-1]->n];

						//x->key[i-1]=x->child[i-1]->key[x->child[i-1]->n-1];//move up key to x.
						//strcpy(x->key[i-1],x->child[i-1]->key[x->child[i-1]->n-1]);//move up key to x.
						Copy_entry(&x->entry[i-1],&x->child[i-1]->entry[x->child[i-1]->n-1]);

						x->child[i-1]->n--;

						x->child[i]->n++;
						Delete_Non_Null(x->child[i],k);

					}
					else//case 3b
					{

						//merge_3b(Node *x,int i,Node *left_child,int k,Node *right_child);
						printf("\ncase 3b\n");
						merge_3b(x,i,x->child[i-1],k,x->child[i]);
						Delete_Non_Null(x->child[i-1],k);

					}

				}
				else 
				{
					if(x->child[i-1]->n>=t)//case 3a ..move left_up_right.
					{
						printf("\ncase 3a\n");
						//move key right with respect to..
						j=x->n;
						while(j>0)
						{
							//x->child[i]->key[j]=x->child[i]->key[j-1];
							//strcpy(x->child[i]->key[j],x->child[i]->key[j-1]);
							Copy_entry(&x->child[i]->entry[j],&x->child[i]->entry[j-1]);
							j--;
						}
						//x->child[i]->key[0]=x->key[i-1];
						//strcpy(x->child[i]->key[0],x->key[i-1]);
						Copy_entry(&x->child[i]->entry[0],&x->entry[i-1]);

						//move child right with respect to i
						j=x->n+1;
						while(j>=0)
						{
							x->child[i]->child[j]=x->child[i]->child[j-1];
							j--;
						}
						x->child[i]->child[0]=x->child[i-1]->child[x->child[i-1]->n];

						//x->key[i-1]=x->child[i-1]->key[x->child[i-1]->n-1];//move up key to x.
						//strcpy(x->key[i-1],x->child[i-1]->key[x->child[i-1]->n-1]);//move up key to x.
						Copy_entry(&x->entry[i-1],&x->child[i-1]->entry[x->child[i-1]->n-1]);

						x->child[i-1]->n--;

						x->child[i]->n++;
						Delete_Non_Null(x->child[i],k);
					}
					else if(x->child[i+1]->n>=t)//case 3a ...move right_up_left
					{

						printf("\ncase 3a\n");
						//move up down key with respect to..
						//x->child[i]->key[x->n]=x->key[i];
						//strcpy(x->child[i]->key[x->n],x->key[i]);
						Copy_entry(&x->child[i]->entry[x->n],&x->entry[i]);
						x->child[i]->child[x->child[i]->n+1]=x->child[i+1]->child[0];
						x->child[i]->n++;

						//x->key[i]=x->child[i+1]->key[0];
						//strcpy(x->key[i],x->child[i+1]->key[0]);
						Copy_entry(&x->entry[i],&x->child[i+1]->entry[0]);

						//shift key x->child[i+1] by one to left.
						j=1;
						while(j<x->child[i+1]->n)
						{
							//x->child[i+1]->key[j-1]=x->child[i+1]->key[j];
							//strcpy(x->child[i+1]->key[j-1],x->child[i+1]->key[j]);
							Copy_entry(&x->child[i+1]->entry[j-1],&x->child[i+1]->entry[j]);
							j++;
						}

						//shift children of x->child[i+1] by one to left.
						j=1;
						while(j<=x->child[i+1]->n)
						{
							x->child[i+1]->child[j-1]=x->child[i+1]->child[j];
							j++;
						}
						x->child[i+1]->n--;
						Delete_Non_Null(x->child[i],k);
					}
					else//case 3b
					{
						printf("\ncase 3b\n");
						merge_3b(x,i,x->child[i-1],k,x->child[i]);
						Delete_Non_Null(x->child[i-1],k);
					}
				}

			}
			else
			{
				
				Delete_Non_Null(x->child[i],k);
			}

		}

	}
}


void B_Tree_Traversal(Node *root)
{
	int i=0;
	if(root==NULL)
	return;
	else
	{
		while(i<root->n)
		{
			B_Tree_Traversal(root->child[i]);
			printf(" %s ",root->entry[i].key);
			i++;
		}
		B_Tree_Traversal(root->child[i]);
	}
}































