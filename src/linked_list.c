#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void linked_list_init(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

void linked_list_append(LinkedList *list, LoginRecord record) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = record;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    list->size++;
}

int linked_list_remove_by_username(LinkedList *list, const char *username) {
    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.username, username) == 0) {
            if (prev == NULL) list->head = current->next;
            else prev->next = current->next;
            
            free(current);
            list->size--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void linked_list_print(LinkedList *list) {
    Node *temp = list->head;
    while (temp != NULL) {
        printf("[%s] %s (Success: %d)\n", temp->data.timestamp, temp->data.username, temp->data.success);
        temp = temp->next;
    }
}

void linked_list_free(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}
