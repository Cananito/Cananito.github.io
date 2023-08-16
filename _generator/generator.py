#!/usr/local/bin/python3
# coding=utf-8

# TODO: Add table of contents support.
# TODO: Replace HTML parsing and stitching with token replacement?

import argparse
import markdown
import os
import sys

from enum import Enum
from html.parser import HTMLParser
from typing import NamedTuple


class ParsedTemplate(NamedTuple):
    before_title_html: str
    title_html: str
    after_title_before_content_html: str
    after_content_before_footer_html: str
    footer_html: str
    after_footer_html: str


class Stage(Enum):
    BEFORE_TITLE = 0
    TITLE = 1
    AFTER_TITLE_BEFORE_CONTENT = 2
    AFTER_CONTENT_BEFORE_FOOTER = 3
    FOOTER = 4
    AFTER_FOOTER = 5


class TemplateParser(HTMLParser):
    def __init__(self) -> None:
        HTMLParser.__init__(self)
        self.__stage: Stage = Stage.BEFORE_TITLE
        self.__before_title_html: str = ""
        self.__title_html: str = ""
        self.__after_title_before_content_html: str = ""
        self.__after_content_before_footer_html: str = ""
        self.__footer_html: str = ""
        self.__after_footer_html: str = ""

    def parsed_template(self) -> ParsedTemplate:
        return ParsedTemplate(self.__before_title_html,
                              self.__title_html,
                              self.__after_title_before_content_html,
                              self.__after_content_before_footer_html,
                              self.__footer_html,
                              self.__after_footer_html)

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str]]) -> None:
        # Handle the title tag.
        if tag == "title":
            if self.__title_html:
                sys.stdout.write("There's more than one title tags in the "
                                 "template! Exiting.\n")
                sys.exit(1)
            self.__stage = Stage.TITLE
        # Handle the footer tag.
        if tag == "footer":
            if self.__footer_html:
                sys.stdout.write("There's more than one foter tags in the "
                                 "template! Exiting.\n")
                sys.exit(1)
            self.__stage = Stage.FOOTER

        change_to_after_content_stage: bool = False
        self.__append_to_current_segment("<")
        self.__append_to_current_segment(tag)
        pair: tuple[str, str]
        for pair in attrs:
            self.__append_to_current_segment(" ")
            self.__append_to_current_segment(pair[0])
            value: str = pair[1]
            if value:
                self.__append_to_current_segment("=")
                self.__append_to_current_segment("\"")
                self.__append_to_current_segment(value)
                self.__append_to_current_segment("\"")
            # Handle the div#content tag.
            if tag == "div" and pair[0] == "id" and pair[1] == "content":
                change_to_after_content_stage = True
        self.__append_to_current_segment(">")
        if change_to_after_content_stage:
            self.__stage = Stage.AFTER_CONTENT_BEFORE_FOOTER

    def handle_endtag(self, tag: str) -> None:
        self.__append_to_current_segment("</")
        self.__append_to_current_segment(tag)
        self.__append_to_current_segment(">")
        # Handle the title tag.
        if tag == "title":
            self.__stage = Stage.AFTER_TITLE_BEFORE_CONTENT
        # Handle the footer tag.
        if tag == "footer":
            self.__stage = Stage.AFTER_FOOTER

    def handle_startendtag(self,
                           tag: str,
                           attrs: list[tuple[str, str]]) -> None:
        self.__append_to_current_segment("<")
        self.__append_to_current_segment(tag)
        pair: tuple[str, str]
        for pair in attrs:
            self.__append_to_current_segment(" ")
            self.__append_to_current_segment(pair[0])
            self.__append_to_current_segment("=")
            self.__append_to_current_segment("\"")
            self.__append_to_current_segment(pair[1])
            self.__append_to_current_segment("\"")
        self.__append_to_current_segment(" />")

    def handle_data(self, data: str) -> None:
        self.__append_to_current_segment(data)

    def handle_entityref(self, name: str) -> None:
        self.__append_to_current_segment("&")
        self.__append_to_current_segment(name)
        self.__append_to_current_segment(";")

    def handle_charref(self, name: str) -> None:
        self.__append_to_current_segment("&#")
        self.__append_to_current_segment(name)
        self.__append_to_current_segment(";")

    def handle_decl(self, decl: str) -> None:
        self.__append_to_current_segment("<!")
        self.__append_to_current_segment(decl)
        self.__append_to_current_segment(">")

    def __append_to_current_segment(self, s: str) -> None:
        if self.__stage == Stage.BEFORE_TITLE:
            self.__before_title_html += s
        elif self.__stage == Stage.TITLE:
            self.__title_html += s
        elif self.__stage == Stage.AFTER_TITLE_BEFORE_CONTENT:
            self.__after_title_before_content_html += s
        elif self.__stage == Stage.AFTER_CONTENT_BEFORE_FOOTER:
            self.__after_content_before_footer_html += s
        elif self.__stage == Stage.FOOTER:
            self.__footer_html += s
        elif self.__stage == Stage.AFTER_FOOTER:
            self.__after_footer_html += s
        else:
            sys.stdout.write("Got into a bad state. Exiting!\n")
            sys.exit(1)


def indented_html_lines(html_lines: list[str]) -> list[str]:
    """Indented HTML lines.

    Returns the passed-in |html_lines| indented by 8 spaces, except for
    lines within a <pre> block.
    """
    indented_html_lines: list[str] = []
    in_pre_block: bool = False
    line: str
    for line in html_lines:
        # First check if we're done with the pre block.
        if in_pre_block and line.endswith("</pre>"):
            in_pre_block = False

        # Then append the line.
        if not in_pre_block:
            indented_html_lines.append("        " + line)
        else:
            indented_html_lines.append(line)

        # Finally check if we're starting a pre block.
        if not in_pre_block and line.startswith("<pre>"):
            in_pre_block = True

    return indented_html_lines


def stitched_content_html(content_html: str,
                          title: str,
                          generate_footer: bool,
                          parsed_template: ParsedTemplate) -> str:
    # Title.
    title_html: str = parsed_template.title_html
    if title:
        title_html = "<title>" + title + " - Rogelio Gudiño</title>"

    # Content.
    content_html_lines: list[str] = content_html.splitlines()
    indented_content_html_lines: list[str] = indented_html_lines(
        content_html_lines)
    indented_content_html: str = "\n".join(indented_content_html_lines)

    # Footer.
    footer_html: str = ""
    if generate_footer:
        footer_html = parsed_template.footer_html

    # Actual stitch.
    return (parsed_template.before_title_html +
            title_html +
            parsed_template.after_title_before_content_html +
            "\n" +
            indented_content_html +
            parsed_template.after_content_before_footer_html +
            footer_html +
            parsed_template.after_footer_html)


# TODO: Remove this class in favor of standalone functions.
# TODO: Finish adding type annotations to all these methods.
class Generator(object):
    def __init__(self, relpaths: list[str]) -> None:
        self.script_dir_path = os.path.dirname(os.path.abspath(__file__))
        self.content_dir_path = os.path.join(self.script_dir_path, "content")
        self.root_output_dir_path = os.path.split(self.script_dir_path)[0]

        self.paths = [os.path.abspath(relpath) for relpath in relpaths]
        if not self.paths:
            self.paths = [self.content_dir_path]

        template_html_path = os.path.join(self.script_dir_path,
                                             "template.html")
        template_html = self.__contents_of_file_path(template_html_path)
        if not template_html:
            sys.stdout.write("Couldn't load template.html!")
            sys.exit(1)

        template_parser: TemplateParser = TemplateParser()
        template_parser.feed(template_html)
        self.__parsed_template: ParsedTemplate = template_parser.parsed_template()

    def generate(self) -> None:
        for path in self.paths:
            if os.path.isdir(path):
                for root, subdirs, files in os.walk(path):
                    for f in files:
                        file_path = os.path.join(root, f)
                        self.__generate_for_file(file_path)
            elif os.path.isfile(path):
                self.__generate_for_file(path)
            else:
                sys.stdout.write("Found a path that's neither a directory nor "
                                 "a file!")
                sys.exit(1)

    def __lines_of_file_path(self, file_path):
        lines = None
        with open(file_path) as fileobject:
          lines = fileobject.readlines()
        return lines

    def __contents_of_file_path(self, file_path):
        contents = None
        with open(file_path) as fileobject:
            contents = fileobject.read()
            fileobject.close()
        return contents

    def ___write_contents_to_file_path(self, contents, file_path):
        with open(file_path, "w") as fileobject:
            fileobject.write(contents)
            fileobject.close()

    def __generate_for_file(self, file_path):
        if not file_path.startswith(self.content_dir_path):
            sys.stdout.write("The following file isn't in the "
                             "/_generator/content/ subtree, so skipping it: " +
                             file_path + "\n")
            return

        if (not os.path.basename(file_path).endswith(".md") and not
            os.path.basename(file_path).endswith(".html")):
            sys.stdout.write("Skipping encountered a non-Markdown or non-HTML "
                             "file: " + file_path + "\n")
            return

        # Build output path.
        file_relpath_to_content_dir_path = os.path.relpath(
            file_path, self.content_dir_path)
        file_relpath_to_content_dir_path_splitext = os.path.splitext(
            file_relpath_to_content_dir_path)
        if file_relpath_to_content_dir_path_splitext[1] == ".md":
            file_relpath_to_content_dir_path = (
                file_relpath_to_content_dir_path_splitext[0] + ".html")
        output_path = os.path.join(self.root_output_dir_path,
                                   file_relpath_to_content_dir_path)

        # Read contents of input path.
        file_lines = self.__lines_of_file_path(file_path)
        if not file_lines:
            sys.stdout.write("Couldn't load " + file_path + "! Skipping.\n")
            return

        # Extract metadata.
        title = None
        if file_lines[0].startswith("% title: "):
            title = file_lines[0][len("% title: "):].strip()
            file_lines.pop(0)
        generate_footer = False
        if file_lines[0].startswith("% generate_footer"):
            generate_footer = True
            file_lines.pop(0)

        # Convert from Markdown to HTML.
        file_markdown = "".join(file_lines)
        file_html = markdown.markdown(file_markdown)

        sys.stdout.write("Generating full HTML for " +
                         file_path +
                         " in " +
                         output_path +
                         "\n")
        # Stitch.
        stitched_html = stitched_content_html(file_html,
                                              title,
                                              generate_footer,
                                              self.__parsed_template)
        # Write contents to output path.
        self.___write_contents_to_file_path(stitched_html, output_path)


def main() -> None:
    parser: argparse.ArgumentParser = argparse.ArgumentParser(
        description="Generates full HTML pages by inserting content HTML "
                    "snippets into a template HTML file. The script can be ran "
                    "from anywhere in the file system, but all input HTML must "
                    "be in `.../_generator/content/` (where ... is the output "
                    "directory).")
    parser.add_argument("--version", "-v", action="version", version="1.0")
    parser.add_argument("relpaths", action="store", nargs="*",
                        help="All the file and directory paths to process. "
                             "Default is `.../_generator/content/`")
    args = parser.parse_args()
    Generator(args.relpaths).generate()

if __name__ == "__main__":
    main()
