/*
hashing.c -- Code demonstrating hash tables & measuring collision rates
Author: David J. Bourke, Student Number: 12304135
Date started:   21st of October 2016
Date submitted: 30th of October 2016
Dependencies:   hashing_functions.h
Compile with $ gcc hashing.c -o3 -std=c99 -o hash
The hash table is stored in a global char array declared on line 30
The insertion & searching the hash table can be performed using the probe_table functions
This code runs to completion within 40 seconds on an i7-4710MQ
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// For good performance, the table 
#define NUM_TEST_KEYS 9973
#define MAX_KEY_LENGTH 16
// HASH_TABLE_SIZE_M must always be a prime for 100% coverage
#define HASH_TABLE_SIZE_M 9973

// wrapper for index and # of collisions returned from probing functions
typedef struct probe_info {
    int index;
    int collisions;
} probe_info;

char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];
char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH];

// Returns a pseudorandom index position based on an input string
static inline unsigned hash_index (const char *key, int table_size) {
    unsigned index = 0;
	for (int i = 0; i < strlen(key); i++) {
        index += key[i] * (i + 1);
	}
    // Comparison + misbranch is less expensive than modulo
    if (index >= table_size) {
        return index % table_size;
    } else {
        return index;
    }
}

// Returns a pseudorandom offset based on an input string
static inline unsigned hash_offset (const char *key, int table_size) {
    unsigned offset = 0;
    for (int i = 0; i < strlen(key); i++) {
        offset += key[i]; 
    }
    // Ensure that the offset is never a multiple of the hash table size
    if (offset % table_size == 0) {
        offset = 3; // Ensures universal coverage
    }
    return offset;
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colisions with existing keys are dealt with using linear probing
static inline probe_info table_probe_lp (const char *key, int table_size, int insert) {
    probe_info lp_probe_info;
    int index = hash_index(key, table_size);
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < table_size; i++) {
        index_mod_ts = index + i;
        if (index + i >= table_size) {  // This comparison is cheaper than modulus
            index_mod_ts %= table_size;
        }
        // if an empty bucket is found, insert the key if insert is set
        // return the index regardless of whether insert is set or not
        if (!hash_table[index_mod_ts][0]) {
            if (insert) {
                strcpy(hash_table[index_mod_ts], key);
            }
            lp_probe_info.index = index_mod_ts;
            lp_probe_info.collisions = i;
            return lp_probe_info;
        }
        // if the key exists in the table already, return the index
        if (!strcmp(key, hash_table[index_mod_ts])) {
            lp_probe_info.index = index_mod_ts;
            lp_probe_info.collisions = i;
            return lp_probe_info;
        }
    }
    // If no empty bucket is found, return -1
    printf("Failed to insert %s, index: %d\n", key, index);
    lp_probe_info.index = -1;
    lp_probe_info.collisions = i;
    return lp_probe_info;
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colissions withexisting keys are dealt with using double hashing
static inline probe_info table_probe_dh (const char *key, int table_size, int insert) {
    probe_info dh_probe_info;
    int index = hash_index(key, table_size);
    int hash_off = hash_offset(key, table_size);
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < table_size; i++) {
        // h(k,i) = (f(k) + i * g(k))
        index_mod_ts = (index + i * hash_off);
        if (index_mod_ts >= table_size) {   // Comparison is cheaper than modulo
            index_mod_ts %= table_size;
        }
        // if an empty bucket is found, insert the key and return the index
        if (!hash_table[index_mod_ts][0]) {
            if (insert) {
                strcpy(hash_table[index_mod_ts], key);
            }
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
static inline void rand_string (char* dest_string, int str_len) {
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

// Returns the average collision rate, takes a number of trials as input
// "double_hash" argument tells the function whether or not to use double hashing
static inline double collision_test (int num_of_trials, int double_hash) {
    int total_collisions;
    double average_collisions;
    probe_info temp_probe_info;

    // Initialise test_keys with random data
    for (int s = 0; s < NUM_TEST_KEYS; s++) {
        rand_string(test_strings[s], MAX_KEY_LENGTH);
    }

    total_collisions = 0;
    // Probe the hash table for every test_string using linear probing function
	for (int i = 0; i < num_of_trials; i++) {
        if (double_hash) {
		    temp_probe_info = table_probe_dh(test_strings[i], HASH_TABLE_SIZE_M, 0);
        } else {
            temp_probe_info = table_probe_lp(test_strings[i], HASH_TABLE_SIZE_M, 0);
        }
        total_collisions += temp_probe_info.collisions;
	}
    average_collisions = total_collisions / (double)num_of_trials;
    return average_collisions;
}

int main (void) {
    double average_collision_results_lp[HASH_TABLE_SIZE_M];
    double average_collision_results_dh[HASH_TABLE_SIZE_M];
    char random_string[MAX_KEY_LENGTH];
    srand((int) clock());
    FILE* p_graph_data = NULL;

    printf("Testing linear probing collision rate...\n");
    p_graph_data = fopen("lp_results.csv", "w");
    // Initialise hash_table buckets to 0
    memcpy(hash_table, "", HASH_TABLE_SIZE_M * MAX_KEY_LENGTH);
    for (int i = 0; i < HASH_TABLE_SIZE_M; i++) {
        // Add entry to hash_table (increase bucket size for next test)
        rand_string(random_string, MAX_KEY_LENGTH);
        table_probe_lp(random_string, HASH_TABLE_SIZE_M, 1);
        // Clear hash table before each test1
        average_collision_results_lp[i] = collision_test(100, 0);
        fprintf(p_graph_data, "%d,%lf\n", i, average_collision_results_lp[i]);
    }
    fclose(p_graph_data);
    printf("Linear probing results stored in lp_results.csv\n");

    printf("Testing double hashing collision rate...\n");
    p_graph_data = fopen("dh_results.csv", "w");
    // Initialise hash_table buckets to 0
    memcpy(hash_table, "", HASH_TABLE_SIZE_M * MAX_KEY_LENGTH);
    for (int i = 0; i < HASH_TABLE_SIZE_M; i++) {
        // Add entry to hash table (increase bucket size for next test)
        rand_string(random_string, MAX_KEY_LENGTH);
        table_probe_dh(random_string, HASH_TABLE_SIZE_M, 1);
        // Clear hash table before each test1
        average_collision_results_dh[i] = collision_test(100, 1);
        fprintf(p_graph_data, "%d,%lf\n", i, average_collision_results_dh[i]);
    }
    fclose(p_graph_data);
    printf("Double hashing results stored in dh_results.csv\n");

	return 0;
}