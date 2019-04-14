#!/usr/bin/perl -w

use strict;
use Spreadsheet::ParseExcel;

my $oExcel = new Spreadsheet::ParseExcel;

die "You must provide a filename to $0 to be parsed as an Excel file" unless @ARGV;

my $oBook = $oExcel->Parse($ARGV[0]);
my($iR, $iC, $oWkS, $oWkC);

# FILE NAME
print "FILE  :", $oBook->{File} , "\n";
# SHEET COUNT
print "SHEET COUNT :", $oBook->{SheetCount} , "\n";
print "AUTHOR:", $oBook->{Author} , "\n"
if defined $oBook->{Author};

open(BASEADDR,">>soc_base_addr.h");

for(my $iSheet=0; $iSheet < $oBook->{SheetCount} ; $iSheet++)
{
 $oWkS = $oBook->{Worksheet}[$iSheet];
 print "\n--------- SHEET:", $oWkS->{Name}, "\n";
 for(my $iR = $oWkS->{MinRow} ;
     defined $oWkS->{MaxRow} && $iR <= $oWkS->{MaxRow} ;
     $iR++)
 {
 	print "#define ";
 	print BASEADDR "#define ";
 	
  for(my $iC = $oWkS->{MinCol} ;
      defined $oWkS->{MaxCol} && $iC <= $oWkS->{MaxCol} ;
      $iC++)
  {
   $oWkC = $oWkS->{Cells}[$iR][$iC];
   #print "( $iR , $iC ) =>", $oWkC->Value,"\n"  if($oWkC);
   print " ", $oWkC->Value,  if($oWkC);
   print BASEADDR " ", $oWkC->Value,  if($oWkC);
  }
  
  print "\n";
  print BASEADDR "\n";
 }
}

close BASEADDR;