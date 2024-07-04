# Cananito.github.io

My site: [cananito.com](https://cananito.com), [rogeliogudino.com](http://rogeliogudino.com), or [cananito.github.io](https://cananito.github.io).

## Generator

In the `_generator/` directory there's a `generator.c` program that goes over all the Markdown pages in `_generator/content/`, converts them to HTML, stiches them into the HTML template `_generator/template.html`, and outputs them as HTML at the root of the repository.

### Requirements

* Linux or macOS.
* [Clang](https://clang.llvm.org/)
* [Make](https://www.gnu.org/software/make/)

### Setup Instructions

1. Clone this repository with the `--recurse-submodules` flag.

Alternatively:

1. Clone this repository.
1. `cd` into the `md4c` dir.
1. Run `git submodule init && git submodule update`.

### Generation Instructions

1. Edit or add `.md` files in `_generator/content/`.
    * Begin the file with a `% title: Something` token to have it's title be "Something", otherwise defaults to "Rogelio Gudiño".
    * Add the `% generate_footer` token to add a footer to the page with a link to the home page. Has to come after the title token.
1. Run `make`.
1. Commit and push both `.md` and the generated `.html` files.

### Build only

1. Run `make build`.

### Clean build artifacts

1. Run `make clean`.
