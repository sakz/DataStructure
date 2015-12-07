        #include "stackli.h"
        #include "fatal.h"
        #include <stdlib.h>

        struct Node
        {
            ElementType Element;
            PtrToNode   Next;
        };

/* START: fig3_40.txt */

        /* 判断栈是否为空 */
        int
        IsEmpty( Stack S )
        {
            return S->Next == NULL;
        }
/* END */

/* START: fig3_41.txt */

        /* 创建一个空栈 */
        Stack
        CreateStack( void )
        {
            Stack S;

            S = malloc( sizeof( struct Node ) );
            if( S == NULL )
                FatalError( "Out of space!!!" );
            S->Next = NULL;
            MakeEmpty( S );
            return S;
        }

        /* 使栈为空 */
        void
        MakeEmpty( Stack S )
        {
            if( S == NULL )
                Error( "Must use CreateStack first" );
            else
                while( !IsEmpty( S ) )
                    Pop( S );
        }
/* END */

         /* 释放栈 */
        void
        DisposeStack( Stack S )
        {
            MakeEmpty( S );
            free( S );
        }

/* START: fig3_42.txt */

        /* 入栈 */
        void
        Push( ElementType X, Stack S )
        {
            PtrToNode TmpCell;

            TmpCell = malloc( sizeof( struct Node ) );
            if( TmpCell == NULL )
                FatalError( "Out of space!!!" );
            else
            {
                TmpCell->Element = X;
                TmpCell->Next = S->Next;
                S->Next = TmpCell;
            }
        }
        /*
        有头节点，栈顶是第一个节点，入栈是插到第一个节点前面，变成第一个节点
        这样出栈方便
        */
       
/* END */

/* START: fig3_43.txt */

        /* 返回栈顶元素 */
        ElementType
        Top( Stack S )
        {
            if( !IsEmpty( S ) )
                return S->Next->Element;
            Error( "Empty stack" );
            return 0;  /* Return value used to avoid warning */
        }
/* END */

/* START: fig3_44.txt */
        
        /* 出栈 */
        void
        Pop( Stack S )
        {
            PtrToNode FirstCell;

            if( IsEmpty( S ) )
                Error( "Empty stack" );
            else
            {
                FirstCell = S->Next;
                S->Next = S->Next->Next;
                free( FirstCell );
            }
        }
/* END */
