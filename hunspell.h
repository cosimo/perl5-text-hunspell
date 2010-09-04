#ifndef _HTYPES_HXX_
#define _HTYPES_HXX_

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <time.h>


#define MAXCONDLEN      20
#define MAXCONDLEN_1    (MAXCONDLEN - sizeof(char *))

#define MAXDELEN    256

#define ROTATE_LEN   5

#define ROTATE(v,q) \
   (v) = ((v) << (q)) | (((v) >> (32 - q)) & ((1 << (q))-1));

// hentry options
#define H_OPT        (1 << 0)
#define H_OPT_ALIASM (1 << 1)
#define H_OPT_PHON   (1 << 2)

// see also csutil.hxx
#define HENTRY_WORD(h) &(h->word)

// approx. number  of user defined words
#define USERWORD 1000

#ifdef HUNSPELL_STATIC
	#define DLLEXPORT
#else
	#ifdef HUNSPELL_EXPORTS
		#define DLLEXPORT  __declspec( dllexport )
	#else
		#define DLLEXPORT  __declspec( dllimport )
	#endif
#endif
#define MAXCONDLEN      20
#define MAXCONDLEN_1    (MAXCONDLEN - sizeof(char *))

#ifndef _HUNZIP_HXX_
#define _HUNZIP_HXX_

#define BUFSIZE  65536
#define HZIP_EXTENSION ".hz"

#define MSG_OPEN   "error: %s: cannot open\n"
#define MSG_FORMAT "error: %s: not in hzip format\n"
#define MSG_MEMORY "error: %s: missing memory\n"
#define MSG_KEY    "error: %s: missing or bad password\n"

struct bit {
    unsigned char c[2];
    int v[2];
};

class Hunzip
{

protected:
    char * filename;
    FILE * fin;
    int bufsiz, lastbit, inc, inbits, outc;
    struct bit * dec;        // code table
    char in[BUFSIZE];        // input buffer
    char out[BUFSIZE + 1];   // Huffman-decoded buffer
    char line[BUFSIZE + 50]; // decoded line
    int getcode(const char * key);
    int getbuf();
    int fail(const char * err, const char * par);
    
public:   
    Hunzip(const char * filename, const char * key = NULL);
    ~Hunzip();
    const char * getline();
};

#endif

#ifndef _FILEMGR_HXX_
#define _FILEMGR_HXX_

class FileMgr
{
protected:
    FILE * fin;
    Hunzip * hin;
    char in[BUFSIZE + 50]; // input buffer
    int fail(const char * err, const char * par);
    int linenum;

public:
    FileMgr(const char * filename, const char * key = NULL);
    ~FileMgr();
    char * getline();
    int getlinenum();
};
#endif


#ifndef __WCHARHXX__
#define __WCHARHXX__

typedef struct {
    unsigned char l;
    unsigned char h;
} w_char;

// two character arrays
struct replentry {
  char * pattern;
  char * pattern2;
};
#endif

#ifndef __CSUTILHXX__
#define __CSUTILHXX__

// First some base level utility routines


// convert UTF-16 characters to UTF-8
char * u16_u8(char * dest, int size, const w_char * src, int srclen);

// convert UTF-8 characters to UTF-16
int u8_u16(w_char * dest, int size, const char * src);

// sort 2-byte vector
void flag_qsort(unsigned short flags[], short begin, short end);

// binary search in 2-byte vector
int flag_bsearch(unsigned short flags[], unsigned short flag, short right);

// remove end of line char(s)
void   mychomp(char * s);

// duplicate string
char * mystrdup(const char * s);

// duplicate reverse of string
char * myrevstrdup(const char * s);

// parse into tokens with char delimiter
char * mystrsep(char ** sptr, const char delim);

// parse into tokens with char delimiter
char * mystrrep(char *, const char *, const char *);

// is one string a leading subset of another
int    isSubset(const char * s1, const char * s2);

// is one reverse string a leading subset of the end of another   
int    isRevSubset(const char * s1, const char * s2, int len);

// append s to ends of every lines in text
void strlinecat(char * lines, const char * s);

// tokenize into lines with new line
   int line_tok(const char * text, char *** lines);

// tokenize into lines with new line and uniq in place
   char * line_uniq(char * text);

// change \n to c in place
   char * line_join(char * text, char c);

// leave only last {[^}]*} pattern in string
   char * delete_zeros(char * morphout);

// reverse word
   void reverseword(char *);

// reverse word
   void reverseword_utf(char *);

// character encoding information
struct cs_info {
  unsigned char ccase;
  unsigned char clower;
  unsigned char cupper;
};

// Unicode character encoding information
struct unicode_info {
  unsigned short ccase;
  unsigned short cupper;
  unsigned short clower;
};

struct unicode_info2 {
  char ccase;
  unsigned short cupper;
  unsigned short clower;
};

struct enc_entry {
  const char * enc_name;
  struct cs_info * cs_table;
};

// language to encoding default map

struct lang_map {
  const char * lang;
  const char * def_enc;
  int num;
};

struct cs_info * get_current_cs(const char * es);

struct unicode_info * get_utf_cs();

int get_utf_cs_len();

const char * get_default_enc(const char * lang);

int get_lang_num(const char * lang);

// convert null terminated string to all caps using encoding
void enmkallcap(char * d, const char * p, const char * encoding);

// convert null terminated string to all little using encoding
void enmkallsmall(char * d, const char * p, const char * encoding);

// convert null terminated string to have intial capital using encoding
void enmkinitcap(char * d, const char * p, const char * encoding);

// convert null terminated string to all caps
void mkallcap(char * p, const struct cs_info * csconv);

// convert null terminated string to all little
void mkallsmall(char * p, const struct cs_info * csconv);

// convert null terminated string to have intial capital
void mkinitcap(char * p, const struct cs_info * csconv);

// convert first nc characters of UTF-8 string to little
void mkallsmall_utf(w_char * u, int nc, struct unicode_info2 * utfconv);

#endif


struct hentry
{
  unsigned char blen; // word length in bytes
  unsigned char clen; // word length in characters (different for UTF-8 enc.)
  short    alen;      // length of affix flag vector
  unsigned short * astr;  // affix flag vector
  struct   hentry * next; // next word with same hash code
  struct   hentry * next_homonym; // next homonym word (with same hash code)
  char     var;       // variable fields (only for special pronounciation yet)
  char     word;      // variable-length word (8-bit or UTF-8 encoding)
};

#endif


#ifndef _HASHMGR_HXX_
#define _HASHMGR_HXX_
enum flag { FLAG_CHAR, FLAG_LONG, FLAG_NUM, FLAG_UNI };

class HashMgr
{
  int               tablesize;
  struct hentry **  tableptr;
  int               userword;
  flag              flag_mode;
  int               complexprefixes;
  int               utf8;
  unsigned short    forbiddenword;
  int               langnum;
  char *            enc;
  char *            lang;
  struct cs_info *  csconv;
  char *            ignorechars;
  unsigned short *  ignorechars_utf16;
  int               ignorechars_utf16_len;
  int               numaliasf; // flag vector `compression' with aliases
  unsigned short ** aliasf;
  unsigned short *  aliasflen;
  int               numaliasm; // morphological desciption `compression' with aliases
  char **           aliasm;


public:
  HashMgr(const char * tpath, const char * apath, const char * key = NULL);
  ~HashMgr();

  struct hentry * lookup(const char *) const;
  int hash(const char *) const;
  struct hentry * walk_hashtable(int & col, struct hentry * hp) const;

  int add(const char * word);
  int add_with_affix(const char * word, const char * pattern);
  int remove(const char * word);
  int decode_flags(unsigned short ** result, char * flags, FileMgr * af);
  unsigned short        decode_flag(const char * flag);
  char *                encode_flag(unsigned short flag);
  int is_aliasf();
  int get_aliasf(int index, unsigned short ** fvec, FileMgr * af);
  int is_aliasm();
  char * get_aliasm(int index);

private:
  int get_clen_and_captype(const char * word, int wbl, int * captype);
  int load_tables(const char * tpath, const char * key);
  int add_word(const char * word, int wbl, int wcl, unsigned short * ap,
    int al, const char * desc, bool onlyupcase);
  int load_config(const char * affpath, const char * key);
  int parse_aliasf(char * line, FileMgr * af);
  int add_hidden_capitalized_word(char * word, int wbl, int wcl,
    unsigned short * flags, int al, char * dp, int captype);
  int parse_aliasm(char * line, FileMgr * af);
  int remove_forbidden_flag(const char * word);

};

#endif

#ifndef _ATYPES_HXX_
#define _ATYPES_HXX_

// HUNSTEM def.
#define HUNSTEM

#define SETSIZE         256
#define CONTSIZE        65536
#define MAXWORDLEN      100
#define MAXWORDUTF8LEN  (MAXWORDLEN * 4)
#define XPRODUCT        (1 << 0)

enum {IN_CPD_NOT, IN_CPD_BEGIN, IN_CPD_END};

#define MAXLNLEN        8192 * 4

#define MAXCOMPOUND	10

#define MAXACC          1000

#define MISSING_DESCRIPTION "[<missing_description>]"

#define FLAG unsigned short
#define FLAG_NULL 0x00
#define FREE_FLAG(a) a = 0

#define TESTAFF( a, b , c ) flag_bsearch((unsigned short *) a, (unsigned short) b, c)

struct affentry
{
   char * strip;
   char * appnd;
   unsigned char stripl;
   unsigned char appndl;
   char  numconds;
   char  opts;
   unsigned short aflag;
   unsigned short * contclass;
   short        contclasslen;
   union {
     char conds[MAXCONDLEN];
     struct {
       char conds1[MAXCONDLEN_1];
       char * conds2;
     } l;
   } c;
   char *       morphcode;
};

struct guessword {
  char * word;
  bool allow;
  char * orig;
};

struct mapentry {
  char * set;
  w_char * set_utf16;
  int len;
};

struct flagentry {
  FLAG * def;
  int len;
};

struct patentry {
  char * pattern;
  char * pattern2;
  char * pattern3;
  FLAG cond;
  FLAG cond2;
};

#endif
#ifndef __PHONETHXX__
#define __PHONETHXX__

#define HASHSIZE          256
#define MAXPHONETLEN      256
#define MAXPHONETUTF8LEN  (MAXPHONETLEN * 4)

struct phonetable {
  char utf8;
  cs_info * lang;
  int num;
  char * * rules;
  int hash[HASHSIZE];
};

void init_phonet_hash(phonetable & parms);

int phonet (const char * inword, char * target,
              int len, phonetable & phone);
#endif

#ifndef _BASEAFF_HXX_
#define _BASEAFF_HXX_

class AffEntry
{
public:

protected:
    char *         appnd;
    char *         strip;
    unsigned char  appndl;
    unsigned char  stripl;
    char           numconds;
    char           opts;
    unsigned short aflag;
    union {
        char       conds[MAXCONDLEN];
        struct {
            char   conds1[MAXCONDLEN_1];
            char * conds2;
        } l;
    } c;
    char *           morphcode;
    unsigned short * contclass;
    short            contclasslen;
};

#endif


#ifndef _HASHMGR_HXX_
#define _HASHMGR_HXX_

e
enum flag { FLAG_CHAR, FLAG_LONG, FLAG_NUM, FLAG_UNI };

class HashMgr
{
  int               tablesize;
  struct hentry **  tableptr;
  int               userword;
  flag              flag_mode;
  int               complexprefixes;
  int               utf8;
  unsigned short    forbiddenword;
  int               langnum;
  char *            enc;
  char *            lang;
  struct cs_info *  csconv;
  char *            ignorechars;
  unsigned short *  ignorechars_utf16;
  int               ignorechars_utf16_len;
  int               numaliasf; // flag vector `compression' with aliases
  unsigned short ** aliasf;
  unsigned short *  aliasflen;
  int               numaliasm; // morphological desciption `compression' with aliases
  char **           aliasm;


public:
  HashMgr(const char * tpath, const char * apath, const char * key = NULL);
  ~HashMgr();

  struct hentry * lookup(const char *) const;
  int hash(const char *) const;
  struct hentry * walk_hashtable(int & col, struct hentry * hp) const;

  int add(const char * word);
  int add_with_affix(const char * word, const char * pattern);
  int remove(const char * word);
  int decode_flags(unsigned short ** result, char * flags, FileMgr * af);
  unsigned short        decode_flag(const char * flag);
  char *                encode_flag(unsigned short flag);
  int is_aliasf();
  int get_aliasf(int index, unsigned short ** fvec, FileMgr * af);
  int is_aliasm();
  char * get_aliasm(int index);

private:
  int get_clen_and_captype(const char * word, int wbl, int * captype);
  int load_tables(const char * tpath, const char * key);
  int add_word(const char * word, int wbl, int wcl, unsigned short * ap,
    int al, const char * desc, bool onlyupcase);
  int load_config(const char * affpath, const char * key);
  int parse_aliasf(char * line, FileMgr * af);
  int add_hidden_capitalized_word(char * word, int wbl, int wcl,
    unsigned short * flags, int al, char * dp, int captype);
  int parse_aliasm(char * line, FileMgr * af);
  int remove_forbidden_flag(const char * word);

};

#endif

#ifndef _REPLIST_HXX_
#define _REPLIST_HXX_

class RepList
{
protected:
    replentry ** dat;
    int size;
    int pos;

public:
    RepList(int n);
    ~RepList();

    int get_pos();
    int add(char * pat1, char * pat2);
    replentry * item(int n);
    int near(const char * word);
    int match(const char * word, int n);
    int conv(const char * word, char * dest);
};
#endif


#ifndef _AFFIXMGR_HXX_
#define _AFFIXMGR_HXX_

#define dupSFX        (1 << 0)
#define dupPFX        (1 << 1)

class AffixMgr
{

  AffEntry *          pStart[SETSIZE];
  AffEntry *          sStart[SETSIZE];
  AffEntry *          pFlag[SETSIZE];
  AffEntry *          sFlag[SETSIZE];
  HashMgr *           pHMgr;
  HashMgr **          alldic;
  int *               maxdic;
  char *              keystring;
  char *              trystring;
  char *              encoding;
  struct cs_info *    csconv;
  int                 utf8;
  int                 complexprefixes;
  FLAG                compoundflag;
  FLAG                compoundbegin;
  FLAG                compoundmiddle;
  FLAG                compoundend;
  FLAG                compoundroot;
  FLAG                compoundforbidflag;
  FLAG                compoundpermitflag;
  int                 checkcompounddup;
  int                 checkcompoundrep;
  int                 checkcompoundcase;
  int                 checkcompoundtriple;
  int                 simplifiedtriple;
  FLAG                forbiddenword;
  FLAG                nosuggest;
  FLAG                needaffix;
  int                 cpdmin;
  int                 numrep;
  replentry *         reptable;
  RepList *           iconvtable;
  RepList *           oconvtable;
  int                 nummap;
  mapentry *          maptable;
  int                 numbreak;
  char **             breaktable;
  int                 numcheckcpd;
  patentry *          checkcpdtable;
  int                 simplifiedcpd;
  int                 numdefcpd;
  flagentry *         defcpdtable;
  phonetable *        phone;
  int                 maxngramsugs;
  int                 nosplitsugs;
  int                 sugswithdots;
  int                 cpdwordmax;
  int                 cpdmaxsyllable;
  char *              cpdvowels;
  w_char *            cpdvowels_utf16;
  int                 cpdvowels_utf16_len;
  char *              cpdsyllablenum;
  const char *        pfxappnd; // BUG: not stateless
  const char *        sfxappnd; // BUG: not stateless
  FLAG                sfxflag;  // BUG: not stateless
  char *              derived;  // BUG: not stateless
  AffEntry *          sfx;      // BUG: not stateless
  AffEntry *          pfx;      // BUG: not stateless
  int                 checknum;
  char *              wordchars;
  unsigned short *    wordchars_utf16;
  int                 wordchars_utf16_len;
  char *              ignorechars;
  unsigned short *    ignorechars_utf16;
  int                 ignorechars_utf16_len;
  char *              version;
  char *              lang;
  int                 langnum;
  FLAG                lemma_present;
  FLAG                circumfix;
  FLAG                onlyincompound;
  FLAG                keepcase;
  FLAG                substandard;
  int                 checksharps;
  int                 fullstrip;

  int                 havecontclass; // boolean variable
  char                contclasses[CONTSIZE]; // flags of possible continuing classes (twofold affix)

public:

  AffixMgr(const char * affpath, HashMgr** ptr, int * md,
    const char * key = NULL);
  ~AffixMgr();
  struct hentry *     affix_check(const char * word, int len,
            const unsigned short needflag = (unsigned short) 0,
            char in_compound = IN_CPD_NOT);
  struct hentry *     prefix_check(const char * word, int len,
            char in_compound, const FLAG needflag = FLAG_NULL);
  inline int isSubset(const char * s1, const char * s2);
  struct hentry *     prefix_check_twosfx(const char * word, int len,
            char in_compound, const FLAG needflag = FLAG_NULL);
  inline int isRevSubset(const char * s1, const char * end_of_s2, int len);
  struct hentry *     suffix_check(const char * word, int len, int sfxopts,
            AffEntry* ppfx, char ** wlst, int maxSug, int * ns,
            const FLAG cclass = FLAG_NULL, const FLAG needflag = FLAG_NULL,
            char in_compound = IN_CPD_NOT);
  struct hentry *     suffix_check_twosfx(const char * word, int len,
            int sfxopts, AffEntry* ppfx, const FLAG needflag = FLAG_NULL);

  char * affix_check_morph(const char * word, int len,
            const FLAG needflag = FLAG_NULL, char in_compound = IN_CPD_NOT);
  char * prefix_check_morph(const char * word, int len,
            char in_compound, const FLAG needflag = FLAG_NULL);
  char * suffix_check_morph (const char * word, int len, int sfxopts,
            AffEntry * ppfx, const FLAG cclass = FLAG_NULL,
            const FLAG needflag = FLAG_NULL, char in_compound = IN_CPD_NOT);

  char * prefix_check_twosfx_morph(const char * word, int len,
            char in_compound, const FLAG needflag = FLAG_NULL);
  char * suffix_check_twosfx_morph(const char * word, int len,
            int sfxopts, AffEntry * ppfx, const FLAG needflag = FLAG_NULL);

  char * morphgen(char * ts, int wl, const unsigned short * ap,
            unsigned short al, char * morph, char * targetmorph, int level);

  int    expand_rootword(struct guessword * wlst, int maxn, const char * ts,
            int wl, const unsigned short * ap, unsigned short al, char * bad,
            int, char *);

  short       get_syllable (const char * word, int wlen);
  int         cpdrep_check(const char * word, int len);
  int         cpdpat_check(const char * word, int len, hentry * r1, hentry * r2);
  int         defcpd_check(hentry *** words, short wnum, hentry * rv,
                    hentry ** rwords, char all);
  int         cpdcase_check(const char * word, int len);
  inline int  candidate_check(const char * word, int len);
  void        setcminmax(int * cmin, int * cmax, const char * word, int len);
  struct hentry * compound_check(const char * word, int len, short wordnum,
            short numsyllable, short maxwordnum, short wnum, hentry ** words,
            char hu_mov_rule, char is_sug);

  int compound_check_morph(const char * word, int len, short wordnum,
            short numsyllable, short maxwordnum, short wnum, hentry ** words,
            char hu_mov_rule, char ** result, char * partresult);

  struct hentry * lookup(const char * word);
  int                 get_numrep();
  struct replentry *  get_reptable();
  RepList *           get_iconvtable();
  RepList *           get_oconvtable();
  struct phonetable * get_phonetable();
  int                 get_nummap();
  struct mapentry *   get_maptable();
  int                 get_numbreak();
  char **             get_breaktable();
  char *              get_encoding();
  int                 get_langnum();
  char *              get_key_string();
  char *              get_try_string();
  const char *        get_wordchars();
  unsigned short *    get_wordchars_utf16(int * len);
  char *              get_ignore();
  unsigned short *    get_ignore_utf16(int * len);
  int                 get_compound();
  FLAG                get_compoundflag();
  FLAG                get_compoundbegin();
  FLAG                get_forbiddenword();
  FLAG                get_nosuggest();
  FLAG                get_needaffix();
  FLAG                get_onlyincompound();
  FLAG                get_compoundroot();
  FLAG                get_lemma_present();
  int                 get_checknum();
  char *              get_possible_root();
  const char *        get_prefix();
  const char *        get_suffix();
  const char *        get_derived();
  const char *        get_version();
  const int           have_contclass();
  int                 get_utf8();
  int                 get_complexprefixes();
  char *              get_suffixed(char );
  int                 get_maxngramsugs();
  int                 get_nosplitsugs();
  int                 get_sugswithdots(void);
  FLAG                get_keepcase(void);
  int                 get_checksharps(void);
  char *              encode_flag(unsigned short aflag);
  int                 get_fullstrip();

private:
  int  parse_file(const char * affpath, const char * key);
  int  parse_flag(char * line, unsigned short * out, FileMgr * af);
  int  parse_num(char * line, int * out, FileMgr * af);
  int  parse_cpdsyllable(char * line, FileMgr * af);
  int  parse_reptable(char * line, FileMgr * af);
  int  parse_convtable(char * line, FileMgr * af, RepList ** rl, const char * keyword);
  int  parse_phonetable(char * line, FileMgr * af);
  int  parse_maptable(char * line, FileMgr * af);
  int  parse_breaktable(char * line, FileMgr * af);
  int  parse_checkcpdtable(char * line, FileMgr * af);
  int  parse_defcpdtable(char * line, FileMgr * af);
  int  parse_affix(char * line, const char at, FileMgr * af, char * dupflags);

  void reverse_condition(char *);
  void debugflag(char * result, unsigned short flag);
  int condlen(char *);
  int encodeit(struct affentry * ptr, char * cs);
  int build_pfxtree(AffEntry* pfxptr);
  int build_sfxtree(AffEntry* sfxptr);
  int process_pfx_order();
  int process_sfx_order();
  AffEntry * process_pfx_in_order(AffEntry * ptr, AffEntry * nptr);
  AffEntry * process_sfx_in_order(AffEntry * ptr, AffEntry * nptr);
  int process_pfx_tree_to_list();
  int process_sfx_tree_to_list();
  int redundant_condition(char, char * strip, int stripl,
      const char * cond, int);
};

#endif


#ifndef _SUGGESTMGR_HXX_
#define _SUGGESTMGR_HXX_

#define MAXSWL 100
#define MAXSWUTF8L (MAXSWL * 4)
#define MAX_ROOTS 100
#define MAX_WORDS 100
#define MAX_GUESS 200
#define MAXNGRAMSUGS 4
#define MAXPHONSUGS 2

// timelimit: max ~1/4 sec (process time on Linux) for a time consuming function
#define TIMELIMIT (CLOCKS_PER_SEC >> 2)
#define MINTIMER 100
#define MAXPLUSTIMER 100

#define NGRAM_LONGER_WORSE  (1 << 0)
#define NGRAM_ANY_MISMATCH  (1 << 1)
#define NGRAM_LOWERING      (1 << 2)

#include <time.h>

enum { LCS_UP, LCS_LEFT, LCS_UPLEFT };

class SuggestMgr
{
  char *          ckey;
  int             ckeyl;
  w_char *        ckey_utf;

  char *          ctry;
  int             ctryl;
  w_char *        ctry_utf;

  AffixMgr*       pAMgr;
  int             maxSug;
  struct cs_info * csconv;
  int             utf8;
  int             langnum;
  int             nosplitsugs;
  int             maxngramsugs;
  int             complexprefixes;


public:
  SuggestMgr(const char * tryme, int maxn, AffixMgr *aptr);
  ~SuggestMgr();

  int suggest(char*** slst, const char * word, int nsug, int * onlycmpdsug);
  int ngsuggest(char ** wlst, char * word, int ns, HashMgr** pHMgr, int md);
  int suggest_auto(char*** slst, const char * word, int nsug);
  int suggest_stems(char*** slst, const char * word, int nsug);
  int suggest_pos_stems(char*** slst, const char * word, int nsug);

  char * suggest_morph(const char * word);
  char * suggest_gen(char ** pl, int pln, char * pattern);
  char * suggest_morph_for_spelling_error(const char * word);

private:
   int testsug(char** wlst, const char * candidate, int wl, int ns, int cpdsuggest,
     int * timer, clock_t * timelimit);
   int checkword(const char *, int, int, int *, clock_t *);
   int check_forbidden(const char *, int);

   int capchars(char **, const char *, int, int);
   int replchars(char**, const char *, int, int);
   int doubletwochars(char**, const char *, int, int);
   int forgotchar(char **, const char *, int, int);
   int swapchar(char **, const char *, int, int);
   int longswapchar(char **, const char *, int, int);
   int movechar(char **, const char *, int, int);
   int extrachar(char **, const char *, int, int);
   int badcharkey(char **, const char *, int, int);
   int badchar(char **, const char *, int, int);
   int twowords(char **, const char *, int, int);
   int fixstems(char **, const char *, int);

   int capchars_utf(char **, const w_char *, int wl, int, int);
   int doubletwochars_utf(char**, const w_char *, int wl, int, int);
   int forgotchar_utf(char**, const w_char *, int wl, int, int);
   int extrachar_utf(char**, const w_char *, int wl, int, int);
   int badcharkey_utf(char **, const w_char *, int wl, int, int);
   int badchar_utf(char **, const w_char *, int wl, int, int);
   int swapchar_utf(char **, const w_char *, int wl, int, int);
   int longswapchar_utf(char **, const w_char *, int, int, int);
   int movechar_utf(char **, const w_char *, int, int, int);

   int mapchars(char**, const char *, int, int);
   int map_related(const char *, int, char ** wlst, int, int, const mapentry*, int, int *, clock_t *);
   int map_related_utf(w_char *, int, int, int, char ** wlst, int, const mapentry*, int, int *, clock_t *);
   int ngram(int n, char * s1, const char * s2, int opt);
   int mystrlen(const char * word);
   int leftcommonsubstring(char * s1, const char * s2);
   int commoncharacterpositions(char * s1, const char * s2, int * is_swap);
   void bubblesort( char ** rwd, char ** rwd2, int * rsc, int n);
   void lcs(const char * s, const char * s2, int * l1, int * l2, char ** result);
   int lcslen(const char * s, const char* s2);
   char * suggest_hentry_gen(hentry * rv, char * pattern);

};

#endif


#ifndef _LANGNUM_HXX_
#define _LANGNUM_HXX_

/*
 language numbers for language specific codes
 see http://l10n.openoffice.org/languages.html
*/

enum {
LANG_ar=96,
LANG_az=100, // custom number
LANG_bg=41,
LANG_ca=37,
LANG_cs=42,
LANG_da=45,
LANG_de=49,
LANG_el=30,
LANG_en=01,
LANG_es=34,
LANG_eu=10,
LANG_fr=02,
LANG_gl=38,
LANG_hr=78,
LANG_hu=36,
LANG_it=39,
LANG_la=99, // custom number
LANG_lv=101, // custom number
LANG_nl=31,
LANG_pl=48,
LANG_pt=03,
LANG_ru=07,
LANG_sv=50,
LANG_tr=90,
LANG_uk=80,
LANG_xx=999
};

#endif


#define  SPELL_COMPOUND  (1 << 0)
#define  SPELL_FORBIDDEN (1 << 1)
#define  SPELL_ALLCAP    (1 << 2)
#define  SPELL_NOCAP     (1 << 3)
#define  SPELL_INITCAP   (1 << 4)

#define  SPELL_XML "<?xml?>"

#define MAXDIC 20
#define MAXSUGGESTION 15
#define MAXSHARPS 5

#ifndef _MYSPELLMGR_HXX_
#define _MYSPELLMGR_HXX_

#ifdef HUNSPELL_STATIC
	#define DLLEXPORT
#else
	#ifdef HUNSPELL_EXPORTS
		#define DLLEXPORT  __declspec( dllexport )
	#else
		#define DLLEXPORT  __declspec( dllimport )
	#endif
#endif

#ifdef WIN32
class DLLEXPORT Hunspell
#else
class Hunspell
#endif
{
  AffixMgr*       pAMgr;
  HashMgr*        pHMgr[MAXDIC];
  int             maxdic;
  SuggestMgr*     pSMgr;
  char *          affixpath;
  char *          encoding;
  struct cs_info * csconv;
  int             langnum;
  int             utf8;
  int             complexprefixes;
  char**          wordbreak;

public:

  /* Hunspell(aff, dic) - constructor of Hunspell class
   * input: path of affix file and dictionary file
   */

  Hunspell(const char * affpath, const char * dpath, const char * key = NULL);
  ~Hunspell();

  /* load extra dictionaries (only dic files) */
  int add_dic(const char * dpath, const char * key = NULL);

  /* spell(word) - spellcheck word
   * output: 0 = bad word, not 0 = good word
   *   
   * plus output:
   *   info: information bit array, fields:
   *     SPELL_COMPOUND  = a compound word 
   *     SPELL_FORBIDDEN = an explicit forbidden word
   *   root: root (stem), when input is a word with affix(es)
   */
   
  int spell(const char * word, int * info = NULL, char ** root = NULL);

  /* suggest(suggestions, word) - search suggestions
   * input: pointer to an array of strings pointer and the (bad) word
   *   array of strings pointer (here *slst) may not be initialized
   * output: number of suggestions in string array, and suggestions in
   *   a newly allocated array of strings (*slts will be NULL when number
   *   of suggestion equals 0.)
   */

  int suggest(char*** slst, const char * word);

  /* deallocate suggestion lists */

  void free_list(char *** slst, int n);

  char * get_dic_encoding();

 /* morphological functions */

 /* analyze(result, word) - morphological analysis of the word */
 
  int analyze(char*** slst, const char * word);

 /* stem(result, word) - stemmer function */
  
  int stem(char*** slst, const char * word);
  
 /* stem(result, analysis, n) - get stems from a morph. analysis
  * example:
  * char ** result, result2;
  * int n1 = analyze(&result, "words");
  * int n2 = stem(&result2, result, n1);   
  */
 
  int stem(char*** slst, char ** morph, int n);

 /* generate(result, word, word2) - morphological generation by example(s) */

  int generate(char*** slst, const char * word, const char * word2);

 /* generate(result, word, desc, n) - generation by morph. description(s)
  * example:
  * char ** result;
  * char * affix = "is:plural"; // description depends from dictionaries, too
  * int n = generate(&result, "word", &affix, 1);
  * for (int i = 0; i < n; i++) printf("%s\n", result[i]);
  */

  int generate(char*** slst, const char * word, char ** desc, int n);

  /* functions for run-time modification of the dictionary */

  /* add word to the run-time dictionary */
  
  int add(const char * word);

  /* add word to the run-time dictionary with affix flags of
   * the example (a dictionary word): Hunspell will recognize
   * affixed forms of the new word, too.
   */
  
  int add_with_affix(const char * word, const char * example);

  /* remove word from the run-time dictionary */

  int remove(const char * word);

  /* other */

  /* get extra word characters definied in affix file for tokenization */
  const char * get_wordchars();
  unsigned short * get_wordchars_utf16(int * len);

  struct cs_info * get_csconv();
  const char * get_version();
  
  /* experimental and deprecated functions */

#ifdef HUNSPELL_EXPERIMENTAL
  /* suffix is an affix flag string, similarly in dictionary files */  
  int put_word_suffix(const char * word, const char * suffix);
  char * morph_with_correction(const char * word);

  /* spec. suggestions */
  int suggest_auto(char*** slst, const char * word);
  int suggest_pos_stems(char*** slst, const char * word);
  char * get_possible_root();
#endif

private:
   int    cleanword(char *, const char *, int * pcaptype, int * pabbrev);
   int    cleanword2(char *, const char *, w_char *, int * w_len, int * pcaptype, int * pabbrev);
   void   mkinitcap(char *);
   int    mkinitcap2(char * p, w_char * u, int nc);
   int    mkinitsmall2(char * p, w_char * u, int nc);
   void   mkallcap(char *);
   int    mkallcap2(char * p, w_char * u, int nc);
   void   mkallsmall(char *);
   int    mkallsmall2(char * p, w_char * u, int nc);
   struct hentry * checkword(const char *, int * info, char **root);
   char * sharps_u8_l1(char * dest, char * source);
   hentry * spellsharps(char * base, char *, int, int, char * tmp, int * info, char **root);
   int    is_keepcase(const hentry * rv);
   int    insert_sug(char ***slst, char * word, int ns);
   void   cat_result(char * result, char * st);
   char * stem_description(const char * desc);
   int    spellml(char*** slst, const char * word);
   int    get_xml_par(char * dest, const char * par, int maxl);
   const char * get_xml_pos(const char * s, const char * attr);
   int    get_xml_list(char ***slst, char * list, const char * tag);
   int    check_xml_par(const char * q, const char * attr, const char * value);

};


#endif

