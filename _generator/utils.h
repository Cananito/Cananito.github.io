#include <stdbool.h>

// On my current set-up, 101 characters is the longest path.
#define MAX_PATH_LENGTH 256

bool string_has_suffix(char const* const str, char const* const suffix);

bool string_has_prefix(char const* const str, char const* const prefix);

void read_file(char* const file_content,
               char const* const file_path,
               size_t buffer_size);

void write_file(char* const file_content, char const* const file_path);
