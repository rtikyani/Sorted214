#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
    SortedListPtr list = (SortedListPtr) malloc(sizeof(struct SortedList));
    list->head = NULL;
    list->cf = cf;
    list->df = df;

    return list;
}

void SLDestroy(SortedListPtr list) {
    node *ptr = list->head;
    node *prev = list->head;

    while (prev != NULL) {
        ptr = ptr->next;
        free(prev);
        prev = ptr;
    }
    free(list);
}

int SLInsert(SortedListPtr list, void *newObj) {
    node *ptr = list->head;
    node *prev = list->head;
    int cmp = 2;

    if (ptr == NULL) {
        //insert at head
        node *newNode = (node *) malloc(sizeof(node));
        newNode->data = newObj;
        newNode->next = NULL;

        list->head = newNode;
        return 1;
    }
    while (ptr != NULL) {
        cmp = list->cf((ptr->data), newObj);

        if (cmp == -1) {
            //newObj data is larger
            prev = ptr;
            ptr = ptr->next;

            continue;
        } else if (cmp == 0) {
            //data is equal, don't add
            return 0;
        } else {
            //new Obj is smaller, add here
            node *newNode = (node *) malloc(sizeof(node));
            newNode->data = newObj;
            newNode->next = ptr;
            if (list->cf((ptr->data), (list->head)->data) == 0) {
                list->head = newNode;
                return 1;
            }
            prev->next = newNode;
            return 1;
        }
    }
    //add to end of list
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = newObj;
    newNode->next = NULL;
    prev->next = newNode;
    return 1;

}

int SLRemove(SortedListPtr list, void *newObj) {
    node *ptr = list->head;
    node *prev = list->head;

    int cmp = 2;

    if (ptr == NULL) {
        //list is empty
        return 0;
    }

    cmp = list->cf((ptr->data), newObj);
    if (cmp == 0) {
        //remove head

        list->head = ptr->next;
        list->df((ptr->data));
        free(ptr);
        return 1;
    }
    ptr = ptr->next;
    while (ptr != NULL) {
        cmp = list->cf((ptr->data), newObj);
        if (cmp == 0) {
            //data found, remove from list
            prev->next = ptr->next;
            list->df((ptr->data));
            free(ptr);
            return 1;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    return 0; //item not found
}

/*
 * Creates a sorted list iterator, given the list.
 */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
    SortedListIteratorPtr iterator = malloc(sizeof(SortedListIteratorPtr));

    if (list == NULL) { return NULL; }

    iterator->current = list->head;
    return iterator;
}

/*
 * Destroys a sorted list iterator.
 */
void SLDestroyIterator(SortedListIteratorPtr iterator) {
    free(iterator);
}

/*
 * Gets the next item in the sorted list iterator, and sets the new current index.
 */
void *SLNextItem(SortedListIteratorPtr iterator) {
    if (iterator->current != NULL) {

        node *next_node = iterator->current->next;

        if (next_node != NULL) {
            iterator->current = next_node;
            return next_node->data;
        }

    }
    return NULL;
}

/*
 * Gets the value of the node that the sorted list iterator is currently pointing to.
 */
void *SLGetItem(SortedListIteratorPtr iterator) {

    if (iterator->current != NULL) {
        if (iterator->current->data != NULL) {
            return iterator->current->data;
        }
    }

    return NULL;
}