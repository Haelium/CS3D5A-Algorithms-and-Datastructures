/*
hash_test.c -- Code demonstrating hash tables
Author: David J. Bourke, Student Number: 12304135
Date started:   21st of October 2016
Date submitted: 28th of October 2016
Compile with $ gcc -o hash -std=c99 hashing_function.c
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "hashing_functions.h"

#define NUM_TEST_KEYS 40
char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH];

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
    // seed PRNG
    srand((int) time(NULL));
    probe_info temp_probe_info;
    // Initialise test_keys with random data
    for (int s = 0; s < NUM_TEST_KEYS; s++) {
        rand_string(test_strings[s], MAX_KEY_LENGTH);
    }
    int total_collisions = 0;
    /* Testing the linear probing method */
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

	//
	// calculate table load here
	//

	return 0;
}