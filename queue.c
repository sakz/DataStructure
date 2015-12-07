        #include "queue.h"
        #include "fatal.h"
        #include <stdlib.h>

        #define MinQueueSize ( 5 )

        /*列队结构的定义*/
        struct QueueRecord
        {
            int Capacity;
            int Front;
            int Rear;
            int Size;
            ElementType *Array;
        };

/* START: fig3_58.txt */

        /*判断队列是否为空*/
        int
        IsEmpty( Queue Q )
        {
            return Q->Size == 0;
        }
/* END */
        
        /*判断队列是否满*/
        int
        IsFull( Queue Q )
        {
            return Q->Size == Q->Capacity;
        }

        /*创建空队列*/
        Queue
        CreateQueue( int MaxElements )
        {
            Queue Q;

/* 1*/      if( MaxElements < MinQueueSize )
/* 2*/          Error( "Queue size is too small" );

/* 3*/      Q = malloc( sizeof( struct QueueRecord ) );
/* 4*/      if( Q == NULL )
/* 5*/          FatalError( "Out of space!!!" );

/* 6*/      Q->Array = malloc( sizeof( ElementType ) * MaxElements );
/* 7*/      if( Q->Array == NULL )
/* 8*/          FatalError( "Out of space!!!" );
/* 9*/      Q->Capacity = MaxElements;
/*10*/      MakeEmpty( Q );

/*11*/      return Q;
        }

/* START: fig3_59.txt */

        /*初始化队列*/
        void
        MakeEmpty( Queue Q )
        {
            Q->Size = 0;
            Q->Front = 1;
            Q->Rear = 0;
        }
/* END */

        /*释放队列内存*/
        void
        DisposeQueue( Queue Q )
        {
            if( Q != NULL )
            {
                free( Q->Array );
                free( Q );
            }
        }

/* START: fig3_60.txt */

        /* 给出Q->Front、Q->Rear自增1后的数组下标值 */
        static int
        Succ( int Value, Queue Q )
        {
            if( ++Value == Q->Capacity )
                Value = 0;
            /*上面两行的作用是只要Front和Rear到达数组的尾端，它就又绕到开头，这叫做循环数组实现。*/
            return Value;
        }
        /*
         1：加了static后表示该函数失去了全局可见性，只在该函数所在的文件作用域内可见

         2：当函数声明为static以后,编译器在该目标编译单元内只含有该函数的入口地址,
         没有函数名,其它编译单元便不能通过该函数名来调用该函数，这也是对1的解析与说明

         3：所以queue.h头文件中不需要声明
         */


        /* 入队 */
        void
        Enqueue( ElementType X, Queue Q )
        {
            if( IsFull( Q ) )
                Error( "Full queue" );
            else
            {
                Q->Size++;
                Q->Rear = Succ( Q->Rear, Q );
                Q->Array[ Q->Rear ] = X;
            }
        }
/* END */


        /* 返回队头元素，但不出队 */
        ElementType
        Front( Queue Q )
        {
            if( !IsEmpty( Q ) )
                return Q->Array[ Q->Front ];
            Error( "Empty queue" );
            return 0;  /* Return value used to avoid warning */
        }

        /* 出队 */
        void
        Dequeue( Queue Q )
        {
            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                Q->Front = Succ( Q->Front, Q );
            }
        }

        /* 返回队头元素，并且出队 */
        ElementType
        FrontAndDequeue( Queue Q )
        {
            ElementType X = 0;

            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                X = Q->Array[ Q->Front ];
                Q->Front = Succ( Q->Front, Q );
            }
            return X;
        }
