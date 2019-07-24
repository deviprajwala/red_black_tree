//red black tree
//function is added to print the tree which is not working properly
#include<stdio.h>
#include<stdlib.h>

int a[25]={5,4,3,2,1};
struct node
{
 int info;
 struct node *llink;
 struct node *rlink;
 struct node *par;
 int height;
 int color;
};
typedef struct node *node;

node root;


void rb_insert_fix(node root,node temp);
node rb_insert(int item,node root);
node getnode();
void left_rotate(node root,node z);
void right_rotate(node root,node z);
int height(node root);
void inorder(node root);
void print(int height);


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
 temp->height=0;
 temp->info=item;

 int h,h1;
 
 
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
     h1=height(temp);
     temp->height=h1;
     h=height(temp->par->par);
    }
 else
    {
    prev->llink=temp;
    temp->par=prev;
    printf("Item inserted is %d\n",temp->info);
    temp->height=h1;
    h=height(temp->par->par);
    }

if(h>=2)
 {
  rb_insert_fix(root,temp);
 }
}

else if(root==NULL)
 {
   root=temp;
   printf("Item inserted is %d\n",temp->info);
   root->color=0; 
   temp->height=h1;
   //break;
 }
return root;

}


void left_rotate(node root,node x)
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
}
void right_rotate(node root,node x)
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
             left_rotate(temp,root);
           }
             parent->color=0;
             gparent->color=1;
             x=gparent;
             right_rotate(x,root);
           sing:
             parent->color=0;
             gparent->color=1;
             x=gparent;
             right_rotate(x,root);

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
             right_rotate(temp,root);
           }
             parent->color=0;
             gparent->color=1;
             x=gparent;
             left_rotate(x,root);
           
        dance:
             parent->color=0;
             gparent->color=1;
             x=gparent;
             left_rotate(x,root);
           

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
void print(int h)
{
  int x,x1,x2;
  x=h;
  
 x1=height(root->rlink);
 x2=height(root->llink);
  
    if(x1==x)
       printf("%d",root->height);
    if(x2==x)
       printf("%d",root->height);
  
  print(x1);
  
  print(x2);
}

void main()
{
 int i;
 //node root;
//color 1-red 0-black
 for(i=0;i<5;i++)
  {
    root=rb_insert(a[i],root);
  }
printf("successful insertion\n");
printf("inorder traversal is\n");
inorder(root);
print(root->height);

}
