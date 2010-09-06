package Text::Hunspell;

require DynaLoader;

use vars qw/  @ISA $VERSION /;
@ISA = 'DynaLoader';

$VERSION = '2.00';

bootstrap Text::Hunspell $VERSION;

# Preloaded methods go here.

1;
__END__

=head1 NAME

Text::Hunspell - Perl interface to the GNU Hunspell library

=head1 SYNOPSIS

    # For this example to work, you have to have
    # the US english dictionary installed!

    use strict;
    use warnings;

    use Data::Dumper ();
    use Text::Hunspell;

    # You can use relative or absolute paths.
    my $speller = Text::Hunspell->new(
        "/usr/share/hunspell/en_US.aff",    # Hunspell affix file
        "/usr/share/hunspell/en_US.dic"     # Hunspell dictionary file
    );

    die unless $speller;

    # Check a word against the dictionary
    my $word = 'opera';
    print $speller->check($word)
          ? "'$word' found in the dictionary\n"
          : "'$word' not found in the dictionary!\n";

    # Spell check suggestions
    my $misspelled = 'programmng';
    my @suggestions = $speller->suggest($misspelled);
    print "\n", "You typed '$misspelled'. Did you mean?\n";
    for (@suggestions) {
        print "  - $_\n";
    }

    # Analysis of a word
    $word = 'automatic';
    my $analysis = $speller->analyze($word);
    print "\n", "Analysis of '$word' returns '$analysis'\n";

    # Word stemming
    $word = 'development';
    my @stemming = $speller->stem($word);
    print "\n", "Stemming of '$word' returns:\n";
    for (@stemming) {
        print "  - $_\n";
    }

    
    #------------------------------------------
    # ADVANCED STUFF FROM HERE
    # NOT SURE HOW IT SHOULD WORK
    #------------------------------------------

    #
    # Test here generator for morphological modification (NOM->ACC)
    #
    $word = 'developer';
    my $stem = 'computer';
    @suggestions = $speller->analyze($stem);
    # Modify analyze output for required class (ACC)
    for (@suggestions) {
       s/NOM/ACC/g;
    }
    # Generate ACC class of stem
    @suggestions = $speller->generate2($stem, \@suggestions);
    print "Morphological modification generator...\n";
    print Data::Dumper::Dumper(\@suggestions);


    #
    # Test generator for morphological modification,
    # modify $stem like $word
    #
    @suggestions = $speller->generate($stem, $word);
    print "Morphological modification generator...\n";
    print Data::Dumper::Dumper(\@suggestions);

    # Deletes the underlying Hunspell C/C++ object
    $speller->delete($speller);


=head1 DESCRIPTION

This module provides a Perl interface to the OO B<Hunspell> library.  This module
is to meet the need of looking up many words, one at a time, in a single
session, such as spell-checking a document in memory.

The example code describes the interface on http://hunspell.sf.net


=head1 DEPENDENCIES

B<You MUST have installed GNU Hunspell library version 1.0 or higher>
on your system before installing this C<Text::Hunspell> Perl module.  

Hunspell location is:

    http://hunspell.sf.net

There have been a number of bug reports because people failed to install hunspell
before installing this module.

This is an interface to the hunspell library installed on your system,
not a replacement for hunspell.

You must also have one hunspell dictionary installed when running the module's
test suite.

Also, please see the README and Changes files.  README may have specific
information about your platform.


=head1 METHODS

The following methods are available:

=over 4

=item $speller = Text::Hunspell->new($full_path_to_affix, $full_path_to_dic);

Creates a new speller object.  New takes the parameters full_path_of_affix file and full_path_of_dic file 
Returns C<undef> if the object could not be created, which is unlikely.

Internally, new() creates the hunspell class.

=item $speller->check($word);

Check the word. Passes back 1, if the word found, 0 otherwise.

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

=back

=head1 BUGS

Probably.
Yes, definitely.

=head1 COPYRIGHT

This library is free software; you can redistribute it
and/or modify it under the same terms as Perl itself.

=head1 AUTHORS

    Eleonora, E<lt>eleonora46_at_gmx_dot_netE<gt>

Current maintainer is:

    Cosimo Streppone, E<lt>cosimo@cpan.orgE<gt>

This module is based on a L<Text::Aspell>
written by Bill Moseley moseley at hank dot org.

Hunspell is written as myspell by Kevin B. Hendricks,
Hunspell is maintained by Németh László.

Please see:

    http://hunspell.sf.net

For the dictionaries:

   http://lingucomponent.openoffice.org/spell_dic.html
   http://magyarispell.sf.net for Hungarian dictionary

=cut
