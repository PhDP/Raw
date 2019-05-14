/**
 * @file str.h
 * @brief Miscellaneous functions for strings and I/O.
 */
#ifndef RANDAMU_STR_H_
#define RANDAMU_STR_H_

#include "randamu/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Concat strings, growing the memory allocated to the destination if necessary.
 * @param dest            Address of the string pointer.
 * @param dest_length     Pointer to the length of the destination (to avoid calling strlen).
 * @param dest_capacity   Pointer to the memory currently allocated to the destination.
 * @param source          String to add to our destination.
 * @return New length of the string.
 */
size_t rd_strcat(char** dest, size_t* dest_length, size_t* dest_capacity, const char* source);

/**
 * @brief Reads an entire file and return its content.
 * @param filename  Name of the file to read.
 * @return A string with the entire content of the file, or NULL in case of failure.
 */
char* rd_read_file(const char* filename);

/**
 * @brief Checks whether a string begins and ends with specific characters.
 * @param txt     Text to test.
 * @param left    First character expected.
 * @param right   Last character expected.
 * @return Whether the test is true
 */
int rd_surrounded(const char* txt, const char left, const char right);

#ifdef __cplusplus
}
#endif

#endif
