# Cananito.github.io

My site: [cananito.com](https://cananito.com), [rogeliogudino.com](http://rogeliogudino.com), or [cananito.github.io](https://cananito.github.io).

## Generator

In the `_generator/` directory there's a `generator.py` script that goes over all the Markdown pages in `_generator/content/`, converts them to HTML, stiches them into the HTML template `_generator/template.html`, and outputs them as HTML at the root of the repository.

### Requirements

* Python 3.
* [Python-Markdown](https://github.com/Python-Markdown/markdown).
* [mypy](https://github.com/python/mypy) for type checking.
    * Run using `mypy _generator/generator.py`.
* [pyink](https://github.com/google/pyink) for formatting.
    * Format using `pyink _generator/generator.py -l 80`.

### Instructions

1. Edit or add `.md` files in `_generator/content/`.
    * Begin the file with a `% title: Something` token to have it's title be "Something", otherwise defaults to "Rogelio Gudiño".
    * Add the `% generate_footer` token to add a footer to the page with a link to the home page. Has to come after the title token.
1. Execute `_generator/generator.py`.
1. Commit and push both `.md` and the generated `.html` files.
