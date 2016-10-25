/*
hashing_functions.c -- Code demonstrating hash tables
Author: David J. Bourke
Date started:   21st of October 2016
Date submitted: 28th of October 2016
*/

#include <stdio.h>
#include <string.h>

#define NUM_TEST_KEYS 25
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 28

char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];
char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
    "Harkonnen", "Atreides", "Ordos", "Sandworm", "Corrino",
    "Ecaz", "Hagal", "Fenring", "Moritani", "Mutelli",
    "Novebruns", "Richese", "Taligari", "Vernius", "Spice",
    "Frank Herbert", "Westwood", "Studios", "Copyright", "Infringement",
    "Nikola Tesla", "Brotherhood", "Of NOD", "beats", "GDI"
};

typedef struct probe_info {
    int index;
    int collisions;
} probe_info;

// Returns a pseudorandom index position based on an input string
int hash_index (const char *key) {
    int index = 0;
	for (int i = 0; i < strlen(key); i++) {
		index += key[i] * (i*i);
	}
    return index;
}

// Returns a pseudorandom offset based on an input string
int hash_offset (const char *key) {
    int offset = 0;
    for (int i = 0; i < strlen(key); i++) {
        offset += key[i] ^ key[-i]; 
    }
    return offset * 2 + 1; // Always an odd number
}

// probes a hash table for a key, if the key exists, the index is returned,
// if the key does not exist, it is added to the hash table
// Colisions with existing keys are dealt with using linear probing
probe_info table_probe_lp (const char *key, int table_size) {
    probe_info dh_probe_info;
    int index = hash_index(key) % table_size;
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; i < table_size; i++) {
        index_mod_ts = (index + i) % table_size;
        // if an empty bucket is found, insert the key and return the index
        if (!hash_table[index_mod_ts][0]) {
            strcpy(hash_table[index_mod_ts], key);
            printf("%d probes to insert: %16s,\tindex: %d\n", i, key, index_mod_ts);
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
        // if the key exists in the table already, return the index
        if (!strcmp(key, hash_table[index_mod_ts])) {
            printf("%d probes to locate: %16s,\tindex: %d\n", i, key, index_mod_ts);
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
    probe_info dh_probe_info;
    int index = hash_index(key) % table_size;
    int hash_off = hash_offset(key) % table_size;
    int index_mod_ts; // allows for "wrapping" where (index > table_size)
    int i;  // We need i after loop for case where no empty bucket is found
    for (i = 0; table_size; i++) {
        // h(k,i) = (f(k) + i * g(k))
        index_mod_ts = (index + i * hash_off) % table_size;
        // if an empty bucket is found, insert the key and return the index
        if (!hash_table[index_mod_ts][0]) {
            strcpy(hash_table[index_mod_ts], key);
            printf("%d probes to insert: %16s,\tindex: %d\n", i, key, index_mod_ts);
            dh_probe_info.index = index_mod_ts;
            dh_probe_info.collisions = i;
            return dh_probe_info;
        }
        // if the key exists in the table already, return the index
        if (!strcmp(key, hash_table[index_mod_ts])) {
            printf("%d probes to locate: %16s,\tindex: %d\n", i, key, index_mod_ts);
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

int main (void) {
    probe_info temp_probe_info;
    int total_collisions = 0;
    // Initialise all elements of hash_table to 0
    memcpy(hash_table, "", HASH_TABLE_SIZE_M * MAX_KEY_LENGTH);
    printf("Probing hash table for every test string using linear probing...\n");
    // Probe the hash table for every test_string using linear probing function
	for ( int i = 0; i < NUM_TEST_KEYS; i++ ) {
		probe_info temp_probe_info = table_probe_lp(test_strings[i], HASH_TABLE_SIZE_M);
        total_collisions += temp_probe_info.collisions;
	}
    printf("Total number of collisions:\t %d\n", total_collisions);
    printf("Average number of collisions:\t %lf\n", total_collisions / (double)NUM_TEST_KEYS);

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

	//
	// calculate table load here
	//

	return 0;
}