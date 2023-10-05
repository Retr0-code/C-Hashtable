#include <stdio.h>
#include "hash_table.h"

// TODO(rename everything properly)
// TODO(write function for rehashing whole table)

int main(int argc, char const** argv)
{
    hashtable_t* hashtable_ptr = malloc(sizeof(hashtable_t));
    if (hashtable_ptr == NULL)
    {
        puts("Unable to allocate memory");
        return -1;
    }

    int err = ht_init(2, &fnv_1a, hashtable_ptr);
    if (err != 0)
    {
        puts(strerror(errno));
        printf("%i\n", err);
        return -1;
    }

    err = ht_emplace("test", "1", hashtable_ptr);
    err = ht_emplace("test1", "2", hashtable_ptr);
    err = ht_emplace("test2", "3", hashtable_ptr);
    err = ht_emplace("test3", "4", hashtable_ptr);
    err = ht_emplace("test4", "5", hashtable_ptr);
    if (err != 0)
    {
        puts(strerror(errno));
        printf("%i\n", err);
    }

    ht_destroy(hashtable_ptr);
    return 0;
}

