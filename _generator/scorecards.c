#include <fts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

static int newest_file_first(FTSENT const** a, FTSENT const** b) {
  return strcmp((*b)->fts_name, (*a)->fts_name);
}

void generate_scorecard_pages(void) {
  // Get the working dir.
  char cwd_buffer[MAX_PATH_LENGTH];
  char* cwd = getcwd(cwd_buffer, MAX_PATH_LENGTH);
  if (cwd == NULL) {
    printf("Failed to get current directory.\n");
    exit(EXIT_FAILURE);
  }
  strcat(cwd, "/");

  // Open the golf scorecards directory.
  char content_dir_path[MAX_PATH_LENGTH];
  strcpy(content_dir_path, cwd);
  strcat(content_dir_path, "_generator/content/golf_scorecards");
  int fts_options = FTS_PHYSICAL|FTS_NOCHDIR|FTS_NOSTAT|FTS_NOSTAT_TYPE;
  char* dirs[] = { content_dir_path, NULL };
  FTS* content_dir_fts = fts_open(dirs, fts_options, newest_file_first);
  if (content_dir_fts == NULL) {
    printf("Failed to open the golf scorecards directory.\n");
    exit(EXIT_FAILURE);
  }

  // Iterate over files in the golf scorecards directory.
  while (1) {
    FTSENT* current_ent = fts_read(content_dir_fts);
    if (current_ent == NULL) {
      break;
    }
    if (current_ent->fts_info != FTS_F) {
      // Not a regular file, skip.
      continue;
    }
    char const* const file_path = current_ent->fts_path;
    if (string_has_prefix(file_path, ".")) {
      // TODO: Implement!
      printf("%s\n", file_path);
    }
  }

  // Close content directory.
  fts_close(content_dir_fts);
}
