#include <fts.h>
#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

static void generate_for_file_path(char* file_path, char* output_dir_path) {
  // TODO: Open and read file.

  // TODO: Convert to HTML.

  // TODO: Stitch template and content.

  // Construct output file path.
  char* file_name_with_extension = basename(file_path);
  char* file_name_without_extension = strsep(&file_name_with_extension, ".");
  char output_file_path[MAXPATHLEN];
  strcpy(output_file_path, output_dir_path);
  strcat(output_file_path, file_name_without_extension);
  strcat(output_file_path, ".html");
  printf(">>> file_path:        %s\n", file_path);
  printf(">>> output_file_path: %s\n", output_file_path);

  // TODO: Write to output_path.
}

static bool string_has_suffix(char* str, char* suffix) {
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
  char cwd_buffer[MAXPATHLEN];
  char* cwd = getcwd(cwd_buffer, MAXPATHLEN);
  if (cwd == NULL) {
    printf("Failed to get current directory.\n");
    exit(EXIT_FAILURE);
  }
  strcat(cwd, "/");

  // TODO: Open up the template HTML file.

  // Open the content directory.
  char content_dir_path[MAXPATHLEN];
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
