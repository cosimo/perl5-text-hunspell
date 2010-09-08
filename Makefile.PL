use lib qw(inc);
use Devel::CheckLib;

# Prompt the user here for any paths and other configuration

check_lib_or_exit(
    lib => 'hunspell',
    header => 'hunspell/hunspell.h',
);

use ExtUtils::MakeMaker;

my $CC = $ENV{"CXX"} || 'g++';

WriteMakefile(
    NAME          => 'Text::Hunspell',
    VERSION_FROM  => 'Hunspell.pm',
    LIBS          => ['-lhunspell'],
    CC            => $CC,
    LD            => '$(CC)',
    PREREQ_PM     => {}, # e.g., Module::Name => 1.1
    XSOPT         => '-C++',
    TYPEMAPS      => ['perlobject.map', 'typemap'],
);

