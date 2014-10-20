use ExtUtils::MakeMaker;
use ExtUtils::PkgConfig;

my $CC = $ENV{'CXX'} || 'g++';

my $shlib_location = ExtUtils::PkgConfig->libs_only_l('hunspell');
my $header_location = ExtUtils::PkgConfig->cflags_only_I('hunspell');

if ($shlib_location ne '' && $header_location ne '') {
    WriteMakefile(
        NAME          => 'Text::Hunspell',
        VERSION_FROM  => 'Hunspell.pm',
        LIBS          => [$shlib_location],
        CC            => $CC,
        LD            => '$(CC)',
        PREREQ_PM     => {
            'ExtUtils::PkgConfig' => 0,
        },
        XSOPT         => '-C++',
        TYPEMAPS      => ['perlobject.map', 'typemap'],
        META_MERGE    => {
            resources => {
                repository => 'https://github.com/cosimo/perl5-text-hunspell',
            },
            keywords  => [ qw(hunspell spelling spell-checker text-processing) ],
        },
    );
}
else {
    # By default, ExtUtils::PkgConfig provides a verbose warning about
    # being unable to locate the pkgconfig file and such. This adds an
    # additional comment after that output.
    warn "\n=========================================================\n";
    warn "NOTE: You may need to install the libhunspell-dev package\n";
    warn "(or the equivalent on your OS).\n";
    warn "=========================================================\n";
}
