#include <stdio.h>
#include "hash_table.h"

// TODO(rename everything properly)
// TODO(write function for rehashing whole table)

int main(int argc, char const** argv)
{
    struct hashtable_t* hashtable_ptr = malloc(sizeof(struct hashtable_t*));
    int err = hash_table_init(10, &fnv_1a, hashtable_ptr);
    if (err != 0)
    {
        puts(strerror(errno));
        printf("%i\n", err);
    }

    err = hash_table_destroy(hashtable_ptr);
    if (err != 0)
    {
        puts(strerror(errno));
        printf("%i\n", err);
    }

    return 0;
}

