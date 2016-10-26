/*
hashing_functions.h -- Code demonstrating hash tables
Author: David J. Bourke, Student Number: 12304135
Date started:   21st of October 2016
Date submitted: 28th of October 2016
Compile with $ gcc -o hash -std=c99 hashing_function.c
*/

#include <string.h>

#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 40

// This is our actual hash table
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];

// wrapper for index and # of collisions returned from probing functions
typedef struct probe_info {
    int index;
    int collisions;
} probe_info;

// Returns a pseudorandom index position based on an input string
int hash_index (const char *key) {
    int index = 0;
	for (int i = 0; i < strlen(key); i++) {
        index += key[i] * i;
	}
    return index;
}

// Returns a pseudorandom offset based on an input string
int hash_offset (const char *key) {
    int offset = 0;
    for (int i = 0; i < strlen(key); i++) {
        offset += key[i]; 
    }
    return offset * 2 + 1; // Always an odd number
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colisions with existing keys are dealt with using linear probing
probe_info table_probe_lp (const char *key, int table_size) {
    probe_info dh_probe_info;
    int index = hash_index(key);
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < table_size; i++) {
        index_mod_ts = (index + i) % table_size;
        // if an empty bucket is found, insert the key and return the index
        if (!hash_table[index_mod_ts][0]) {
            strcpy(hash_table[index_mod_ts], key);
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
        // if the key exists in the table already, return the index
        if (!strcmp(key, hash_table[index_mod_ts])) {
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
    }
    // If no empty bucket is found, return -1
    printf("Failed to insert %s\n", key);
    dh_probe_info.index = -1;
    dh_probe_info.collisions = i;
    return dh_probe_info;
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colissions withexisting keys are dealt with using double hashing
probe_info table_probe_dh (const char *key, int table_size) {
    int max_loops = 100;    // Prevents infinite loops
    probe_info dh_probe_info;
    int index = hash_index(key);
    int hash_off = hash_offset(key);
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < max_loops; i++) {
        // h(k,i) = (f(k) + i * g(k))
        index_mod_ts = (index + i * hash_off) % table_size;
        // if an empty bucket is found, insert the key and return the index
        if (!hash_table[index_mod_ts][0]) {
            strcpy(hash_table[index_mod_ts], key);
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
        // if the key exists in the table already, return the index
        if (!strcmp(key, hash_table[index_mod_ts])) {
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
    }
    // If no empty bucket is found, return -1 as index
    printf("Failed to insert %s\n", key);
    dh_probe_info.index = -1;
    dh_probe_info.collisions = i;
    return dh_probe_info;
}