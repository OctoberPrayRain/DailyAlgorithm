#include <stdio.h>
#include "data-struct/2-LinkedList.c"

int main(void) {
        LinkedList L = NULL;
        ElemType value = 0;

        if (!InitList(&L)) {
                printf("InitList failed\n");
                return 1;
        }

        printf("ListEmpty: %s\n", ListEmpty(L) ? "true" : "false");
        printf("ListLength: %d\n", ListLength(L));

        printf("Insert 10 at 1: %s\n", ListInsert(L, 1, 10) ? "true" : "false");
        printf("Insert 20 at 2: %s\n", ListInsert(L, 2, 20) ? "true" : "false");
        printf("Insert 15 at 2: %s\n", ListInsert(L, 2, 15) ? "true" : "false");
        printf("Current list: ");
        PrintList(L);

        if (GetElem(L, 2, &value)) {
                printf("GetElem(2): %d\n", value);
        } else {
                printf("GetElem(2) failed\n");
        }

        printf("LocateElem(20): %d\n", LocateElem(L, 20));
        printf("LocateElem(99): %d\n", LocateElem(L, 99));
        printf("ListLength: %d\n", ListLength(L));

        printf("Insert 30 at 5: %s\n", ListInsert(L, 5, 30) ? "true" : "false");
        printf("Insert 30 at 4: %s\n", ListInsert(L, 4, 30) ? "true" : "false");
        printf("Current list: ");
        PrintList(L);

        DestroyList(&L);
        printf("After destroy, ListEmpty: %s\n", ListEmpty(L) ? "true" : "false");
        PrintList(L);

        return 0;
}
