#include <fts.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

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

  // TODO: Open up the template HTML file.

  // Open the content directory.
  char content_dir_path[MAXPATHLEN];
  strcpy(content_dir_path, cwd);
  strcat(content_dir_path, "/_generator/content");
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
    char* file_path = current_ent->fts_path;
    if (string_has_suffix(file_path, ".md")) {
      // TODO: Process file.
      printf(">>> %s\n", file_path);
    }
  }

  // Close content directory.
  fts_close(content_dir_fts);
}

int main(void) {
  generate();
  return 0;
}
