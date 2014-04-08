#ifndef Rcpp__R__h
#define Rcpp__R__h

// include R headers, but set R_NO_REMAP and access everything via Rf_ prefixes
#define R_NO_REMAP
#define USE_RINTERNALS

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Complex.h>
#include <R_ext/Parse.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Callbacks.h>
#include <Rversion.h>

typedef SEXP (*CCODE)(SEXP, SEXP, SEXP, SEXP);
 
/* Information for Deparsing Expressions */
typedef enum {
    PP_INVALID  =  0,
    PP_ASSIGN   =  1,
    PP_ASSIGN2  =  2,
    PP_BINARY   =  3,
    PP_BINARY2  =  4,
    PP_BREAK    =  5,
    PP_CURLY    =  6,
    PP_FOR      =  7,
    PP_FUNCALL  =  8,
    PP_FUNCTION =  9,
    PP_IF     = 10,
    PP_NEXT     = 11,
    PP_PAREN    = 12,
    PP_RETURN   = 13,
    PP_SUBASS   = 14,
    PP_SUBSET   = 15,
    PP_WHILE     = 16,
    PP_UNARY     = 17,
    PP_DOLLAR     = 18,
    PP_FOREIGN     = 19,
    PP_REPEAT     = 20
} PPkind;
 
typedef enum {
    PREC_FN     = 0,
    PREC_LEFT    = 1,
    PREC_EQ     = 2,
    PREC_RIGHT     = 3,
    PREC_TILDE     = 4,
    PREC_OR     = 5,
    PREC_AND     = 6,
    PREC_NOT     = 7,
    PREC_COMPARE = 8,
    PREC_SUM     = 9,
    PREC_PROD     = 10,
    PREC_PERCENT = 11,
    PREC_COLON     = 12,
    PREC_SIGN     = 13,
    PREC_POWER     = 14,
    PREC_DOLLAR  = 15,
    PREC_NS     = 16,
    PREC_SUBSET     = 17
} PPprec;
 
typedef struct {
    PPkind kind;      /* deparse kind */
    PPprec precedence; /* operator precedence */
    unsigned int rightassoc;  /* right associative? */
} PPinfo;
 
typedef struct {
    char   *name;    /* print name */
    CCODE  cfun;     /* c-code address */
    int       code;     /* offset within c-code */
    int       eval;     /* evaluate args? */
    int       arity;    /* function arity */
    PPinfo gram;     /* pretty-print info */
} FUNTAB;
 
extern FUNTAB    R_FunTab[];        /* Built in functions */ 

#undef isNull
#define RCPP_isNull(s)    (TYPEOF(s) == NILSXP)
inline bool Rf_isNull(SEXP s){ return RCPP_isNull(s); }

#undef isSymbol
#define RCPP_isSymbol(s)    (TYPEOF(s) == SYMSXP)
inline bool Rf_isSymbol(SEXP s){ return RCPP_isSymbol(s);}

#undef isLogical
#define RCPP_isLogical(s)    (TYPEOF(s) == LGLSXP)
inline bool Rf_isLogical(SEXP s){ return RCPP_isLogical(s); }

#undef isReal
#define RCPP_isReal(s)    (TYPEOF(s) == REALSXP)
inline bool Rf_isReal(SEXP s){ return RCPP_isReal(s); }

#undef isComplex
#define RCPP_isComplex(s)    (TYPEOF(s) == CPLXSXP)
inline bool Rf_isComplex(SEXP s){ return RCPP_isComplex(s); }

#undef isExpression
#define RCPP_isExpression(s) (TYPEOF(s) == EXPRSXP)
inline bool Rf_isExpression(SEXP s){ return RCPP_isExpression(s); }

#undef isEnvironment
#define RCPP_isEnvironment(s) (TYPEOF(s) == ENVSXP)
inline bool Rf_isEnvironment(SEXP s){ return RCPP_isEnvironment(s); }

#undef isString
#define RCPP_isString(s)    (TYPEOF(s) == STRSXP)
inline bool Rf_isString(SEXP s){ return RCPP_isString(s); }

#undef isObject
#define RCPP_isObject(s)    (OBJECT(s) != 0)
inline bool Rf_isObject(SEXP s){ return RCPP_isObject(s); }

#define RCPP_DATAPTR(x)    (((SEXPREC_ALIGN *) (x)) + 1)
#undef DATAPTR
inline void* DATAPTR(SEXP x){ return RCPP_DATAPTR(x); }

#define RCPP_SETLEVELS(x,v)    (((x)->sxpinfo.gp)=((unsigned short)v))
#undef SETLEVELS
inline int SETLEVELS(SEXP x, int v){ return RCPP_SETLEVELS(x,v); }

#undef PRINTNAME 
#define RCPP_PRINTNAME(x)    ((x)->u.symsxp.pname)
inline SEXP PRINTNAME(SEXP x){ return RCPP_PRINTNAME(x) ; }

// #define JMP_BUF jmp_buf
#define JMP_BUF sigjmp_buf

enum {
    CTXT_TOPLEVEL = 0,
    CTXT_NEXT        = 1,
    CTXT_BREAK      = 2,
    CTXT_LOOP        = 3,    /* break OR next target */
    CTXT_FUNCTION = 4,
    CTXT_CCODE      = 8,
    CTXT_RETURN      = 12,
    CTXT_BROWSER  = 16,
    CTXT_GENERIC  = 20,
    CTXT_RESTART  = 32,
    CTXT_BUILTIN  = 64  /* used in profiling */
};
                 
#ifdef BC_INT_STACK
typedef union { void *p; int i; } IStackval;
#endif

typedef struct RPRSTACK {
    SEXP promise;
    struct RPRSTACK *next;
} RPRSTACK;

typedef struct RCNTXT {
    struct RCNTXT *nextcontext;    /* The next context up the chain */
    int callflag;                    /* The context "type" */
    JMP_BUF cjmpbuf;                /* C stack and register information */
    int cstacktop;                  /* Top of the pointer protection stack */
    int evaldepth;                /* evaluation depth at inception */
    SEXP promargs;                /* Promises supplied to closure */
    SEXP callfun;                    /* The closure called */
    SEXP sysparent;                /* environment the closure was called from */
    SEXP call;                        /* The call that effected this context*/
    SEXP cloenv;                    /* The environment */
    SEXP conexit;                    /* Interpreted "on.exit" code */
    void (*cend)(void *);          /* C "on.exit" thunk */
    void *cenddata;                  /* data for C "on.exit" thunk */
    void *vmax;                      /* top of R_alloc stack */
    int intsusp;                /* interrupts are suspended */
    SEXP handlerstack;          /* condition handler stack */
    SEXP restartstack;          /* stack of available restarts */
    
    struct RPRSTACK *prstack;   /* stack of pending promises */
    SEXP *nodestack;
    #ifdef BC_INT_STACK
        IStackval *intstack;
    #endif
    SEXP srcref;                  /* The source line in effect */
    int browserfinish;          /* should browser finish this context without stopping */
} RCNTXT ;

extern RCNTXT* R_GlobalContext;  
    
#define PRIMOFFSET(x)    ((x)->u.primsxp.offset)
#define PRIMFUN(x)    (R_FunTab[PRIMOFFSET(x)].cfun)

extern SEXP R_TrueValue ;
extern SEXP R_FalseValue ;
extern SEXP R_LogicalNAValue ;

#endif
