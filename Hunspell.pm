package Text::Hunspell;

# $Id: Hunspell.pm,v 2.1 2007/07/08 20:28:00 Eleonora Exp $

require DynaLoader;

use vars qw/  @ISA $VERSION /;
@ISA = 'DynaLoader';

$VERSION = '1.21';

bootstrap Text::Hunspell $VERSION;

# Preloaded methods go here.

1;
__END__

=head1 NAME

Text::Hunspell - Perl interface to the GNU Hunspell library

=head1 SYNOPSIS

    use Text::Hunspell;
    my $speller = Text::Hunspell->new("/../language.aff","/../language.dic");

    die unless $speller;


   # Set some words
    my $word = "lótól";
    my $word1 = "lóotól";
    my $misspelled = "lóo";


    # check a word
    print $speller->check( $word )
          ? "$word found\n"
          : "$word not found!\n";

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

    @suggestions = $speller->analyze($word);
    print Data::Dumper::Dumper( \@suggestions ); 
 
    @suggestions = $speller->stem($word);
    print Data::Dumper::Dumper( \@suggestions ); 


    # Test here generator for morphological modification (NOM->ACC)
    @suggestions = $speller->analyze($stem);
    $count = @suggestions;

    # modify analyze output for required class (ACC)
    for($i = 0; $i < $count; $i++){
       $res = @suggestions[$i];
       $res =~ s/NOM/ACC/g;
       @suggestions[$i] = $res;
    }
    # generate ACC class of stem
    @suggestions = $speller->generate2($stem, \@suggestions);
    # end of generator for morphological modification (NOM->ACC) test 

    # test generator for mrphological modification, modify $stem like $word
    @suggestions = $speller->generate($stem, $word);

    # delete speller class
    $speller->delete($speller);

=head1 DESCRIPTION

This module provides a Perl interface to the Oo Hunspell library.  This module
is to meet the need of looking up many words, one at a time, in a single
session, such as spell-checking a document in memory.


The example code describes the interface on http://hunspell.sf.net


=head1 DEPENDENCIES

You MUST have installed GNU Hunspell library version 1.0  or higher on your
system before installing this Text::Hunspell Perl module.  

hunspell location is:

    http://hunspell.sf.net


There have been a number of bug reports because people failed to install hunspell before installing this module.  This is an interface to the hunspell library installed on your system, not a replacement for hunspell.

You must also have one hunspell dictionary installed when running the module's
test suite.

Also, please see the README and Changes files.  README may have specific
information about your platform.



=head1 METHODS

The following methods are available:

=over 4

=item $speller = Text::Hunspell->new(full_path_to_affix, full_path_to_dic);

Creates a new speller object.  New takes the parameters full_path_of_affix file and full_path_of_dic file 
Returns C<undef> if the object could not be created, which is unlikely.

Internally, new() creates the hunspell class.

=item $speller->check($word);
check the word. Passes back 1, if the word found, 0 otherwise.

=item $speller->suggest($misspelled_word);

Passes back the list of suggestions for the misspelled word.

=item $speller->analyze($word);

Passes back the analyzis list for the word.

=item $speller->stem($word);

Passes back the stem list for the word.

=item  $speller->generate2($stem, \@suggestions);

Passes back morphologically modified stem as defined in @suggestions (got by analyzis)

=item $speller->generate($stem, $word);

Passes back morphologically modified stem like $word

=item $string = $speller->delete($speller);

deletes the speller class.


=head1 BUGS

Probably.


=head1 COPYRIGHT

This library is free software; you can redistribute it
and/or modify it under the same terms as Perl itself.


=head1 AUTHOR

Eleonora eleonora46_at_gmx_dot_net

This module is based on a perl module (Text::Aspell) written by Bill Moseley moseley@hank.org.

Hunspell is written as myspell by Kevin B. Hendricks, hunspell is maintained by Németh László

Please see:

    http://hunspell.sf.net
for the dictionaries:
   http://lingucomponent.openoffice.org/spell_dic.html
   http://magyarispell.sf.net for Hungarian dictionary
   

=cut
