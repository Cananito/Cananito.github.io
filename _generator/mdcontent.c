#include <ctype.h>
#include <fts.h>
#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "utils.h"
#include "../md4c/src/md4c-html.h"

// At the moment, the largest file contains 17056 characters.
// Making the max 256 kB to allow for plenty of leeway.
#define MAX_FILE_CONTENT_BUFFER_SIZE 262144

// At the moment, 1647 bytes. Adding extra just in case.
#define TEMPLATE_HTML_FILE_BUFFER_SIZE 2048

struct TemplateParts {
  char const* const before_title;
  char const* const after_title_before_content;
  char const* const after_content_before_footer;
  char const* const footer;
  char const* const after_footer;
};

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
  memcpy(str + index_for_next_chunk_append, chunk, size);
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
                                   char const* const output_dir_path,
                                   struct TemplateParts template_parts) {
  // Open and read file.
  char file_content[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  read_file(file_content, file_path, MAX_FILE_CONTENT_BUFFER_SIZE);
  char const* markdown = file_content;

  // Extract title metadata, if present.
  char title[100] = { 0 };
  char const* const title_metadata_marker = "\% title: ";
  if (string_has_prefix(markdown, title_metadata_marker)) {
    markdown += strlen(title_metadata_marker);
    size_t title_value_len = strcspn(markdown, "\n");
    strncpy(title, markdown, title_value_len);
    markdown += title_value_len + 1; // +1 for the newline.
  }
  // Extract footer metadata, if present.
  bool generate_footer = false;
  char const* const footer_metadata_marker = "\% generate_footer";
  if (string_has_prefix(markdown, footer_metadata_marker)) {
    generate_footer = true;
    markdown += strcspn(markdown, "\n") + 1; // +1 for the newline.
  }
  // Skip empty line between metadata and actual content.
  if (string_has_prefix(markdown, "\n")) {
    // Advance `markdown` to the next line.
    markdown++;
  }

  // Convert Markdown to HTML.
  char html[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  html_from_markdown(html, markdown);

  // Indent the html.
  char indented_html[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };
  strcat(indented_html, "        ");
  size_t indented_html_index = 8;
  size_t html_index = 0;
  bool in_pre_block = false;
  while (true) {
    char html_current = html[html_index];

    // If we reached the end, append the null terminator and finish.
    if (html_current == '\0') {
      indented_html[indented_html_index] = html_current;
      break;
    }

    // Toggle in_pre_block.
    if (string_has_prefix(html + html_index, "<pre><code>")) {
      in_pre_block = true;
    }
    if (in_pre_block == true &&
        html_current == '\n' &&
        string_has_prefix(html + html_index + 1, "</code></pre>")) {
      in_pre_block = false;
    }

    // Append the character.
    indented_html[indented_html_index] = html_current;
    indented_html_index++;
    html_index++;

    // Append indentation.
    if (html_current == '\n' &&
        html[html_index] != '\0' &&
        in_pre_block == false) {
      strcat(indented_html, "        ");
      indented_html_index += 8;
    }
  }

  char output[MAX_FILE_CONTENT_BUFFER_SIZE] = { 0 };

  // Append from the beginning to the open title tag.
  strcat(output, template_parts.before_title);

  if (strlen(title) != 0) {
    // Append the separating dash and title.
    char const* const separating_dash = " - ";
    size_t separating_dash_len = strlen(separating_dash);
    strcat(output, title);
    strncat(output, separating_dash, separating_dash_len);
  }

  // Append the default title.
  char const* const default_title = "Rogelio Gudiño";
  size_t default_title_len = strlen(default_title);
  strncat(output, default_title, default_title_len);

  // Append from the close title tag to the open content tag.
  strcat(output, template_parts.after_title_before_content);

  // Append the converted HTML.
  strcat(output, indented_html);

  // Append from the close content tag to the footer.
  strcat(output, template_parts.after_content_before_footer);

  if (generate_footer) {
    // Append footer.
    strcat(output, template_parts.footer);
  }

  // Append everything else.
  strcat(output, template_parts.after_footer);

  // Construct output file path.
  // TODO: Stop casting and make a copy instead to be safe.
  char* file_name_with_extension = basename((char *)file_path);
  char const* const file_name_without_extension =
      strsep(&file_name_with_extension, ".");
  char output_file_path[MAX_PATH_LENGTH];
  strcpy(output_file_path, output_dir_path);
  strcat(output_file_path, file_name_without_extension);
  strcat(output_file_path, ".html");

  // Write output.
  write_file(output, output_file_path);
}

void generate_from_markdown_content(void) {
  // Get the working dir.
  char cwd_buffer[MAX_PATH_LENGTH];
  char* cwd = getcwd(cwd_buffer, MAX_PATH_LENGTH);
  if (cwd == NULL) {
    printf("Failed to get current directory.\n");
    exit(EXIT_FAILURE);
  }
  strcat(cwd, "/");

  // Open the template HTML file.
  char template_html_file_path[MAX_PATH_LENGTH];
  strcpy(template_html_file_path, cwd);
  strcat(template_html_file_path, "_generator/template.html");
  char template_html_file_content[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  read_file(template_html_file_content,
            template_html_file_path,
            TEMPLATE_HTML_FILE_BUFFER_SIZE);


  // Split the template into parts.
  char before_title[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  char after_title_before_content[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  char after_content_before_footer[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  char footer[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };
  char after_footer[TEMPLATE_HTML_FILE_BUFFER_SIZE] = { 0 };

  char const* const title_tag = "<title>";
  size_t title_tag_len = strlen(title_tag);
  char const* const start_of_open_title_tag = strstr(template_html_file_content,
                                                     title_tag);
  size_t start_to_end_of_open_title_tag_len =
      start_of_open_title_tag + title_tag_len - template_html_file_content;
  strncpy(before_title,
          template_html_file_content,
          start_to_end_of_open_title_tag_len);

  char const* const start_of_close_title_tag =
      start_of_open_title_tag + title_tag_len;
  char const* const content_tag = "<div id=\"content\">\n";
  size_t content_tag_len = strlen(content_tag);
  char const* const start_of_open_content_tag = strstr(start_of_close_title_tag,
                                                       content_tag);
  size_t start_of_close_title_tag_to_end_of_open_content_tag_len =
      start_of_open_content_tag + content_tag_len - start_of_close_title_tag;
  strncpy(after_title_before_content,
          start_of_close_title_tag,
          start_of_close_title_tag_to_end_of_open_content_tag_len);

  char const* const start_of_close_content_tag =
      start_of_open_content_tag + content_tag_len;
  char const* const open_footer_tag = "<footer>";
  char const* const start_of_open_footer_tag =
      strstr(start_of_close_content_tag, open_footer_tag);
  size_t start_of_close_content_tag_to_start_of_open_footer_tag_len =
      start_of_open_footer_tag - start_of_close_content_tag;
  strncpy(after_content_before_footer,
          start_of_close_content_tag,
          start_of_close_content_tag_to_start_of_open_footer_tag_len);

  char const* const close_footer_tag = "</footer>";
  size_t close_footer_tag_len = strlen(close_footer_tag);
  char const* const start_of_close_footer_tag = strstr(start_of_open_footer_tag,
                                                       close_footer_tag);
  size_t start_of_open_footer_tag_to_end_of_close_footer_tag_len =
      start_of_close_footer_tag +
      close_footer_tag_len -
      start_of_open_footer_tag;
  strncpy(footer,
          start_of_open_footer_tag,
          start_of_open_footer_tag_to_end_of_close_footer_tag_len);

  char const* const end_of_close_footer_tag =
      start_of_close_footer_tag + close_footer_tag_len;
  size_t end_of_close_footer_tag_to_end_of_file_len =
      template_html_file_content +
      strlen(template_html_file_content) -
      end_of_close_footer_tag;
  strncpy(after_footer,
          end_of_close_footer_tag,
          end_of_close_footer_tag_to_end_of_file_len);

  struct TemplateParts template_parts = {
    .before_title = before_title,
    .after_title_before_content = after_title_before_content,
    .after_content_before_footer = after_content_before_footer,
    .footer = footer,
    .after_footer = after_footer,
  };


  // Open the content directory.
  char content_dir_path[MAX_PATH_LENGTH];
  strcpy(content_dir_path, cwd);
  strcat(content_dir_path, "_generator/content");
  int fts_options = FTS_PHYSICAL|FTS_NOCHDIR|FTS_NOSTAT|FTS_NOSTAT_TYPE;
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
      // Not a regular file, skip.
      continue;
    }
    char const* const file_path = current_ent->fts_path;
    if (string_has_suffix(file_path, ".md")) {
      generate_for_file_path(file_path, cwd, template_parts);
    }
  }

  // Close content directory.
  fts_close(content_dir_fts);
}
