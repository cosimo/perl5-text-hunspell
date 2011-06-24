package Text::Hunspell;

require DynaLoader;

use vars qw/  @ISA $VERSION /;
@ISA = 'DynaLoader';

$VERSION = '2.03';

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

This module provides a Perl interface to the OO B<Hunspell> library.
This module is to meet the need of looking up many words,
one at a time, in a single session, such as spell-checking
a document in memory.

The example code describes the interface on http://hunspell.sf.net

=head1 DEPENDENCIES

B<You MUST have installed GNU Hunspell library version 1.0 or higher>
on your system before installing this C<Text::Hunspell> Perl module.

Hunspell location is:

    http://hunspell.sf.net

There have been a number of bug reports because people failed to install
hunspell before installing this module.

This is an interface to the hunspell library installed on your system,
not a replacement for hunspell.

You must also have one hunspell dictionary installed when running the module's
test suite.

Also, please see the README and Changes files.  README may have specific
information about your platform.

=head1 METHODS

The following methods are available:

=head2 C<Text::Hunspell->new($full_path_to_affix, $full_path_to_dic)>

Creates a new speller object. Parameters are:

=over 4

=item full path of affix file

=item full path of dictionary (dic) file

=back

Returns C<undef> if the object could not be created, which is unlikely.

=head2 C<check($word)>

Check the word. Returns 1 if the word is found, 0 otherwise.

=head2 C<suggest($misspelled_word)>

Returns the list of suggestions for the misspelled word.

=head2 C<analyze($word)>

Returns the analysis list for the word.
TODO HOW? What does it return??

See the examples in the examples/ folder for now.

=head2 C<stem($word)>

Returns the stem list for the word.

=head2 C<generate2($stem, \@suggestions)>

Returns a morphologically modified stem as defined in
C<@suggestions> (got by analysis).

TODO Explain ...

=head2 C<generate($stem, $word)>

Returns morphologically modified stem like $word.

TODO WHY IS THIS DIFFERENT FROM generate2() ???
EXPLAIN.

=head2 C<$speller->delete($speller)>

Deletes the speller class.

TODO WHY IS THIS NEEDED?? Called on C<$speller> and needs C<$speller> ???

=head1 BUGS

Probably. Yes, definitely.

=head1 COPYRIGHT

This library is free software; you can redistribute it
and/or modify it under the same terms as Perl itself.

=head1 AUTHORS

    Eleonora, E<lt>eleonora46_at_gmx_dot_netE<gt>

Current maintainer is:

    Cosimo Streppone, E<lt>cosimo@cpan.orgE<gt>

This module is based on a L<Text::Aspell>
written by Bill Moseley moseley at hank dot org.

Hunspell is written as myspell by Kevin B. Hendricks.

Hunspell is maintained by Németh László.

Please see:

    http://hunspell.sf.net

For the dictionaries:

   http://lingucomponent.openoffice.org/spell_dic.html
   http://magyarispell.sf.net for Hungarian dictionary

=cut
