//
// Created by wein on 3/3/18.
//

#include "cciList.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

typedef struct cciListNode {
    struct cciListNode *prev;
    struct cciListNode *next;
    int value;
} cciListNode_t;

cciList_t *NewList() {
    cciList_t *l = malloc(sizeof(cciList_t));
    memset(l, 0, sizeof(cciList_t));
    return l;
}

void DeleteList(cciList_t *l) {
    cciListNode_t *curr = l->head;
    while (curr) {
        l->head = l->head->next;
        free(curr);
        curr = l->head;
    }
    free(l);
}

cciListNode_t *createNode() {
    cciListNode_t *n = malloc(sizeof(cciListNode_t));
    memset(n, 0, sizeof(cciListNode_t));
    return n;
}

// prev n next
// prev   next
void deleteNode(cciList_t *l, cciListNode_t *prev, cciListNode_t *n, cciListNode_t *next) {
    if (prev) {
        prev->next = next;
    } else {
        l->head = next;
    }
    if (next) {
        next->prev = prev;
    } else {
        l->tail = prev;
    }
    free(n);
    l->size--;
}

CCILIST_ERROR validateIndex(cciList_t *l, int index) {
    if (index < 0 || index > l->size - 1) {
        return CCILIST_INDEX_ERROR;
    }
    return CCILIST_NO_ERROR;
}

cciListNode_t *node(cciList_t *l, int index) {
    cciListNode_t *curr = l->head;
    for (int i=0; i < index; ++i) {
        curr = curr->next;
    }
    assert(curr); // should not happen
    return curr;
}

// prev         next
// prev newNode next
void insert(cciList_t *l, cciListNode_t *prev, cciListNode_t *newNode, cciListNode_t *next) {
    if (prev) {
        prev->next = newNode;
    } else {
        l->head = newNode;
    }
    if (next) {
        next->prev = newNode;
    } else {
        l->tail = newNode;
    }
    newNode->prev = prev;
    newNode->next = next;
    l->size++;
}

void AppendInt(cciList_t *l, int v) {
    cciListNode_t *n = createNode();
    n->value = v;
    if (l->size == 0) {
        insert(l, NULL, n, NULL);
    } else {
        insert(l, l->tail, n, NULL);
    }
}

int GetInt(cciList_t *l, int index) {
    l->errCode = validateIndex(l, index);
    if (!l->errCode) {
        return node(l, index)->value;
    }
    return 0;
}

void InsertInt(cciList_t *l, int index, int value) {
    cciListNode_t *prev = NULL;
    cciListNode_t *newNode = NULL;
    l->errCode = validateIndex(l, index);
    if (!l->errCode) {
        prev = node(l, index);
        newNode = createNode();
        newNode->value = value;
        insert(l, prev, newNode, prev->next);
    }
}

void Remove(cciList_t *l, int index) {
    cciListNode_t *n = NULL;
    l->errCode = validateIndex(l, index);
    if (!l->errCode) {
        n = node(l, index);
        deleteNode(l, n->prev, n, n->next);
    }
}
