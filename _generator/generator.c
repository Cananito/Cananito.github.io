#include <fts.h>
#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

// On my current set-up, 101 characters is the longest path.
#define MAX_PATH_LENGTH 256

// At the moment, the largest file contains 17056 characters.
// Making the max 256 kB to allow for plenty of leeway.
#define MAX_FILE_CONTENT_BUFFER_SIZE 262144

static void html_from_markdown(char* html_destination,
                               char const* const markdown_source) {
  // TODO: Implement!
  printf(">>> %c\n", markdown_source[0]);
  html_destination[0] = 'a';
  html_destination[1] = '\0';
  printf(">>> %s\n", html_destination);
}

static void generate_for_file_path(char const* const file_path,
                                   char const* const output_dir_path) {
  printf(">>> Generating for file_path:        %s\n", file_path);

  // Open and read file.
  char file_content[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  FILE* file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Failed to open file_path: %s.\n", file_path);
    exit(EXIT_FAILURE);
  }
  fread(&file_content, sizeof(char), MAX_FILE_CONTENT_BUFFER_SIZE, file);
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

  // Convert to HTML.
  char html[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  html_from_markdown(html, file_content);

  // TODO: Stitch template and content.

  // Construct output file path.
  // TODO: Stop casting and make a copy instead to be safe.
  char* file_name_with_extension = basename((char *)file_path);
  char* file_name_without_extension = strsep(&file_name_with_extension, ".");
  char output_file_path[MAX_PATH_LENGTH];
  strcpy(output_file_path, output_dir_path);
  strcat(output_file_path, file_name_without_extension);
  strcat(output_file_path, ".html");
  printf(">>> output_file_path: %s\n", output_file_path);

  // TODO: Write to output_path.
}

static bool string_has_suffix(char const* const str, char const* const suffix) {
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

static void generate(void) {
  // Get the working dir.
  char cwd_buffer[MAX_PATH_LENGTH];
  char* cwd = getcwd(cwd_buffer, MAX_PATH_LENGTH);
  if (cwd == NULL) {
    printf("Failed to get current directory.\n");
    exit(EXIT_FAILURE);
  }
  strcat(cwd, "/");

  // TODO: Open up the template HTML file.

  // Open the content directory.
  char content_dir_path[MAX_PATH_LENGTH];
  strcpy(content_dir_path, cwd);
  strcat(content_dir_path, "_generator/content");
  int fts_options = FTS_PHYSICAL|FTS_NOCHDIR;
  char* dirs[] = { content_dir_path, NULL };
  FTS* content_dir_fts = fts_open(dirs, fts_options, NULL);
  if (content_dir_fts == NULL) {
    printf("Failed to open the content directory.\n");
    exit(EXIT_FAILURE);
  }

  // Iterate over files in the content directory.
  while (1) {
    FTSENT* current_ent = fts_read(content_dir_fts);
    if (current_ent == NULL) {
      break;
    }
    if (current_ent->fts_info != FTS_F) {
      // Not a regular file, likely a directory, skip.
      continue;
    }
    char* file_path = current_ent->fts_path;
    if (string_has_suffix(file_path, ".md")) {
      generate_for_file_path(file_path, cwd);
    }
  }

  // Close content directory.
  fts_close(content_dir_fts);
}

int main(void) {
  generate();
  return 0;
}
