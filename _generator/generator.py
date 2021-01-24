#!/usr/bin/python
# coding=utf-8

import argparse
import os
import sys

from enum import Enum
from html.parser import HTMLParser


class Stage(Enum):
    BEFORE_CONTENT = 0
    AFTER_CONTENT = 1


class Stitcher(HTMLParser):
    def __init__(self, template_html):
        HTMLParser.__init__(self)
        self.stage = Stage.BEFORE_CONTENT
        self.before_content_html = ""
        self.after_content_html = ""
        self.feed(template_html)

    def stitched(self, content_html):
        content_html_lines = content_html.split("\n")
        indented_content_html_lines = ["        " + s for s in content_html_lines]
        indented_content_html = "\n".join(indented_content_html_lines)
        return self.before_content_html + "\n" + indented_content_html + self.after_content_html

    def handle_starttag(self, tag, attrs):
        needs_to_change_stage = False
        self.append_to_current_segment("<")
        self.append_to_current_segment(tag)
        for pair in attrs:
            self.append_to_current_segment(" ")
            self.append_to_current_segment(pair[0])
            self.append_to_current_segment("=")
            self.append_to_current_segment("\"")
            self.append_to_current_segment(pair[1])
            self.append_to_current_segment("\"")
            if tag == "div" and pair[0] == "id" and pair[1] == "content":
                needs_to_change_stage = True
        self.append_to_current_segment(">")
        if needs_to_change_stage:
            self.stage = Stage.AFTER_CONTENT

    def handle_endtag(self, tag):
        self.append_to_current_segment("</")
        self.append_to_current_segment(tag)
        self.append_to_current_segment(">")

    def handle_startendtag(self, tag, attrs):
        self.append_to_current_segment("<")
        self.append_to_current_segment(tag)
        self.append_to_current_segment(" />")

    def handle_data(self, data):
        self.append_to_current_segment(data)

    def handle_entityref(self, name):
        self.append_to_current_segment("&")
        self.append_to_current_segment(name)
        self.append_to_current_segment(";")

    def handle_charref(self, name):
        self.append_to_current_segment("&#")
        self.append_to_current_segment(name)
        self.append_to_current_segment(";")

    def handle_decl(self, decl):
        self.append_to_current_segment("<!")
        self.append_to_current_segment(decl)
        self.append_to_current_segment(">")

    def append_to_current_segment(self, s):
        if self.stage == Stage.BEFORE_CONTENT:
            self.before_content_html += s
        elif self.stage == Stage.AFTER_CONTENT:
            self.after_content_html += s


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generates full HTML pages by inserting content HTML snippets into a template HTML file.")
    parser.add_argument("--version", "-v", action="version", version="1.0")
    parser.add_argument("relpaths", action="store", nargs="*", help="All the file and directory paths that get processed.")
    args = parser.parse_args()

    script_relpath = os.path.dirname(os.path.relpath(__file__))

    relpaths = args.relpaths
    if not relpaths:
        content_dir_relpath = script_relpath + "/content"
        relpaths = [content_dir_relpath]

    template_html_relpath = script_relpath + "/template.html"
    template_html = open(template_html_relpath).read()
    stitcher = Stitcher(template_html)

    # TODO: In a recursive loop, stitch all files.

    # Verifying going up relative paths:
    # root_relpath = script_relpath + "/.."
    # index_html_relpath = root_relpath + "/index.html"
    # index_html = open(index_html_relpath).read()
    # sys.stdout.write(">>> index.html:\n")
    # sys.stdout.write(index_html + "\n")

    # Verifying stitcher:
    # s = stitcher.stitched("HELLO WORLDDDDDDDDDDDDDDDDDDDDd")
    # sys.stdout.write(s + "\n")
