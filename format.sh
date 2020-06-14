#!/bin/sh
find ./engine ./game -iname *.cxx -o -iname *.hxx | xargs clang-format -i
