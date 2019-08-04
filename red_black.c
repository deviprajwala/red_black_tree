//red black tree

#include<stdio.h>
#include<stdlib.h>

//int a[25]={10,9,8,7,6,5,4,3,2,1};
struct node
{
 int info;
 struct node *llink;
 struct node *rlink;
 struct node *par;
 int color;
};
typedef struct node *node;



node rb_insert_fix(node root,node temp);
node rb_insert(int item,node root);
node getnode();
node left_rotate(node root,node z);
node right_rotate(node root,node z);
void inorder(node root);
node verify(node root);
void verify2(node x);
void verify3(node x);

node getnode()
{
 node x;
 x=(node)malloc(sizeof(struct node));
 if(x==NULL)
   {
     printf("out of memory\n");
     exit(0);
    }
    return x;
}

node rb_insert(int item,node root)
{
 node temp,prev,cur;
 temp=getnode();
 temp->llink=NULL;
 temp->rlink=NULL;
 temp->par=NULL; 
 temp->color=1;
 temp->info=item;

 
if(root!=NULL)
{
 prev=NULL;
 cur=root;
 while(cur!=NULL)
 {
   prev=cur;
   if(item>cur->info)
       cur=cur->rlink;
   else
       cur=cur->llink;
 }
 if(item>=prev->info)
    {
     prev->rlink=temp;
     temp->par=prev;
     printf("Item inserted is %d\n",temp->info);
    }
 else
    {
    prev->llink=temp;
    temp->par=prev;
    printf("Item inserted is %d\n",temp->info);
    }


  root=rb_insert_fix(root,temp);

 
}

else if(root==NULL)
 {
   root=temp;
   printf("Item inserted is %d\n",temp->info);
   root->color=0; 
   //break;
 }
return root;

}

node left_rotate(node root,node x)
{
  node y;
  y=x->rlink;
  
  x->rlink=y->llink;
  if(y->llink!=NULL)
  {
     y->llink->par=x;
    
  }
  y->par=x->par;
  if(x->par==NULL)
  {
    root=y;
  }
  else if(x==x->par->llink)
  {
    x->par->llink=y;
  }
  else
  {
    x->par->rlink=y;
  }
  y->llink=x;
  x->par=y;
  return root;
}
node right_rotate(node root,node x)
{
  node y;
  y=x->llink;
 
  x->llink=y->rlink;
  if(y->rlink!=NULL)
  {
     y->rlink->par=x;
     
  }
  y->par=x->par;
  if(x->par==NULL)
  {
    root=y;
  }
  else if(x==x->par->rlink)
  {
    x->par->rlink=y;
  }
  else
  {
    x->par->llink=y;
  }
  y->rlink=x;
  x->par=y;
  return y;
 
}

node rb_insert_fix(node root,node temp)
{
  node y;
  
  while(temp->par!=NULL&&temp->par->color==1)               
  {
    if(temp->par==temp->par->par->llink)
     {
          
            y=temp->par->par->rlink;
            if(y!=NULL&&y->color==1)
            { 
            temp->par->color=0;
            y->color=0;
            temp->par->par->color=1;
            temp=temp->par->par;
            }
         
            else if(temp==temp->par->rlink)
           {
           temp=temp->par;
           root=left_rotate(root,temp);
           }
           else
           {
           temp->par->color=0;
           temp->par->par->color=1;
           y=temp->par->par;
           root=right_rotate(root,y);
           }
        
      }
      else
      {  
             y=temp->par->par->llink;
             if(y!=NULL&&y->color==1) 
             {
             temp->par->color=0;
             y->color=0;
             temp->par->par->color=1;
             temp=temp->par->par;
             }
    
             else if(temp==temp->par->llink)
             {
             temp=temp->par;
             root=right_rotate(root,temp);
             }
            else
             {
             temp->par->color=0;
             temp->par->par->color=1;
             y=temp->par->par;
             root=left_rotate(root,y);
             }
         
     }
 
 }         
root->color=0; 
root=verify(root);
return root;
}

void inorder(node root)
{
   if(root==NULL) return;
   inorder(root->llink);
   printf("%d ",root->info); goto color;
color:
  { if(root->color==1)
      printf("red\n");
   else
      printf("black\n");
   }
   inorder(root->rlink);
}

node verify(node root)
{
  if(root->color!=0)
  {
   exit(0);
  }
  verify2(root);
  return root;
 
}
void verify2(node x)
{
 
  if(x->rlink!=NULL)
  {
  verify3(x->rlink);
  }goto lchild;

lchild:
  if(x->llink!=NULL)
  {
  verify3(x->llink);
  }
}
void verify3(node x)
{ 
  if(x->color==1)
 {
   if(x->rlink!=NULL&&x->rlink->color==1)
     {
      printf("ERROR red parent red child");
      exit(0);
     }
   else if(x->llink!=NULL&&x->llink->color==1)
     {
      printf("ERROR red parent red child");
      exit(0);
     }
  }
 
  if(x->rlink!=NULL)
  {
  verify2(x->rlink);
  }goto lchild1;

lchild1:
  
  if(x->llink!=NULL)
  {
  verify2(x->llink);
  }
 
return;
}

void main()
{
 int i,n=10,a[100];//={1,2,3,4,5,6,7,8,9,10};
 node root;
//color 1-red 0-black
//printf("enter the number of elements\n");
scanf("%d",&n);
for(i=0;i<n;i++)
 {
  scanf("%d",&a[i]);
 }
 for(i=0;i<n;i++)
  {
    if(i==0)
    {
       root=NULL;
    }
    root=rb_insert(a[i],root);
  }
printf("successful insertion\n");
printf("inorder traversal is\n");
inorder(root);

}
