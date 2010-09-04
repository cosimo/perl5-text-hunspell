use ExtUtils::MakeMaker;

my $CC = $ENV{"CXX"} || 'g++';

# $Id: Makefile.PL,v 1.3 2002/08/26 02:40:25 moseley Exp $

WriteMakefile(
    NAME          => 'Text::Hunspell',
    VERSION_FROM  => 'Hunspell.pm',
    LIBS          => ['-lhunspell'],
    'CC'                => $CC,
    'LD'                => '$(CC)',
     PREREQ_PM     => {}, # e.g., Module::Name => 1.1
    'XSOPT'             => '-C++',
    'TYPEMAPS'          => ['perlobject.map', 'typemap' ],
    test => {'TESTS'     =>'t/test.pl'},
);
