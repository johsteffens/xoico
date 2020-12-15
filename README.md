# Xoila Compiler

Xoico is a self-hosting compiler for [xoila](https://github.com/johsteffens/beth#xoila)-code.

It generates c-source code, which is stored in files named `*.xo.{c,h}`.

Configuration files `*_xoico.cfg` specify how xoico is to navigate through the sources.
I tried to make them self-explanatory.

***More details will follow ...***

## Getting Started

```
$ git clone https://github.com/johsteffens/beth
$ git clone https://github.com/johsteffens/xoico
$ cd xoico
$ make
$ ./bin/xoico --help
```

## About Xoila

Xoila is a meta-language designed along with
the [beth](https://github.com/johsteffens/beth)-framework.
Xoila-code is typically embedded in c-header files. 
It can also occur in dedicated files, which have the extension `*.x`.

Inside a header file the xoila-section is enclosed by #ifdef XOILA_SECTION ... #endif.
The (pseudo-)macro XOILA_SECTION is to be unknown by the C-compiler,
so it will not try to interpret the enclosed code.
Xoico, on the other hand, uses this keyword to determine the code block to be comiled.

Xoila is used in conjunction with library bcore of [beth](https://github.com/johsteffens/beth).
It provides a convenient programming layer unlocking core concepts of project beth.

(*Xoila* was initially called *Beth-Plant*.)

***More details will follow ...***

------

<sub>&copy; Johannes B. Steffens</sub>

