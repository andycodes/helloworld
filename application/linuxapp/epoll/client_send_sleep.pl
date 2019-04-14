#!/usr/bin/perl
use IO::Socket;

my $host = "127.0.0.1";
my $port = 5000;

my $socket = IO::Socket::INET ->new("$host:$port") or die "create socket err $@";
my $msg_out = "fansaihua";
print $socket $msg_out;
print "now send over ,go to sleep..\n";
sleep(5);
print "5 second gone... send another line\n";
print $socket $msg_out;

while(1)
{
	sleep(1);
}
