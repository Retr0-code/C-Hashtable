#include <stdio.h>
#include "hash_table.h"

int ht_init(size_t size, hash_func_t ht_func_ptr, hashtable_t* hash_table)
{
    if (hash_table == NULL || size == 0 || ht_func_ptr == NULL)
    {
        errno = EPERM;
        return -1;
    }

    hash_table->size = size;
    hash_table->filled_nodes = 0;
    hash_table->hash_func = ht_func_ptr;

    hash_table->data = malloc(hash_table->size * sizeof(ht_node_t*));
    if (hash_table->data == NULL)
        return -4;

    memset(hash_table->data, NULL, hash_table->size * sizeof(ht_node_t*));

    return 0;
}

int ht_emplace(const char* key, void* value, hashtable_t* hash_table)
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

    ht_node_t* new_node = malloc(sizeof(ht_node_t));
    if (new_node == NULL)
        return -3;

    ht_node_init(new_node);
    new_node->value = value;
    new_node->key = key;
    
    ht_insert_node(new_node, hash_table->data, hash_table);

    ++hash_table->filled_nodes;

    return 0;
}

void ht_destroy(hashtable_t* hash_table)
{
    for (size_t i = 0; i < hash_table->size; i++)
        if (hash_table->data[i] != NULL)
            ht_node_destroy_from_base(hash_table->data[i]);
    
    free(hash_table);
}

void ht_node_init(ht_node_t* node)
{
    node->value = NULL;
    node->key = NULL;
    node->next = NULL;
}

int ht_insert_node(const ht_node_t* node, ht_node_t** nodes_space, hashtable_t* hash_table)
{
    size_t new_hash = (*hash_table->hash_func)(node->key) % hash_table->size;
    if (nodes_space[new_hash] == NULL)
    {
        nodes_space[new_hash] = node;
        return 0;
    }

    ht_node_t* last_node = nodes_space[new_hash];
    while (last_node->next != NULL)
        last_node = last_node->next;

    last_node->next = node;
    return 1;
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
        ht_node_rehash_from_base(base_node->next, nodes_space, hash_table);

    ht_insert_node(base_node, nodes_space, hash_table);
    //size_t new_hash = (*hash_table->hash_func)(base_node->key) % hash_table->size;
    //if (nodes_space[new_hash] == NULL)
    //    nodes_space[new_hash] = base_node;

    base_node->next = NULL;
}

int ht_resize(hashtable_t* hash_table)
{
    size_t old_size = hash_table->size;
    hash_table->size *= 2;

    ht_node_t** new_data = malloc(hash_table->size * sizeof(ht_node_t*));
    if (new_data == NULL)
        return -1;

    memset(new_data, NULL, hash_table->size * sizeof(ht_node_t*));

    for (size_t i = 0; i < old_size; i++)
    {
        if (hash_table->data[i] == NULL)
            continue;
        
        ht_node_rehash_from_base(hash_table->data[i], new_data, hash_table);
        //new_data[(*hash_table->hash_func)(hash_table->data[i]->key) % hash_table->size] = hash_table->data[i];
    }
    // memcpy(new_data, hash_table->data, old_size);

    //free(hash_table->data);
    hash_table->data = new_data;
    return 0;
}

size_t fnv_1a(const char* a)
{
    return 0;
}
