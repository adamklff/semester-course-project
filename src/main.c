#include "array_list.h"
#include "config.h"
#include "linked_list.h"

#include <stdio.h>
#include <string.h>

static int parse_record(char *line, LoginRecord *record)
{
    char *timestamp = line;
    char *fields[] = {record->username, record->ip};
    const size_t limits[] = {sizeof record->username, sizeof record->ip};

    char *separator = strchr(line, ',');
    if (!separator)
        return 0;
    *separator = '\0';
    size_t length = strlen(timestamp);
    if (length != 16 && length != 19)
        return 0;
    memcpy(record->timestamp, timestamp, length + 1);

    for (size_t i = 0; i < sizeof fields / sizeof fields[0]; ++i) {
        char *field = separator + 1;
        separator = strchr(field, ',');
        if (!separator)
            return 0;
        *separator = '\0';
        length = strlen(field);
        if (!length || length >= limits[i])
            return 0;
        memcpy(fields[i], field, length + 1);
    }

    const char *result = separator + 1;
    if (strcmp(result, "0") && strcmp(result, "1"))
        return 0;
    record->success = result[0] == '1';
    return 1;
}

static void report_failures(const ArrayList *records)
{
    for (int i = 0; i < records->size; ++i) {
        const LoginRecord *record = &records->data[i];
        if (record->success)
            continue;

        int count = 0;
        for (int j = 0; j <= i; ++j) {
            const LoginRecord *previous = &records->data[j];
            if (!previous->success && strcmp(previous->username, record->username) == 0)
                ++count;
        }
        if (count == MAX_FAILED_ATTEMPTS)
            printf("Alert: %s reached %d failed attempts\n", record->username, count);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3 || (argc == 3 && strcmp(argv[2], "--list"))) {
        fprintf(stderr, "Usage: %s INPUT.csv [--list]\n", argv[0]);
        return 2;
    }
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror(argv[1]);
        return 1;
    }

    ArrayList records;
    array_init(&records, 16);
    char line[256];
    unsigned long line_number = 0;
    int status = 0;
    while (fgets(line, sizeof line, input)) {
        ++line_number;
        if (!strchr(line, '\n') && !feof(input)) {
            fprintf(stderr, "Line %lu is too long\n", line_number);
            status = 1;
            break;
        }
        line[strcspn(line, "\r\n")] = '\0';
        if (!*line || (line_number == 1 && !strcmp(line, "timestamp,username,ip,success")))
            continue;

        LoginRecord record = {0};
        if (!parse_record(line, &record)) {
            fprintf(stderr, "Invalid input on line %lu\n", line_number);
            status = 1;
            break;
        }

        int prior_size = records.size;
        array_insert(&records, record);
        if (records.size == prior_size) {
            fputs("Could not store login record\n", stderr);
            status = 1;
            break;
        }
    }
    if (ferror(input)) {
        perror(argv[1]);
        status = 1;
    }
    fclose(input);

    if (!status) {
        printf("Analyzed %d login records\n", records.size);
        report_failures(&records);

        if (argc == 3) {
            Node *head = NULL;
            for (int i = records.size; i > 0; --i) {
                Node *previous = head;
                list_insert(&head, records.data[i - 1]);
                if (head == previous) {
                    status = 1;
                    break;
                }
            }
            if (!status)
                list_print(head);
            list_free(head);
        }
    }
    array_free(&records);
    return status;
}
