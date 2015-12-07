        #include "tree.h"
        #include <stdlib.h>
        #include "fatal.h"

        struct TreeNode
        {
            ElementType Element;
            SearchTree  Left;
            SearchTree  Right;
        };

/* START: fig4_17.txt */

        /*让二叉查找树为空*/
        SearchTree
        MakeEmpty( SearchTree T )
        {
            if( T != NULL )
            {
                MakeEmpty( T->Left );
                MakeEmpty( T->Right );
                free( T );
            }
            return NULL;
        }
/* END */

/* START: fig4_18.txt */
        /*找元素在二叉查找树中的位置*/
        Position
        Find( ElementType X, SearchTree T )
        {
            if( T == NULL )
                return NULL;
            if( X < T->Element )
                return Find( X, T->Left );
            else
            if( X > T->Element )
                return Find( X, T->Right );
            else
                return T;
        }
/* END */

/* START: fig4_19.txt */
        //递归实现
        Position
        FindMin( SearchTree T )
        {
            if( T == NULL )
                return NULL;
            else
            if( T->Left == NULL )
                return T;
            else
                return FindMin( T->Left );
        }
/* END */

/* START: fig4_20.txt */
        //非递归实现
        Position
        FindMax( SearchTree T )
        {
            if( T != NULL )
                while( T->Right != NULL )
                    T = T->Right;

            return T;
        }
/* END */

/* START: fig4_22.txt */

        /*二叉查找树的插入*/
        SearchTree
        Insert( ElementType X, SearchTree T )
        {
/* 1*/      if( T == NULL )
            {
                /* Create and return a one-node tree */
/* 2*/          T = malloc( sizeof( struct TreeNode ) );
/* 3*/          if( T == NULL )
/* 4*/              FatalError( "Out of space!!!" );
                else
                {
/* 5*/              T->Element = X;
/* 6*/              T->Left = T->Right = NULL;
                }
            }
            else
/* 7*/      if( X < T->Element )
/* 8*/          T->Left = Insert( X, T->Left );
            else
/* 9*/      if( X > T->Element )
/*10*/          T->Right = Insert( X, T->Right );
            /* Else X is in the tree already; we'll do nothing */

/*11*/      return T;  /* Do not forget this line!! */
        }
/* END */

/* START: fig4_25.txt */

        /*二叉查找树的删除*/
        /*
          分三种情况
          1.两个子节点
          2.1个子节点（左节点或者右节点）
          3.叶子节点（0个子节点）
         */
        SearchTree
        Delete( ElementType X, SearchTree T )
        {
            Position TmpCell;

            if( T == NULL )
                Error( "Element not found" );
            else
            if( X < T->Element )  /* Go left */
                T->Left = Delete( X, T->Left );
            else
            if( X > T->Element )  /* Go right */
                T->Right = Delete( X, T->Right );
            else  /* Found element to be deleted */
            if( T->Left && T->Right )  /* Two children 两个孩子*/
            {
                /* Replace with smallest in right subtree */
                TmpCell = FindMin( T->Right );
                T->Element = TmpCell->Element;
                T->Right = Delete( T->Element, T->Right );
            }
            else  /* One or zero children */
            {
                TmpCell = T;
                if( T->Left == NULL ) /* Also handles 0 children 也处理了0个孩子的情况*/
                    T = T->Right;
                else if( T->Right == NULL )
                    T = T->Left;
                free( TmpCell );
            }

            return T;
        }
/* END */

        /* 返回某个节点的元素 */
        ElementType
        Retrieve( Position P )
        {
            return P->Element;
        }
