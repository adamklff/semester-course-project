#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "login_record.h"

typedef struct Node {
    LoginRecord data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

void linked_list_init(LinkedList *list);
void linked_list_append(LinkedList *list, LoginRecord record);
int linked_list_remove_by_username(LinkedList *list, const char *username);
void linked_list_print(LinkedList *list);
void linked_list_free(LinkedList *list);

#endif
