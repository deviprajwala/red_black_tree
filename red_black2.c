//red black tree

#include<stdio.h>
#include<stdlib.h>

//int a[25]={10,9,8,7,6};
struct node
{
 int info;
 struct node *llink;
 struct node *rlink;
 struct node *par;
 int color;
};
typedef struct node *node;



void rb_insert_fix(node root,node temp);
node rb_insert(int item,node root);
node getnode();
node left_rotate(node root,node z);
node right_rotate(node root,node z);
void inorder(node root);
int height(node root);
void print2(int h[10],int hmax,node root);
void print(node root);
void verify(node root);
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

 int h;
 
 
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
     h=height(temp->par->par);
    }
 else
    {
    prev->llink=temp;
    temp->par=prev;
    printf("Item inserted is %d\n",temp->info);
    h=height(temp->par->par);
    }

if(h>=2)
 {
  rb_insert_fix(root,temp);
 }
  verify(root);
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
  else if(x=x->par->llink)
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
  else if(x=x->par->rlink)
  {
    x->par->rlink=y;
  }
  else
  {
    x->par->llink=y;
  }
  y->rlink=x;
  x->par=y;
  return root;
 
}

void rb_insert_fix(node root,node temp)
{
  node parent,gparent,unc,x;
  parent=temp->par;
  gparent=parent->par;
  if(parent->color==1)               
  {
    if(parent==gparent->llink)
     {
       if(gparent->rlink==NULL) goto sing;
       unc=gparent->rlink;
       if(unc->color==1)
          {
            parent->color=0;
            unc->color=0;
            gparent->color=1;
            temp=gparent;
           }
        else if(temp==parent->rlink)
           {
             temp=parent;
             root=left_rotate(temp,root);
           }
             parent->color=0;
             gparent->color=1;
             x=gparent;
             root=right_rotate(x,root);
           sing:
             parent->color=0;
             gparent->color=1;
             x=gparent;
             root=right_rotate(x,root);

       }
     else
      {
       if(gparent->llink==NULL) goto dance;
       unc=gparent->llink;
       if(unc->color==1)
          {
            parent->color=0;
            unc->color=0;
            gparent->color=1;
            temp=gparent;
           }
        else if(temp==parent->llink)
           {
             temp=parent;
             root=right_rotate(temp,root);
           }
             parent->color=0;
             gparent->color=1;
             x=gparent;
             root=left_rotate(x,root);
           
        dance:
             parent->color=0;
             gparent->color=1;
             x=gparent;
             root=left_rotate(x,root);
           

       }
 }         
root->color=0; 
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

int height(node root)
{
  int ldepth,rdepth;
 
  if(root==NULL)
     return 0;
  
  else
     ldepth=height(root->llink);
     rdepth=height(root->rlink);

     if(ldepth>rdepth)
         return (ldepth+1);
      
     else
         return (rdepth+1);

}
void verify(node root)
{
  if(root->color!=0)
  {
   exit(0);
  }
  verify2(root);
 
}
void verify2(node x)
{
  while(x->rlink!=NULL)
  {
  verify3(x->rlink);
  verify3(x->llink);
  }
}
void verify3(node x)
{ 
 if(x->color==1)
 {
   if(x->rlink!=NULL&&x->rlink->color==1)
     {
      exit(0);
     }
   else if(x->llink!=NULL&&x->llink->color==1)
     {
      exit(0);
     }
  }
  verify2(x->rlink);
  verify2(x->llink);
}

void main()
{
 int i,n,a[5]={10,9,8,7,6};
 node root;
//color 1-red 0-black
//printf("enter the number of elements\n");
//scanf("%d",&n);
//for(i=0;i<5;i++)
//{
  // scanf("%d",&a[i]);
//}
 for(i=0;i<5;i++)
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
