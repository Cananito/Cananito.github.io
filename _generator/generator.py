#!/usr/bin/python
# coding=utf-8

import argparse
import sys

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generates full HTML pages by inserting content HTML snippets into a template HTML file.")

    parser.add_argument("--version", "-v", action="version", version="1.0")
    # TODO: Add optional argument that takes directory or HTML file so that it only processes that.

    args = parser.parse_args()

    # TODO: Implement!
    sys.stdout.write("Hello!!\n")
