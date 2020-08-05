# Xoila Compiler

This tool compiles xoila-code, which is embedded in c-header files.
It creates or updates \*_xoi_out.{c,h} files as specified by xoico-configuration files (\*_xoico.cfg).

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

Xoila is the name of a meta language intended to be embedded in C-Header files.
The xoila-section is enclosed by #ifdef \<tag\> ... #endif. \<tag\> is unknown by
the c-compiler, so it skips over this section. Xoico detects this definition.

Xoila is used in conjunction with the core library of [beth](https://github.com/johsteffens/beth).
It provides a convenient programming layer unlocking core concepts of project beth.

(*Xoila* was initially called *Beth-Plant*.)

------

<sub>&copy; Johannes B. Steffens</sub>

