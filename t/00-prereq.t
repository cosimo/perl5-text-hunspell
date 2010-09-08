use Test::More tests => 1;

use lib qw(inc ../inc);
use Devel::CheckLib;

check_lib_or_exit(
    lib => 'hunspell',
    header => 'hunspell/hunspell.h',
);

ok(1, 'Prerequisite hunspell library found');

