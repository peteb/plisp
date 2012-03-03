#!/bin/bash
flex plisp.l
bison -d plisp.y
gcc main.c object.c symbol.c list.c eval.c cfun.c lex.yy.c plisp.tab.c  -g -lfl
