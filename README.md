The LMNO parser generator
====

LMNO is an LALR(1) parser generator for C or C++. It does the same job as Bison and Yacc. But lmno is not another Yacc clone. It uses a different grammar syntax which is designed to reduce the number of coding errors. LMNO also uses a more sophisticated parsing engine that is faster than Yacc and Bison, and which is both reentrant and thread-safe. Furthermore, LMNO implements features that can be used to eliminate resource leaks, making is suitable for use in long-running programs such as graphical user interfaces or embedded controllers.

Building
--------

For most POSIX type systems, simply cd to the top-level folder and type `make && make install`. This should work for the vast majority of systems; it has very few build dependencies. There's no autoconf, automake, or other configuration scripts to worry about. The following environment variables may be set to customize the makefile's behavior:
```
CC=/usr/bin/gcc
CFLAGS=-std=gnu99 -O2
TOUCH=/usr/bin/touch
PREFIX=/usr/local/bin
```

Command Line Options
--------------------

The behavior of LMNO can be modified using command-line options. You can obtain a list of the available command-line options together with a brief explanation of what each does by typing

 `lmno -h`

As of this writing, the following command-line options are supported:
```
   -b           Print only the basis in report.
   -C           Generate C language parser (the default is a C++ parser).
   -c           Do not compress the action table.
   D=<string>   Define an %ifdef macro.
   -g           Print grammar without actions.
   -q           (Quiet) Do not print the report file.
   -s           Print parser stats to standard output.
   -v           Print version info and exit.
   -h           Print this help message and exit.
```

Writing Grammars
----------------

One writes grammar files in a language that is functionally very similar to standard Backus-Nauer Form. You may include inline code to be executed for each reduction, e.g. for building a parse tree, or directly executing interpreted code. Further details can be found in the LMNO [wiki](https://github.com/IonoclastBrigham/lmno/wiki).
