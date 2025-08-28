#include "mdcontent.h"
#include "scorecards.h"

// TODO: rename scorecards.c to golf_stats.c

// TODO: rename generate_from_markdown_content to
// generate_markdown_content_pages

// TODO: rename generate_scorecard_pages to generate_golf_stats_pages

// TODO: use csv instead of txt?

// TODO: rename golf_scorecards to golf_round_stats

// TODO: output summary scorecards to /golf_scorecards.html; add summed global
// stats (% of each club e.g.) to this page as well?

// TODO: output detailed entries to /golf_stats/<yyy_mm_dd>.html; linked by each
// entry in /golf_scorecards.html

// TODO: design the global data struct for ALL parsed entries

// TODO: move all md content into an mdcontent dir

int main(void) {
  generate_from_markdown_content();
  generate_scorecard_pages();
  return 0;
}
