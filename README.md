# Xoila Compiler

This tool compiles xoila-code, which is embedded in c-header files.
It creates or updates \*_xoila_out.{c,h} files as specified by xoico-configuration files (\*_xoico.cfg).

***More details will follow ...***

## Getting Started

```
$ git clone https://github.com/johsteffens/beth
$ git clone https://github.com/johsteffens/xoico
$ cd xoico
$ make
$ ./xoico --help
```

## About Xoila

Xoila is the name of a meta language intended to be embedded in C-header files.
The xoila-section is enclosed by #ifdef XOILA_SECTION ... #endif.

The (pseudo-)macro XOILA_SECTION is to be unknown by the C-compiler,
so it will not try to interpret xoila code.
Xoico, on the other hand, uses this keyword to determine the xoila code block.

Xoila is used in conjunction with library bcore of [beth](https://github.com/johsteffens/beth).
It provides a convenient programming layer unlocking core concepts of project beth.

(*Xoila* was initially called *Beth-Plant*.)

------

<sub>&copy; Johannes B. Steffens</sub>

