        #include "avltree.h"
        #include <stdlib.h>
        #include "fatal.h"

        struct AvlNode
        {
            ElementType Element;
            AvlTree  Left;
            AvlTree  Right;
            int      Height;
        };

        /*置空平衡树*/
        AvlTree
        MakeEmpty( AvlTree T )
        {
            if( T != NULL )
            {
                MakeEmpty( T->Left );
                MakeEmpty( T->Right );
                free( T );
            }
            return NULL;
        }

        /*查找元素在平衡树中的位置*/
        Position
        Find( ElementType X, AvlTree T )
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

        /*找平衡树的最小元素，递归实现*/
        Position
        FindMin( AvlTree T )
        {
            if( T == NULL )
                return NULL;
            else
            if( T->Left == NULL )
                return T;
            else
                return FindMin( T->Left );
        }

        /*找平衡树的最大元素，非递归实现*/
        Position
        FindMax( AvlTree T )
        {
            if( T != NULL )
                while( T->Right != NULL )
                    T = T->Right;

            return T;
        }

/* START: fig4_36.txt */

        /*返回节点的高度*/
        static int
        Height( Position P )
        {
            if( P == NULL )
                return -1;
            else
                return P->Height;
        }
/* END */

        /*返回两个数的最大值*/
        static int
        Max( int Lhs, int Rhs )
        {
            return Lhs > Rhs ? Lhs : Rhs;
        }

/* START: fig4_39.txt */
        /* This function can be called only if K2 has a left child */
        /* Perform a rotate between a node (K2) and its left child */
        /* Update heights, then return new root */

        /* 
        左左(LL)情况的右旋 

            K2
           /                k1
          K1      =>       /  \
         /                k    k2
        k

        */
        static Position
        SingleRotateWithLeft( Position K2 )
        {
            Position K1;

            K1 = K2->Left;
            K2->Left = K1->Right;
            K1->Right = K2;

            K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
            K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

            return K1;  /* New root */
        }
/* END */

        /* This function can be called only if K1 has a right child */
        /* Perform a rotate between a node (K1) and its right child */
        /* Update heights, then return new root */

        /* 
        右右(RR)情况的左旋 

         k1
           \
            k2      =>       k2
              \             /  \
               k           k1   k


        */
        static Position
        SingleRotateWithRight( Position K1 )
        {
            Position K2;

            K2 = K1->Right;
            K1->Right = K2->Left;
            K2->Left = K1;

            K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
            K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

            return K2;  /* New root */
        }

/* START: fig4_41.txt */
        /* This function can be called only if K3 has a left */
        /* child and K3's left child has a right child */
        /* Do the left-right double rotation */
        /* Update heights, then return new root */

        /*
        
         左右(LR)情况的左右旋转
         
             k3             k3
            /              /
           k1    =>       k2    =>      k2
             \            /            /  \
              k2         k1           k1   k3

         */
        
        static Position
        DoubleRotateWithLeft( Position K3 )
        {
            /* Rotate between K1 and K2 */
            K3->Left = SingleRotateWithRight( K3->Left );

            /* Rotate between K3 and K2 */
            return SingleRotateWithLeft( K3 );
        }
/* END */

        /* This function can be called only if K1 has a right */
        /* child and K1's right child has a left child */
        /* Do the right-left double rotation */
        /* Update heights, then return new root */

        /*
        
         右左(RL)情况的右左旋转

           k1         k1
             \         \
              k3   =>  k2     =>       k2
             /           \            /  \
           k2             k3         k1   k3

         */
        
        static Position
        DoubleRotateWithRight( Position K1 )
        {
            /* Rotate between K3 and K2 */
            K1->Right = SingleRotateWithLeft( K1->Right );

            /* Rotate between K1 and K2 */
            return SingleRotateWithRight( K1 );
        }


/* START: fig4_37.txt */
        /*平衡树的插入*/
        AvlTree
        Insert( ElementType X, AvlTree T )
        {
            if( T == NULL )
            {
                /* Create and return a one-node tree */
                T = malloc( sizeof( struct AvlNode ) );
                if( T == NULL )
                    FatalError( "Out of space!!!" );
                else
                {
                    T->Element = X; T->Height = 0;
                    T->Left = T->Right = NULL;
                }
            }
            else
            if( X < T->Element )
            {
                T->Left = Insert( X, T->Left );
                if( Height( T->Left ) - Height( T->Right ) == 2 )
                    if( X < T->Left->Element )
                        T = SingleRotateWithLeft( T );
                    else
                        T = DoubleRotateWithLeft( T );
            }
            else
            if( X > T->Element )
            {
                T->Right = Insert( X, T->Right );
                if( Height( T->Right ) - Height( T->Left ) == 2 )
                    if( X > T->Right->Element )
                        T = SingleRotateWithRight( T );
                    else
                        T = DoubleRotateWithRight( T );
            }
            /* Else X is in the tree already; we'll do nothing */

            T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
            return T;
        }
/* END */

        AvlTree
        Delete( ElementType X, AvlTree T )
        {
            printf( "Sorry; Delete is unimplemented; %d remains\n", X );
            return T;
        }
  
        /*返回某节点的值*/
        ElementType
        Retrieve( Position P )
        {
            return P->Element;
        }


        //以下是补充
        //
        void PrintTree(AvlTree T)
        {
            if (T != NULL)
            {
                PrintTree(T->Left);
                printf("%3d", Retrieve(T));
                PrintTree(T->Right);
            }
        }

        AvlTree Remove(ElementType X, AvlTree T)
        {
              if(T == NULL)
                  return NULL;//没有找到要删除的值,do nothing
              if(X < T->Element)
              {
                  T->Left = Remove(X, T->Left);
                  if(Height(T->Right)-Height(T->Left)==2)
                  {
                      //右子树比左子树高2,那么在删除操作之前右子树比左子树高1,
                     //也就是说T的右子树必然不为空,甚至必然有非空子树(高度至少为1).
                     AvlTree s = T->Right;
                     if(Height(s->Left)>Height(s->Right))
                         T = DoubleRotateWithRight(T);//右双旋转
                     else
                         T = SingleRotateWithRight(T);//右单旋转
                 }
                 else
                     //不需要调整就满足平衡条件的话,只需要重新计算其高度就好
                     T->Height=Max(Height(T->Left),Height(T->Right))+1;
             }
             else if(X>T->Element)
             {

                 T->Right = Remove(X,T->Right);
                 if(Height(T->Left)-Height(T->Right)==2)
                 {
                     AvlTree s=T->Left;
                     if(Height(s->Right)>Height(s->Left))
                         T = DoubleRotateWithLeft(T);//左双旋转
                     else
                         T = SingleRotateWithLeft(T);//左单旋转
                 }
                 else
                     T->Height=Max(Height(T->Left),Height(T->Right))+1;
             }
             else
             {
                 if(T->Left&&T->Right)         //T的左右子树都非空,把Remove操作转移到只有一个非空子树的结点或者叶子结点上去
                 {
                     if( Height(T->Left) > Height(T->Right) )
                     //把Remove操作往更高的那颗子树上转移
                     {
                         //左子树中的最大值
                         T->Element=FindMax(T->Left)->Element;
                         T->Left = Remove(T->Element,T->Left);
                     }
                     else
                     {
                         //右子树中的最小值
                         T->Element=FindMin(T->Right)->Element;
                         T->Right = Remove(T->Element,T->Right);
                     }
                 }
                 else
                 {
                     AvlTree oldnode = T;
                     T=T->Left?T->Left:T->Right;
                     free(oldnode);
                 }
             }
            return T;
        }
