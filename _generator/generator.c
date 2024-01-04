#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

static void generate(void) {
  static const size_t cwd_size = MAXPATHLEN;
  char cwd_buffer[cwd_size];
  char* cwd = getcwd(cwd_buffer, cwd_size);
  if (cwd == NULL) {
    printf("Failed to get current directory.\n");
    exit(EXIT_FAILURE);
  }
  printf(">>> cwd: %s\n", cwd);
}

int main(void) {
  generate();
  return 0;
}
