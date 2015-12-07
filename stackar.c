        #include "stackar.h"
        #include "fatal.h"
        #include <stdlib.h>

        #define EmptyTOS ( -1 )
        #define MinStackSize ( 5 )

        struct StackRecord
        {
            int Capacity;
            int TopOfStack;
            ElementType *Array;
        };

/* START: fig3_48.txt */

        /* 判断栈是否为空 */
        int
        IsEmpty( Stack S )
        {
            return S->TopOfStack == EmptyTOS;
        }
/* END */

        /*判断栈是否满了 */
        int
        IsFull( Stack S )
        {
            return S->TopOfStack == S->Capacity - 1;
        }

/* START: fig3_46.txt */

        /* 创建一个空栈 */
        Stack
        CreateStack( int MaxElements )
        {
            Stack S;

/* 1*/      if( MaxElements < MinStackSize )
/* 2*/          Error( "Stack size is too small" );

/* 3*/      S = malloc( sizeof( struct StackRecord ) );
/* 4*/      if( S == NULL )
/* 5*/          FatalError( "Out of space!!!" );

/* 6*/      S->Array = malloc( sizeof( ElementType ) * MaxElements );
/* 7*/      if( S->Array == NULL )
/* 8*/          FatalError( "Out of space!!!" );
/* 9*/      S->Capacity = MaxElements;
/*10*/      MakeEmpty( S );

/*11*/      return S;
        }
/* END */

/* START: fig3_49.txt */

        /* 使栈顶指向-1，即空栈 */
        void
        MakeEmpty( Stack S )
        {
            S->TopOfStack = EmptyTOS;
        }
/* END */

/* START: fig3_47.txt */

        /* 释放栈 */
        void
        DisposeStack( Stack S )
        {
            if( S != NULL )
            {
                free( S->Array );
                free( S );
            }
        }
/* END */

/* START: fig3_50.txt */

        /* 入栈 */
        void
        Push( ElementType X, Stack S )
        {
            if( IsFull( S ) )
                Error( "Full stack" );
            else
                S->Array[ ++S->TopOfStack ] = X;
        }
/* END */


/* START: fig3_51.txt */

        /* 返回栈顶元素 */
        ElementType
        Top( Stack S )
        {
            if( !IsEmpty( S ) )
                return S->Array[ S->TopOfStack ];
            Error( "Empty stack" );
            return 0;  /* Return value used to avoid warning */
        }
/* END */

/* START: fig3_52.txt */

        /* 出栈 */
        void
        Pop( Stack S )
        {
            if( IsEmpty( S ) )
                Error( "Empty stack" );
            else
                S->TopOfStack--;
        }
/* END */

/* START: fig3_53.txt */

        /* 返回栈顶元素和出栈 */
        ElementType
        TopAndPop( Stack S )
        {
            if( !IsEmpty( S ) )
                return S->Array[ S->TopOfStack-- ];
            Error( "Empty stack" );
            return 0;  /* Return value used to avoid warning */
        }
/* END */
