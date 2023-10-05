#include <stdio.h>
#include "hash_table.h"

int hash_table_init(size_t size, hash_func_t ht_func_ptr, hashtable_t* hash_table)
{
    if (hash_table == NULL || size == 0 || ht_func_ptr == NULL)
    {
        errno = EPERM;
        return -1;
    }

    hash_table->size = size;
    hash_table->hash_func = ht_func_ptr;

    hash_table->data = malloc(hash_table->size * sizeof(ht_node_t*));
    if (hash_table->data == NULL)
        return -4;

    for (size_t i = 0; i < hash_table->size; i++)
    {
        hash_table->data[i] = malloc(sizeof(ht_node_t));
        ht_node_init(hash_table->data[i]);
    }

    return 0;
}

int hash_table_emplace(const char* key, hashtable_t* hash_table)
{
    if (key == NULL || hash_table == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    if (hash_table->filled_nodes == hash_table->size - 1)
    {
        ht_resize(hash_table);
    }


}

int hash_table_destroy(hashtable_t* hash_table)
{
    for (size_t i = 0; i < hash_table->size; i++)
        ht_node_destroy_from_base(hash_table->data[i]);
    
    free(hash_table);
}

void ht_node_init(ht_node_t* node)
{
    node->value = NULL;
    node->key = NULL;
    node->next = NULL;
}

void ht_node_destroy_from_base(ht_node_t* base_node)
{
    if (base_node->next != NULL)
        ht_node_destroy_from_base(base_node->next);

    free(base_node);
}

void ht_node_rehash_from_base(
    ht_node_t* base_node,
    ht_node_t** nodes_space,
    hashtable_t* hash_table
    )
{
    if (base_node->next != NULL)
        ht_node_rehash_from_base(base_node, nodes_space, hash_table);

    size_t new_hash = (*hash_table->hash_func)(base_node->key) % hash_table->size;
    if (nodes_space[new_hash] != 0)
    nodes_space[] = base_node;
    base_node->next = NULL;
}

int ht_resize(hashtable_t* hash_table)
{
    size_t old_size = hash_table->size;
    hash_table->size *= 2;
    ht_node_t** new_data = malloc(hash_table->size * sizeof(ht_node_t*));

    for (size_t i = 0; i < hash_table->size; i++)
    {
        new_data[i] = malloc(sizeof(ht_node_t));
        ht_node_init(new_data[i]);
    }

    for (size_t i = 0; i < old_size; i++)
    {
        if (hash_table->data[i] == NULL)
            continue;
        
        new_data[(*hash_table->hash_func)(hash_table->data[i]->key) % hash_table->size] = hash_table->data[i];
    }
    // memcpy(new_data, hash_table->data, old_size);

    free(hash_table->data);
    hash_table->data = new_data;
    return 0;
}

size_t fnv_1a(const char* a)
{
    return 0;
}
