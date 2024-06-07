#include <ctype.h>
#include <fts.h>
#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "../md4c/src/md4c-html.h"

// On my current set-up, 101 characters is the longest path.
#define MAX_PATH_LENGTH 256

// At the moment, the largest file contains 17056 characters.
// Making the max 256 kB to allow for plenty of leeway.
#define MAX_FILE_CONTENT_BUFFER_SIZE 262144

// At the moment, 1647 bytes. Adding extra just in case.
#define TEMPLATE_HTML_FILE_BUFFER_SIZE 2048

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

static bool string_has_prefix(char const* const str, char const* const prefix) {
  if (str == NULL || prefix == NULL) {
    return false;
  }
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

static void read_file(char* file_content,
                      char const* const file_path,
                      size_t buffer_size) {
  FILE* file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Failed to open file_path: %s.\n", file_path);
    exit(EXIT_FAILURE);
  }
  fread(&file_content, sizeof(char), buffer_size, file);
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

struct StringBuilder {
  char* const str;
  size_t index_for_next_chunk_append;
};

static void handle_html_chunk(MD_CHAR const* chunk,
                              MD_SIZE size,
                              void* userdata) {
  struct StringBuilder* string_builder = (struct StringBuilder*)userdata;

  size_t index_for_next_chunk_append =
      string_builder->index_for_next_chunk_append;
  char* const str = string_builder->str;

  for (size_t i = 0; i < size; i++) {
    size_t index = index_for_next_chunk_append + i;
    str[index] = chunk[i];
  }

  string_builder->index_for_next_chunk_append += size;
}

static void html_from_markdown(char* const destination_html,
                               char const* const source_markdown) {
  struct StringBuilder string_builder = {
    .str = destination_html,
    .index_for_next_chunk_append = 0,
  };
  int result = md_html(source_markdown,
                       strlen(source_markdown),
                       &handle_html_chunk,
                       &string_builder,
                       MD_DIALECT_COMMONMARK,
                       MD_HTML_FLAG_XHTML);

  if (result == -1) {
    printf("Failed to parse markdown.\n");
    exit(EXIT_FAILURE);
  }

  // Add null terminator.
  destination_html[string_builder.index_for_next_chunk_append] = '\0';
}

static void generate_for_file_path(char const* const file_path,
                                   char const* const output_dir_path) {
  printf(">>> Generating for file_path:        %s\n", file_path);

  // Open and read file.
  char file_content[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  read_file(file_content, file_path, MAX_FILE_CONTENT_BUFFER_SIZE);

  char* markdown = file_content;

  // Extract metadata (top lines beginning with %).
  if (string_has_prefix(markdown, "\% title: ")) {
    // TODO: Extract value and store into a `char* title`.

    // Advance `markdown` to the next line.
    while (markdown[0] != '\n') {
      markdown++;
    }
    markdown++;
  }
  if (string_has_prefix(markdown, "\% generate_footer")) {
    // TODO: Store true into a `bool generate_footer`.

    // Advance `markdown` to the next line.
    while (markdown[0] != '\n') {
      markdown++;
    }
    markdown++;
  }
  if (string_has_prefix(markdown, "\n")) {
    // Advance `markdown` to the next line.
    markdown++;
  }

  // Convert to HTML.
  char html[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  html_from_markdown(html, markdown);
  printf(">>> html:\n%s\n", html);

  // TODO: Stitch template and content.

  // Construct output file path.
  // TODO: Stop casting and make a copy instead to be safe.
  char* file_name_with_extension = basename((char *)file_path);
  char* file_name_without_extension = strsep(&file_name_with_extension, ".");
  char output_file_path[MAX_PATH_LENGTH];
  strcpy(output_file_path, output_dir_path);
  strcat(output_file_path, file_name_without_extension);
  strcat(output_file_path, ".html");
  printf(">>> output_file_path:                %s\n", output_file_path);

  // TODO: Write to output_path.
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

  // TODO: Make open file func and reuse in generate_for_file_path.

  // Open the template HTML file.
  char template_html_file_path[MAX_PATH_LENGTH];
  strcpy(template_html_file_path, cwd);
  strcat(template_html_file_path, "_generator/template.html");
  char template_html_file_content[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  read_file(template_html_file_content,
            template_html_file_path,
            TEMPLATE_HTML_FILE_BUFFER_SIZE);
  printf(">>> template.html contents: %s\n", template_html_file_content);

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
    //if (string_has_suffix(file_path, ".md")) {
    if (string_has_suffix(file_path, "wine.md")) {
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
