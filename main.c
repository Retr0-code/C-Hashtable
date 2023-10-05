#include <stdio.h>
#include "hash_table.h"


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

    err = ht_emplace("test1", "1", hashtable_ptr);
    err = ht_emplace("test2", "2", hashtable_ptr);
    err = ht_emplace("test3", "3", hashtable_ptr);
    err = ht_emplace("test4", "4", hashtable_ptr);
    err = ht_emplace("test5", "5", hashtable_ptr);

    printf("%s =(%llu)=> %s\n", "test1", fnv_1a("test1") % hashtable_ptr->size, (char*)ht_get_elem("test1", hashtable_ptr));
    ht_remove("test1", hashtable_ptr);

    for (size_t i = 0; i < hashtable_ptr->size; i++)
    {
        if (hashtable_ptr->data[i] == NULL)
            printf("%llu => NULL\n", i);
        else
            printf("%llu => %s\n", i, (char*)hashtable_ptr->data[i]->value);
    }

    ht_destroy(hashtable_ptr);
    return 0;
}

