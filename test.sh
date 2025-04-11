#!/bin/sh
########################################################################
##                  Super Light Regular Expressions                   ##
##                                                                    ##
##             Copyright (C) 2019-2024 Alexander Nicholi.             ##
##           Copyright (C) 2024-2025 Aquefir Consulting LLC           ##
##            Released under GNU General Public License v2            ##
##                                                                    ##
##   This program is free software;  you can redistribute it and/or   ##
##   modify it under the terms of the GNU General Public License as   ##
##       published by the  Free Software Foundation; version 2.       ##
##                                                                    ##
##  This program is distributed in  the hope that it will be useful,  ##
##   but WITHOUT ANY WARRANTY; without even the implied warranty of   ##
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  ##
##              General Public License for more details.              ##
##                                                                    ##
## You should have received a copy of the  GNU General Public License ##
##    along with this program;  if not, write to the Free Software    ##
##    Foundation, Inc, 51 Franklin Street, Fifth Floor, Boston, MA    ##
##                          02110-1301, USA.                          ##
########################################################################

cc -otest test.c slre.c
./test
rm -f test
