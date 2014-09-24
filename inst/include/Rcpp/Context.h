#ifndef RCPP_CONTEXT_H
#define RCPP_CONTEXT_H

#if defined(_WIN32)

namespace Rcpp {

    inline SEXP Rcpp_eval(SEXP expr, SEXP env ){
        // version not using contexts for windows until we figure out how to
        Shield<SEXP> x = Rf_lang3( Rf_install("try"), expr, Rf_ScalarLogical(TRUE) );
        SET_TAG( CDDR(x), Rf_install("silent") );
        Shield<SEXP> res = Rf_eval( x, env) ;
        if( inherits( res, "try-error" ) ){
            stop( CHAR(STRING_ELT(res, 0)) ) ;
        }
        return res ;
    }
    inline SEXP get_current_call() { return R_NilValue; }
}
    #else

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

extern void* R_GlobalContext;

    namespace Rcpp{

    // borrowed from rJava
    inline SEXP get_current_call() {
      RCNTXT* ctx = *(RCNTXT**) libR["R_GlobalContext"];
        /* skip the .External/.Call context to get at the underlying call */
        if (ctx->nextcontext && (ctx->callflag & CTXT_BUILTIN))
            ctx = ctx->nextcontext;
        return ctx->call;
    }

    namespace internal{

        template <typename Fun>
        void try_catch_helper( void* data ){
            typedef std::pair<Fun*, SEXP&> Pair ;
            Pair* pair = reinterpret_cast<Pair*>(data) ;

            RCNTXT* ctx    = *(RCNTXT**) libR["R_GlobalContext"];
            ctx->callflag  = CTXT_FUNCTION ;

            // first call to .addCondHands to add a handler
            SEXP args = pairlist(
                Rf_mkString("error"),
                Rf_allocVector(VECSXP,1),
                ctx->cloenv,
                ctx->cloenv,
                R_FalseValue
            ) ;

            SEXP symb = Rf_install(".addCondHands") ;
            SEXP ifun = INTERNAL( symb ) ;
            PRIMFUN(ifun)(symb, ifun, args, R_GlobalEnv );

            // call it a second time to get the current R_HandlerStack
            CAR(args) = R_NilValue ;
            SEXP value = PRIMFUN(ifun)(symb, ifun, args, R_GlobalEnv ) ;
            pair->second = VECTOR_ELT(CAR(value),4) ;

            Fun& fun = *pair->first ;
            fun() ;

        }

    }

    template <typename Fun>
    void try_catch( Fun fun ) {
        typedef std::pair<Fun*, SEXP&> Pair ;

        SEXP return_value ;

        Pair pair = std::make_pair(&fun, std::ref(return_value)) ;

        bool ok = R_ToplevelExec( &internal::try_catch_helper<Fun>, &pair ) ;

        if( !ok ){

          SEXP condition = VECTOR_ELT(return_value,0) ;

          if( Rf_isNull(condition) ){
              stop("eval error : %s", R_curErrorBuf()) ;
          } else {
              Shield<SEXP> msg = Rf_eval( Rf_lang2( Rf_install( "conditionMessage"),  condition ), R_GlobalEnv ) ;
              stop("eval error : %s", CHAR(STRING_ELT(msg, 0)) ) ;
          }
        }
    }

    inline SEXP Rcpp_eval(SEXP expr, SEXP env ){
        SEXP res ;
        try_catch( [&](){
            res = Rf_eval(expr, env) ;
        }) ;
        return res ;
    }


}

#endif

#endif
