//red black tree
//not going into the rotate function

#include<stdio.h>
#include<stdlib.h>

int a[25]={1,2,3,4,5};
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
//node parent(node root,int key);
void left_rotate(node root,node z);
void right_rotate(node root,node z);
void printinorder(node root);

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
    }
 else
    {
    prev->llink=temp;
    temp->par=prev;
    }

rb_insert_fix(root,temp);
}

else if(root==NULL)
 {
   root=temp;
   //break;
 }
return root;

}

//node parent(node root,int key)
//{
//  node lchild,rchild;
//  if(root==NULL) return root;
  
 // rchild=root->rlink;
 // lchild=root->llink;
  
//  if(root->llink!=NULL) 
//      lchild=root->llink;
//  if(root->rlink!=NULL) 
//      rchild=root->rlink;

//  if ((rchild->info==key)||(lchild->info==key)) return root;

//  else if (root->info>key)
//         parent(lchild,key);
//  else
//         parent(root->rlink,key);
 // return root;
 
//}

void left_rotate(node root,node z)
{
 // node gpar,par;
  //par=parent(z,z->info);
  //gpar=parent(par,par->info);
  
  //if(par->rlink==NULL)
    //{
      //gpar->rlink=NULL;
      //gpar->llink=NULL;
      //par->rlink=gpar;
      //par->llink=z;
    //}
  //else
    //{
      //gpar->llink=par->rlink;
      //par->rlink=gpar;
    //}
//}

  node A,B,C,top,D;
  C=z->par;
  B=C->par;
  A=B->par;
  top=A->par;
  
  if(B->llink==NULL)
   {
     B->par=top;
     B->llink=A;  A->par=B;
     B->rlink=C;  C->par=B;
    }
   else
    {
     D=B->rlink;
     B->par=top; 
     B->rlink=A;  A->par=B;
     B->llink=C;  C->par=B;
     A->rlink=D;  D->par=A;
    }
}
//void right_rotate(node root,node z)
//{
  //node gpar,par,x;
  //par=parent(z,z->info);
  //gpar=parent(par,par->info);
  
  //if(par->llink==NULL)
    //{
      //gpar->rlink=NULL;
      //gpar->llink=NULL;
      //par->llink=gpar;
      //par->rlink=z;
    //}
  //else
    //{
      //gpar->rlink=par->llink;
      //par->llink=gpar;
    //}
//}

void rb_insert_fix(node root,node temp)
{
  node paren,gparent,unc,x;
  paren=parent(root,temp->info);
  gparent=parent(root,paren->info);
  while(paren->color=1)
  {
    if(paren==gparent->llink)
     {
       unc=gparent->rlink;
       if(unc->color==1)
          {
            paren->color=0;
            unc->color=0;
            gparent->color=1;
            temp=gparent;
           }
        else if(temp==paren->rlink)
           {
             temp=paren;
             left_rotate(temp,root);
             paren->color=0;
             gparent->color=1;
             x=parent(gparent,gparent->info);
             right_rotate(x,root);
           }

       }
     else
        {
       unc=gparent->llink;
       if(unc->color==1)
          {
            paren->color=0;
            unc->color=0;
            gparent->color=1;
            temp=gparent;
           }
        else if(temp==paren->llink)
           {
             temp=paren;
             left_rotate(temp,root);
             paren->color=0;
             gparent->color=1;
             x=parent(root,gparent->info);
             right_rotate(x,root);
           }
          }
root->color=0;
  } 
}

void printinorder(node root)
{
   while(root!=NULL)
  {
   printinorder(root->llink);
   printf("%d ",root->info);
   if(root->color==1)
     printf("red\n");
   else
     printf("black\n");
   printinorder(root->rlink);
  }
}

void main()
{
 int i;
 node root;
//color 1-red 0-black
 for(i=0;i<5;i++)
  {
    root=rb_insert(a[i],root);
  }
printf("successful insertion\n");
printinorder(root);

}
