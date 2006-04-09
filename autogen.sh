#!/bin/bash


rm -f configure
aclocal
libtoolize --copy --force
automake --copy --add-missing
autoconf
