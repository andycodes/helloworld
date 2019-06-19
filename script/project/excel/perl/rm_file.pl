#!/usr/bin/perl -w

use strict;

my $filename = "soc_base_addr.h";
 
if( -e $filename)
 {
    print "rm file \n";
    unlink($filename); # rm file
    
 }
 else
 {
    print "file no exist\n";
 }