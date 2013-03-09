#include "hunspell.h"
#include "assert.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#ifdef __cplusplus
}
#endif


using namespace std;
/*using namespace Hunspell;*/

/* $Id: Hunspell.xs,v 1.5 2002/08/29 20:28:00 moseley Exp $ */

static Hunspell *handle;

/* Needed for static initialization inside XS functions.
   A hack, yes, since 'THIS' is always empty it seems.
*/
static Hunspell * get_hunspell_handle () {
    assert(handle != NULL);
    return handle;
}

static void * get_mortalspace ( size_t nbytes ) {
    SV * mortal;
    mortal = sv_2mortal( NEWSV(0, nbytes ) );
    return (void *)SvPVX(mortal);
}

MODULE = Text::Hunspell        PACKAGE = Text::Hunspell

PROTOTYPES: ENABLE

# Make sure that we have at least xsubpp version 1.922.
REQUIRE: 1.922

Hunspell *
Hunspell::new(aff,dic )
    char *aff;
    char *dic;
    CODE:
        /* Store the new object as static shared handle.
           Every new will overwrite it. Ugly, but reasonable. */
        handle = new Hunspell(aff, dic);
        RETVAL = handle;

    OUTPUT:
        RETVAL


int
Hunspell::delete(h)
    Hunspell *h;
    CODE:
        delete h;
        /* If we deleted our shared static object (most likely)
           then remove the reference to it, so it doesn't get used */
        if (h == handle)
            handle = NULL;

        /* And return something to the caller too. */
        RETVAL = 1;

int
Hunspell::add_dic(dic)
    char *dic;
    CODE:
        handle = get_hunspell_handle();
        RETVAL = handle->add_dic(dic);

    OUTPUT:
        RETVAL

int
Hunspell::check(buf)
    char *buf;
    CODE:
        handle = get_hunspell_handle();
        RETVAL = handle->spell(buf);

    OUTPUT:
        RETVAL

void 
Hunspell::suggest(buf)
    char *buf;
    PREINIT:
        char **wlsti;
	int i, val;
    PPCODE:
        handle = get_hunspell_handle();
        val = handle->suggest(&wlsti, buf);
	for (int i = 0; i < val; i++) {
            PUSHs(sv_2mortal(newSVpv( wlsti[i] ,0 )));
	    free(wlsti[i]);
	}

void 
Hunspell::analyze(buf)
    char *buf;
    PREINIT:
        char **wlsti;
        int i, val;
    PPCODE:
        handle = get_hunspell_handle();
        val = handle->analyze(&wlsti, buf);
        for (i = 0; i < val; i++) {
            PUSHs(sv_2mortal(newSVpv(wlsti[i], 0)));
            free(wlsti[i]);
        }


void 
Hunspell::stem( buf)
    char *buf;
    PREINIT:
        char **wlsti;
	int i, val;
    PPCODE:
        handle = get_hunspell_handle();
        val = handle->stem(&wlsti, buf);
	for (int i = 0; i < val; i++) {
            PUSHs(sv_2mortal(newSVpv( wlsti[i] ,0 )));
	    free(wlsti[i]);
	}


void 
Hunspell::generate( buf, sample)
    char *buf;
    char *sample;
    PREINIT:
        char **wlsti;
	int i, val;
    PPCODE:
        handle = get_hunspell_handle();
        val = handle->generate(&wlsti, buf, sample);
	for (int i = 0; i < val; i++) {
            PUSHs(sv_2mortal(newSVpv( wlsti[i] ,0 )));
	    free(wlsti[i]);
	}


void 
Hunspell::generate2( buf, avref)
    AV * avref;
    char *buf;
    PREINIT:
        char ** array;
        char **wlsti;
        int len;
        SV ** elem;
        int i, val;
    PPCODE:
        len = av_len(avref) + 1;

        /* First allocate some memory for the pointers */
        array = (char **) get_mortalspace( len * sizeof( *array ));

        /* Loop over each element copying pointers to the new array */
        for (i=0; i<len; i++) {
            elem = av_fetch( avref, i, 0 );
            array[i] = SvPV( *elem, PL_na );
        }

        handle = get_hunspell_handle();
        val = handle->generate(&wlsti, buf, array,  len);

        for (int i = 0; i < val; i++) {
            PUSHs(sv_2mortal(newSVpv( wlsti[i] ,0 )));
            free(wlsti[i]);
        }

