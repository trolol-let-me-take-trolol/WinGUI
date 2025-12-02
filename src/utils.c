#include "utils.h"
#include <stdlib.h>

List* list_create(int capacity) {
    List *list=malloc(sizeof(List));
    if (list==NULL) return NULL;
    list->count=0;
    list->capacity=capacity>0 ? capacity : 4;
    list->items=malloc(sizeof(void*)*list->capacity);
    if (list->items==NULL) {
        free(list);
        return NULL;
    }
    return list;
}

int list_append(List *list,void *item) {
    if (list->count>=list->capacity) {
        int new_capacity=list->capacity*2;
        void **new_items=realloc(list->items,sizeof(void*)*new_capacity);
        if (!new_items) return -1;
        list->items=new_items;
        list->capacity=new_capacity;
    }
    list->items[list->count++]=item;
    return list->count-1;
}

void* list_get(List *list,int index){
    if (list==NULL || index<0 || index>=list->count) return NULL;
    return list->items[index];
}

int list_remove(List *list,int index) {
    if (list==NULL || index<0 || index>=list->count) return -1;
    for (int i=index;i<list->count-1;i++) {
        list->items[i]=list->items[i+1];
    }
    list->count--;
    return list->count;
}

void list_free(List *list) {
    free(list->items);
    free(list);
}
