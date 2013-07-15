#!/bin/bash
rm -rf autoscan.log config.status configure configure.in config.log autom4te.cache config.h.in autoscan.log config.log aclocal.m4 configure.ac COPYING INSTALL AUTHORS ChangeLog config.h config.h.in~ Makefile.in NEWS stamp-h1 README
autoscan
mv configure.scan configure.ac #ou configure.in
autoheader
vim configure.ac #AM_INIT_AUTOMAKE
#echo 'AM_INIT_AUTOMAKE' >> configure.ac
aclocal
autoconf
touch INSTALL NEWS README AUTHORS ChangeLog
automake --add-missing --copy
./configure
#make
#make install

#to work
#http://www.faqs.org/docs/Linux-HOWTO/Program-Library-HOWTO.html
#http://www.lugod.org/presentations/autotools/presentation/autotools.pdf
#http://www.adp-gmbh.ch/misc/tools/configure/small_example.html
#http://developer.gnome.org/doc/GGAD/z70.html
#http://www.gnu.org/software/automake/manual/html_node/Program-and-Library-Variables.html

#en static 
#INCLUDES = -I../../src
#bin_PROGRAMS = 3ds2mat
#3ds2mat_SOURCES = 3ds2mat.c
#CFLAGS = -static
#LDADD =../../src/.libs/lib3ds.a libm.a

#en dynamique 
#INCLUDES = -I../../src

#bin_PROGRAMS = 3ds2mat
#3ds2mat_SOURCES = 3ds2mat.c
##CFLAGS = -static
#LDADD =../../src/.libs/lib3ds.so 

#pour info
# /lib/ld-linux.so.2 --library-path /home/yann/blender/patch_vahm/lib3ds-20080909/src/.libs/ ./3ds2mat
# permet de lancer un pg linké dynamique dans export le LD_LIBRAIRY_PATH

