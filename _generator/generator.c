#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct option long_options[] = {
  { .name = "version", .has_arg = no_argument, .flag = 0, .val = 'v' },
  { .name = "relpaths", .has_arg = required_argument, .flag = 0, .val = 0},
  { .name = 0, .has_arg = 0, .flag = 0, .val = 0 },
};

int main(int argc, char** argv) {
  while (1) {
    int option_index = 0;
    int c = getopt_long(argc, argv, "v", long_options, &option_index);

    if (c == -1) {
      break;
    }

    // TODO: Support -h and --help.
    switch (c) {
      case 0: { // long options
        switch (option_index) {
          case 0: { // version
            // TODO: This should never be handled here, exit?
            break;
          }
          case 1: { // relpaths
            optind--;
            while (optind < argc) {
              char* path = argv[optind];
              // TODO: Gather into an array!
              printf("relpath value: %s\n", path);

              int next_optind = optind + 1;
              if (next_optind < argc &&
                  strncmp("-", argv[next_optind], 1) == 0) {
                break;
              }

              optind++;
            }
            break;
          }
        }
        break;
      }
      case 'v': {
        printf("Version 1.0\n");
        break;
      }
      case '?': {
        exit(EXIT_FAILURE);
        break;
      }
    }
  }

  // TODO: Read relpaths array and implement!

  return 0;
}
