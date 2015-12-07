#include <stdio.h>
#include <stdlib.h>
/*本程序作为数据结构课程（使用教材“数据结构与算法分析-C语言描述”，M. A. Ｗeiss著）关于二叉树部分的补充程序。*/ 
/*本程序使用纯 C 语言*/

typedef char ElementType;
typedef struct TreeNode {
	ElementType Element;
	struct TreeNode *Left;
	struct TreeNode *Right;
} BTNode;

BTNode *CreateTree(BTNode *root)
{
//先序递归创建二叉树，
//输入范例：abd#g##e##cf#h###
/*
       a
     /  \
    /    \
   b      c
  / \    /
 d   e  f
  \      \
   g      h

 */

//对应于：  a(b(d(,g),e),c(f(,h),))
	char ch;
	scanf("%c",&ch);
	if(ch=='#') {
		//printf("--%c$$$\n",ch);
		return NULL;
	}
	else
	{
		//printf("++%c***\n",ch);
		root=(BTNode *)malloc(sizeof(BTNode));
		root->Element=ch;
		root->Left=CreateTree(root->Left);
		root->Right=CreateTree(root->Right);
	}
	return root;
}

void PreOrder(BTNode *b) 	/*先序遍历的递归算法*/
{
	if (b!=NULL) {
		printf("%c ",b->Element); /*访问根结点*/
		PreOrder(b->Left);
		PreOrder(b->Right);
	}
}

void InOrder(BTNode *b) 	/*中序遍历的递归算法*/
{
	if (b!=NULL) {
		InOrder(b->Left);
		printf("%c ",b->Element); /*访问根结点*/
		InOrder(b->Right);
	}
}

void PostOrder(BTNode *b) /*后序遍历递归算法*/
{
	if (b!=NULL) {
		PostOrder(b->Left);
		PostOrder(b->Right);
		printf("%c ",b->Element); /*访问根结点*/
	}
}

int CountNode(BTNode *T) /*计算二叉树节点个数*/
{
	if ( T == NULL )
		return 0;
	else 
		return 1+CountNode(T->Left)+CountNode(T->Right);
}

int CountLeafNode(BTNode *T) /*计算二叉树叶子节点个数*/
{
	if ( T == NULL )
		return 0;
	else if ((T->Left==NULL)&&(T->Right==NULL))
		return 1;
	else 
		return CountLeafNode(T->Left)+CountLeafNode(T->Right);
}

	
int TreeDepth(BTNode *b)    /*求二叉树的深度 */
{
	int leftDep,rightDep;
	if (b==NULL) return(0); /*空树的深度为0*/
	else  
	{
		leftDep=TreeDepth(b->Left);
		/*求左子树的深度*/
		rightDep=TreeDepth(b->Right);
		/*求右子树的深度*/
		return(leftDep>rightDep)?(leftDep+1):(rightDep+1);
	}
}

BTNode *FindNode(BTNode *b,ElementType x) 
{
//在二叉树中查找值为x的结点
	BTNode *p;
	if (b==NULL)   return NULL;
	else if (b->Element==x)   return b;
	else
	{
		p=FindNode(b->Left,x);
		if (p!=NULL) return p; //判断子递归返回值
		else   return FindNode(b->Right,x);
	}
}

int Like(BTNode *b1,BTNode *b2)
{
    /*b1和b2两棵二叉树相似时返回1,否则返回0*/
	int like1,like2;
	if (b1==NULL && b2==NULL) return 1;
	else if (b1==NULL || b2==NULL)  return 0;
	else
	{
		like1=Like(b1->Left,b2->Left);
		like2=Like(b1->Right,b2->Right);
		return (like1 & like2);
		/*返回like1和like2的与*/
	}
}


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	BTNode *T,*p;
	T=CreateTree(p);
	PreOrder(T);
	printf("\nNode:%i\n",CountNode(T));
	printf("LeafNode:%i\n",CountLeafNode(T));
	printf("Depth:%i\n",TreeDepth(T));
	
	BTNode *f=FindNode(T,'c');
	PreOrder(f);
	
	return 0;
}
