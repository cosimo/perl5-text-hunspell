use lib qw(inc);
use Config;
use Devel::CheckLib;

#
# Try to warn the user if linking might fail.
# Some systems seem to not install the unversioned library symlinks.
#
# Probably too platform specific, but seemed an acceptable compromise.
#
my $dlext = $Config{dlext} || 'so';
my $candidate_lib;
for (split " " => $Config{libpth}) {
    my $lib_path = "$_/libhunspell.$dlext";
    #warn "Checking $lib_path\n";
    if (-e $lib_path) {
        $candidate_lib++;
        warn "Found '$lib_path'. Good.\n";
    }
}

if (0 == $candidate_lib) {
    my $def_lib = "/usr/lib/libhunspell";
    my ($possible_candidate) = glob("$def_lib-*.so");
    $possible_candidate ||= "/usr/lib/libhunspell-<ver>.so";
    warn "---------------------------------------------------------------------\n";
    warn "Your system doesn't appear to have a libhunspell.$dlext link.\n";
    warn "Linking might fail. If it does, you might want to try installing\n";
    warn "the libhunspell-dev package (or the equivalent on your OS) or try:\n";
    warn "\n";
    warn "    $Config{lns} $possible_candidate $def_lib.so\n";
    warn "---------------------------------------------------------------------\n";
    warn "\n";
}

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
    META_MERGE    => {
        resources => {
            repository => 'https://github.com/cosimo/perl5-text-hunspell',
        },
        keywords  => [ qw(hunspell spelling spell-checker text-processing) ],
    },
);
