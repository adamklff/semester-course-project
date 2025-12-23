#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "login_record.h"
#include <stddef.h>

typedef struct {
    LoginRecord *data;
    size_t size;
    size_t capacity;
} ArrayList;

void array_list_init(ArrayList *list);
void array_list_add(ArrayList *list, LoginRecord record);
void array_list_remove_at(ArrayList *list, size_t index);
LoginRecord* array_list_get(ArrayList *list, size_t index);
void array_list_free(ArrayList *list);

#endif
