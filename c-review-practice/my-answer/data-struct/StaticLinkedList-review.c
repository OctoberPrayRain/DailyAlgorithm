#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct Node {
        ElemType data;
        int next;
} Node;


/*
head表示第一个存放数据的节点，在数组中的下标位置
free表示第一个空闲的节点，在数组中的下标位置
*/
typedef struct StaticList {
        Node nodes[MAX_SIZE];
        int head;
        int free;
} StaticList;

void InitList(StaticList *L) {
        L->head = -1;
        L->free = 0;

        for (int i = 0; i < MAX_SIZE - 1; i ++) {
                L->nodes[i].next = i - 1;
        }    // 现在整个链表，都是以 free 为首的链表，说明整个静态链表都是空的
}

bool MallocNode(StaticList *L) {
        if (L->free == -1) {
                return false;
        }    // L->free == -1 说明没有静态表没有空余了

        
}
