#!/bin/sh
find . -iname *.cxx -o -iname *.hxx | xargs clang-format -i
