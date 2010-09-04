#!/usr/bin/perl -w
# first install perl-devel
#  then install Text::Hunspell
#
use Text::Hunspell;
use Data::Dumper;
    my $curDir;
    $currDir = `pwd`;
    chomp $currDir;
 #   print $currDir."/test.aff","\n";
   my $speller = Text::Hunspell->new($currDir."/t/test.aff", $currDir."/t/test.dic");

    die unless $speller;


    # Set some words
    my $word = "lótól";
    my $word1 = "lóotól";
    my $misspelled = "lóo";

    # check a word
    print $speller->check( $word )
          ? "$word found\n"
          : "$word not found!\n";
    print $speller->check( $word1 )
          ? "$word1 found\n"
          : "$word1 not found!\n";

    # lookup up words
    my @suggestions;
    @suggestions = $speller->suggest( $misspelled );
    print Data::Dumper::Dumper( \@suggestions ); 

    $speller->delete($speller);
    print "1..3\n";
    print "ok\n";
    print "ok\n";
    print "ok\n";

 
