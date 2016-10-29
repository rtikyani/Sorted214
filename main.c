#include "sorted-list.h"

int compareString(void *c1, void *c2) {
    char *ptr1 = (char *) c1;
    char *ptr2 = (char *) c2;
    int i = strcmp(ptr1, ptr2);
    if (i < 0) { return -1; }
    if (i > 0) { return 1; }
    return 0;
}

void destroyString(void *data) {
    char *ptr = (char *) data;
    ptr = NULL;
    return;
}

void testStrings(SortedListPtr list) {
    char *s1 = "hello";
    char *s2 = "world";
    char *s3 = "abc";
    char *s4 = "def";

    void *v1 = (void *) s1;
    void *v2 = (void *) s2;
    void *v3 = (void *) s3;
    void *v4 = (void *) s4;

    SLInsert(list, v1);
    SLInsert(list, v2);
    SLInsert(list, v3);
    SLRemove(list, v3);
    SLInsert(list, v4);

    SortedListIteratorPtr list_iterator = SLCreateIterator(list);

    char *current = list_iterator->current->data;

    while(current != NULL) {
        printf("%s\n", current);
        current = SLNextItem(list_iterator);
    }

    SLDestroyIterator(list_iterator);

    return;
}

int compareInt(void *c1, void *c2) {
    int *ptr1 = (int *) c1;
    int *ptr2 = (int *) c2;


    if (*ptr1 > *ptr2) {
        return 1;
    } else if (*ptr1 < *ptr2) {
        return -1;
    } else if (*ptr1 == *ptr2) {
        return 0;
    }
    return 5;

}

void destroyInt(void *data) {
    int *ptr = (int *) data;
    free(ptr);
    return;
}

void testInt(SortedListPtr list) {

    return;
}

int main(int argc, char **argv) {
    CompareFuncT cInt = compareInt;
    DestructFuncT dInt = destroyInt;

    CompareFuncT cStr = compareString;
    DestructFuncT dStr = destroyString;

    SortedListPtr strList = SLCreate(cStr, dStr);
    SortedListPtr intList = SLCreate(cInt, dInt);

    testStrings(strList);
    testInt(intList);
    return 0;

}