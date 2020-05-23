This is a command-line tool to read [elastic tabstops](http://nickgravgaard.com/elastic-tabstops/) in the terminal.

It supports unicode by way of the ICU library.

It supports a few arguments:
-'-t', which takes an integer and defines the minimal length of tabs (default: 4).
-'--block-end-chars', which takes a list of chars and defines the characters after which the next line must be considered a separate indentation block (default: :{).
