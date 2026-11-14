#include "array_list.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_init(ArrayList *list, int capacity)
{
    list->data = capacity > 0 ? calloc((size_t)capacity, sizeof *list->data) : NULL;
    list->capacity = list->data ? capacity : 0;
    list->size = 0;
}

void array_insert(ArrayList *list, LoginRecord record)
{
    if (list->size == list->capacity) {
        if (list->capacity > INT_MAX / 2)
            return;
        int capacity = list->capacity ? list->capacity * 2 : 10;
        LoginRecord *data = realloc(list->data, (size_t)capacity * sizeof *data);
        if (!data)
            return;

        list->data = data;
        list->capacity = capacity;
    }
    list->data[list->size++] = record;
}

void array_delete(ArrayList *list, int index)
{
    if (index < 0 || index >= list->size)
        return;
    size_t remaining = (size_t)(list->size - index - 1);
    memmove(&list->data[index], &list->data[index + 1], remaining * sizeof *list->data);
    --list->size;
}

void array_print(const ArrayList *list)
{
    for (int i = 0; i < list->size; ++i) {
        const LoginRecord *record = &list->data[i];
        printf("%s %s %s %d\n", record->timestamp, record->username,
               record->ip, record->success);
    }
}

void array_free(ArrayList *list)
{
    free(list->data);
    *list = (ArrayList){0};
}
