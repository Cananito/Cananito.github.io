#include "mdcontent.h"
#include "scorecards.h"

int main(void) {
  generate_from_markdown_content();
  generate_scorecard_pages();
  return 0;
}
