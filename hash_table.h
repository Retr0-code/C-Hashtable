#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef size_t (*hash_func_t)(const char*);

typedef struct ht_node_t
{
    void* value;
    const char* key;
    struct ht_node_t* next;
} ht_node_t;

typedef struct hashtable_t
{
    size_t size;
    size_t filled_nodes;
    hash_func_t hash_func;
    struct ht_node_t** data;
} hashtable_t;

// Initializes hash table of specific size with specific hash function
int ht_init(
    size_t size,
    hash_func_t ht_func_ptr,
    hashtable_t* hash_table
    );

// Adds new element to hashtable
int ht_emplace(const char* key, void* value, hashtable_t* hash_table);

// Removes element from hashtable
int ht_remove_elem(const char* key, hashtable_t* hash_table);

// Properly frees memory of hashtable
void ht_destroy(hashtable_t* hash_table);

// Initializes node with NULLs
void ht_node_init(ht_node_t* node);

// Returns zero if added directly to a table and 1 if added to linked list
int ht_insert_node(const ht_node_t* node, ht_node_t** nodes_space, hashtable_t* hash_table);

// Destroys all nodes including base node
void ht_node_destroy_from_base(ht_node_t* base_node);

// Rehashes all nodes in given linked list to new space
void ht_node_rehash_from_base(
    ht_node_t* base_node,
    ht_node_t** nodes_space,
    hashtable_t* hash_table
    );

int ht_resize(hashtable_t* hash_table);

// Default hashing function
size_t fnv_1a(const char*);

#endif
