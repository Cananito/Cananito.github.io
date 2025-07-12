#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool string_has_suffix(char const* const str, char const* const suffix) {
  if (str == NULL || suffix == NULL) {
    return false;
  }
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);
  if (suffix_len > str_len) {
    return false;
  }
  return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

bool string_has_prefix(char const* const str, char const* const prefix) {
  if (str == NULL || prefix == NULL) {
    return false;
  }
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

void read_file(char* const file_content,
                      char const* const file_path,
                      size_t buffer_size) {
  FILE* file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Failed to open file_path: %s.\n", file_path);
    exit(EXIT_FAILURE);
  }
  fread(file_content, sizeof(char), buffer_size, file);
  if (feof(file) == 0) {
    printf("Couldn't read to end of file for file_path: %s.\n", file_path);
    fclose(file);
    exit(EXIT_FAILURE);
  }
  if (ferror(file) != 0) {
    printf("Read error for file_path: %s.\n", file_path);
    fclose(file);
    exit(EXIT_FAILURE);
  }
  fclose(file);
}

void write_file(char* const file_content, char const* const file_path) {
  FILE* file = fopen(file_path, "w");
  if (file == NULL) {
    printf("Failed to write to file_path: %s.\n", file_path);
    exit(EXIT_FAILURE);
  }
  fputs(file_content, file);
  fclose(file);
}
