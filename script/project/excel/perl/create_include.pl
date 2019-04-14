#!/usr/bin/perl -w
use strict;

# ">" : data --->file
#Create soc_base_addr.h file

system("perl rm_file.pl");

my $success = open BASEADDR,">>soc_base_addr.h";
if(!$success)
{
		die "Create BASEADDR Failed($!)";	
}

print "Create soc_base_addr.h OK\n";

system("perl parse-excel.pl parse-excel.xls");

close BASEADDR;

#my $content="one;two;three;four\n";
#open(BASEADDR,">>soc_base_addr.h");
#print BASEADDR $content;


#select (BASEADDR);
#$~ = "MYFORMAT";
#write ;

#format MYFORMAT =
#===================================
# Here is the text I want to display.
# The winning number is @<<<<<<!
# $content
#===================================
#. 

 
close BASEADDR;