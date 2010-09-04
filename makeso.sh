#affentry.o  csutil.o   hashmgr.o   suggestmgr.o
#affixmgr.o  dictmgr.o  hunspell.o  utf_info.o
g++ -I. -I../.. -fPIC -g -c -Wall suggestmgr.cxx
g++ -I. -I../.. -fPIC -g -c -Wall affentry.cxx
g++ -I. -I../.. -fPIC -g -c -Wall csutil.cxx
g++ -I. -I../.. -fPIC -g -c -Wall hashmgr.cxx
g++ -I. -I../.. -fPIC -g -c -Wall hunspell.cxx
g++ -I. -I../.. -fPIC -g -c -Wall affixmgr.cxx
g++ -I. -I../.. -fPIC -g -c -Wall dictmgr.cxx
g++ -I. -I../.. -fPIC -g -c -Wall hunzip.cxx
g++ -I. -I../.. -fPIC -g -c -Wall replist.cxx
g++ -I. -I../.. -fPIC -g -c -Wall filemgr.cxx
g++ -I. -I../.. -fPIC -g -c -Wall phonet.cxx
g++ -I. -I../.. -fPIC -g -c -Wall utf_info.cxx
g++ -shared -Wl,-soname,libhunspell.so.1 -o libhunspell.so.1.0.1 affentry.o  csutil.o   hashmgr.o   suggestmgr.o affixmgr.o  dictmgr.o  hunzip.o replist.o filemgr.o phonet.o  hunspell.o utf_info.o  -lc
# cp libhunspell.so.1.0.1 /usr/local/lib
# to link (otherwise ld does not find .so):
# ln -s /usr/local/lib/libhunspell.so.1.0.1 /usr/local/lib/libhunspell.so
# to execute: (otherwise .so library not found):
# ln -s /usr/local/lib/libhunspell.so.1.0.1 /usr/lib/libhunspell.so.1
# ls -l /lib/libhu*
# ls -l /usr/lib/libhu*
# ls -l /usr/local/lib/libhu*
