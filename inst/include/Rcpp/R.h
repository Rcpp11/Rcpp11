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

#undef isNull
#define RCPP_isNull(s)	(TYPEOF(s) == NILSXP)
inline bool Rf_isNull(SEXP s){ return RCPP_isNull(s); }

#undef isSymbol
#define RCPP_isSymbol(s)	(TYPEOF(s) == SYMSXP)
inline bool Rf_isSymbol(SEXP s){ return RCPP_isSymbol(s);}

#undef isLogical
#define RCPP_isLogical(s)	(TYPEOF(s) == LGLSXP)
inline bool Rf_isLogical(SEXP s){ return RCPP_isLogical(s); }

#undef isReal
#define RCPP_isReal(s)	(TYPEOF(s) == REALSXP)
inline bool Rf_isReal(SEXP s){ return RCPP_isReal(s); }

#undef isComplex
#define RCPP_isComplex(s)	(TYPEOF(s) == CPLXSXP)
inline bool Rf_isComplex(SEXP s){ return RCPP_isComplex(s); }

#undef isExpression
#define RCPP_isExpression(s) (TYPEOF(s) == EXPRSXP)
inline bool Rf_isExpression(SEXP s){ return RCPP_isExpression(s); }

#undef isEnvironment
#define RCPP_isEnvironment(s) (TYPEOF(s) == ENVSXP)
inline bool Rf_isEnvironment(SEXP s){ return RCPP_isEnvironment(s); }

#undef isString
#define RCPP_isString(s)	(TYPEOF(s) == STRSXP)
inline bool Rf_isString(SEXP s){ return RCPP_isString(s); }

#undef isObject
#define RCPP_isObject(s)	(OBJECT(s) != 0)
inline bool Rf_isObject(SEXP s){ return RCPP_isObject(s); }

#define RCPP_DATAPTR(x)	(((SEXPREC_ALIGN *) (x)) + 1)
#undef DATAPTR
inline void* DATAPTR(SEXP x){ return RCPP_DATAPTR(x); }

#define RCPP_SETLEVELS(x,v)	(((x)->sxpinfo.gp)=((unsigned short)v))
#undef SETLEVELS
inline int SETLEVELS(SEXP x, int v){ return RCPP_SETLEVELS(x,v); }

#undef PRINTNAME 
#define RCPP_PRINTNAME(x)	((x)->u.symsxp.pname)
inline SEXP PRINTNAME(SEXP x){ return RCPP_PRINTNAME(x) ; }

#define JMP_BUF jmp_buf

enum {
    CTXT_TOPLEVEL = 0,
    CTXT_NEXT	    = 1,
    CTXT_BREAK	  = 2,
    CTXT_LOOP	    = 3,	/* break OR next target */
    CTXT_FUNCTION = 4,
    CTXT_CCODE	  = 8,
    CTXT_RETURN	  = 12,
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
    struct RCNTXT *nextcontext;	/* The next context up the chain */
    int callflag;		            /* The context "type" */
    JMP_BUF cjmpbuf;		        /* C stack and register information */
    int cstacktop;		          /* Top of the pointer protection stack */
    int evaldepth;	            /* evaluation depth at inception */
    SEXP promargs;	            /* Promises supplied to closure */
    SEXP callfun;		            /* The closure called */
    SEXP sysparent;	            /* environment the closure was called from */
    SEXP call;			            /* The call that effected this context*/
    SEXP cloenv;		            /* The environment */
    SEXP conexit;		            /* Interpreted "on.exit" code */
    void (*cend)(void *);	      /* C "on.exit" thunk */
    void *cenddata;		          /* data for C "on.exit" thunk */
    void *vmax;		              /* top of R_alloc stack */
    int intsusp;                /* interrupts are suspended */
    SEXP handlerstack;          /* condition handler stack */
    SEXP restartstack;          /* stack of available restarts */
    
    struct RPRSTACK *prstack;   /* stack of pending promises */
    SEXP *nodestack;
    #ifdef BC_INT_STACK
        IStackval *intstack;
    #endif
    SEXP srcref;	              /* The source line in effect */
    int browserfinish;          /* should browser finish this context without stopping */
} RCNTXT ;

extern SEXP R_HandlerStack ;
extern SEXP R_RestartStack ;
extern RCNTXT* R_ToplevelContext ;
extern RCNTXT* R_GlobalContext;  
extern int R_ShowErrorMessages ;

#endif
