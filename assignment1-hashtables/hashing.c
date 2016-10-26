/*
hashing.c -- Code demonstrating hash tables
Author: David J. Bourke, Student Number: 12304135
Date started:   21st of October 2016
Date submitted: 28th of October 2016
Dependencies:   hashing_functions.h
Compile with $ gcc -o hash -std=c99 hashing_function.c
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_TEST_KEYS 997
#define MAX_KEY_LENGTH 16
// HASH_TABLE_SIZE_M must always be a prime for 100% coverage
#define HASH_TABLE_SIZE_M 997

// wrapper for index and # of collisions returned from probing functions
typedef struct probe_info {
    int index;
    int collisions;
} probe_info;

// Hash table
char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];
// Test strings
char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH];

// Returns a pseudorandom index position based on an input string
unsigned hash_index (const char *key) {
    unsigned index = 0;
	for (int i = 0; i < strlen(key); i++) {
        index += key[i] * i;
	}
    return index * 2;
}

// Returns a pseudorandom offset based on an input string
unsigned hash_offset (const char *key) {
    unsigned offset = 0;
    for (int i = 0; i < strlen(key); i++) {
        offset += key[i]; 
    }
    // Ensure that the offset is never a multiple of the has table size
    if (offset % HASH_TABLE_SIZE_M == 0) {
        offset = 3; // Ensures universal coverage
    }
    return offset;
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
    printf("Failed to insert %s, index: %d\n", key, index);
    dh_probe_info.index = -1;
    dh_probe_info.collisions = i;
    return dh_probe_info;
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colissions withexisting keys are dealt with using double hashing
probe_info table_probe_dh (const char *key, int table_size) {
    probe_info dh_probe_info;
    int index = hash_index(key) % table_size;
    int hash_off = hash_offset(key) % table_size;
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < table_size; i++) {
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
    printf("Failed to insert %s, index: %d, offset: %d\n", key, index, hash_off);
    dh_probe_info.index = -1;
    dh_probe_info.collisions = i;
    return dh_probe_info;
}

// generates a random string (used for testing)
void rand_string(char* dest_string, int str_len) {
    int rand_len;
    int min_len = 3;
    int min_char = 32, max_char = 126;  // Range of printable ASCII characters
    // Generate random string length
    rand_len = rand() % (str_len + 1 - min_len) + min_len;
    for (int c = 0; c < rand_len; c++) {
        // Generate random character in range of printable ASCII characters
        dest_string[c] = (char) (rand() % (max_char + 1 - min_char) + min_char);
    }
    dest_string[rand_len - 1] = '\0';   // Append null terminator
    return;
}

int main (void) {
    int total_collisions;
    // seed PRNG
    srand((int) time(NULL));
    probe_info temp_probe_info;
    // Initialise test_keys with random data
    for (int s = 0; s < NUM_TEST_KEYS; s++) {
        rand_string(test_strings[s], MAX_KEY_LENGTH);
    }


    /* Testing the linear probing method */
    total_collisions = 0;
    // Initialise all elements of hash_table to 0
    memcpy(hash_table, "", HASH_TABLE_SIZE_M * MAX_KEY_LENGTH);
    printf("Probing hash table for every test string using linear probing...\n");
    // Probe the hash table for every test_string using linear probing function
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
		temp_probe_info = table_probe_lp(test_strings[i], HASH_TABLE_SIZE_M);
        total_collisions += temp_probe_info.collisions;
	}
    printf("Total number of collisions:\t %d\n", total_collisions);
    printf("Average number of collisions:\t %lf\n", total_collisions / (double)NUM_TEST_KEYS);


    /* Testing the double hashing method */
    total_collisions = 0;   // Reset collision counter 
    // Reinitialise all elements of hash_table to 0
    memcpy(hash_table, "", HASH_TABLE_SIZE_M * MAX_KEY_LENGTH);
    printf("Probing hash table for every test string using double hashing...\n");
    // Probe the hash table for every test_string using double hashing probe function
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
		temp_probe_info = table_probe_dh(test_strings[i], HASH_TABLE_SIZE_M);
        total_collisions += temp_probe_info.collisions;
	}
    printf("Total number of collisions:\t %d\n", total_collisions);
    printf("Average number of collisions:\t %lf\n", total_collisions / (double)NUM_TEST_KEYS);

	return 0;
}