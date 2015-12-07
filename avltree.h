        /*平衡树的声明*/
        typedef int ElementType;

/* START: fig4_35.txt */
        #ifndef _AvlTree_H
        #define _AvlTree_H

        struct AvlNode;
        typedef struct AvlNode *Position;
        typedef struct AvlNode *AvlTree;

        AvlTree MakeEmpty( AvlTree T );
        Position Find( ElementType X, AvlTree T );
        Position FindMin( AvlTree T );
        Position FindMax( AvlTree T );
        AvlTree Insert( ElementType X, AvlTree T );
        AvlTree Delete( ElementType X, AvlTree T );
        ElementType Retrieve( Position P );

        //以下是补充
        void PrintTree(AvlTree T);
        AvlTree Remove(const ElementType X, AvlTree T);
        AvlTree Remove( ElementType X, AvlTree T );

        #endif  /* _AvlTree_H */
/* END */
