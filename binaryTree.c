#include <stdio.h>
#include <stdlib.h>
/*��������Ϊ���ݽṹ�γ̣�ʹ�ý̲ġ����ݽṹ���㷨����-C������������M. A. ��eiss�������ڶ��������ֵĲ������*/ 
/*������ʹ�ô� C ����*/

typedef char ElementType;
typedef struct TreeNode {
	ElementType Element;
	struct TreeNode *Left;
	struct TreeNode *Right;
} BTNode;

BTNode *CreateTree(BTNode *root)
{
//����ݹ鴴����������
//���뷶����abd#g##e##cf#h###
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

//��Ӧ�ڣ�  a(b(d(,g),e),c(f(,h),))
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

void PreOrder(BTNode *b) 	/*��������ĵݹ��㷨*/
{
	if (b!=NULL) {
		printf("%c ",b->Element); /*���ʸ����*/
		PreOrder(b->Left);
		PreOrder(b->Right);
	}
}

void InOrder(BTNode *b) 	/*��������ĵݹ��㷨*/
{
	if (b!=NULL) {
		InOrder(b->Left);
		printf("%c ",b->Element); /*���ʸ����*/
		InOrder(b->Right);
	}
}

void PostOrder(BTNode *b) /*��������ݹ��㷨*/
{
	if (b!=NULL) {
		PostOrder(b->Left);
		PostOrder(b->Right);
		printf("%c ",b->Element); /*���ʸ����*/
	}
}

int CountNode(BTNode *T) /*����������ڵ����*/
{
	if ( T == NULL )
		return 0;
	else 
		return 1+CountNode(T->Left)+CountNode(T->Right);
}

int CountLeafNode(BTNode *T) /*���������Ҷ�ӽڵ����*/
{
	if ( T == NULL )
		return 0;
	else if ((T->Left==NULL)&&(T->Right==NULL))
		return 1;
	else 
		return CountLeafNode(T->Left)+CountLeafNode(T->Right);
}

	
int TreeDepth(BTNode *b)    /*������������ */
{
	int leftDep,rightDep;
	if (b==NULL) return(0); /*���������Ϊ0*/
	else  
	{
		leftDep=TreeDepth(b->Left);
		/*�������������*/
		rightDep=TreeDepth(b->Right);
		/*�������������*/
		return(leftDep>rightDep)?(leftDep+1):(rightDep+1);
	}
}

BTNode *FindNode(BTNode *b,ElementType x) 
{
//�ڶ������в���ֵΪx�Ľ��
	BTNode *p;
	if (b==NULL)   return NULL;
	else if (b->Element==x)   return b;
	else
	{
		p=FindNode(b->Left,x);
		if (p!=NULL) return p; //�ж��ӵݹ鷵��ֵ
		else   return FindNode(b->Right,x);
	}
}

int Like(BTNode *b1,BTNode *b2)
{
    /*b1��b2���ö���������ʱ����1,���򷵻�0*/
	int like1,like2;
	if (b1==NULL && b2==NULL) return 1;
	else if (b1==NULL || b2==NULL)  return 0;
	else
	{
		like1=Like(b1->Left,b2->Left);
		like2=Like(b1->Right,b2->Right);
		return (like1 & like2);
		/*����like1��like2����*/
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
