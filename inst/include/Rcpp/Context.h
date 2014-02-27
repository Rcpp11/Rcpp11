#ifndef RCPP_CONTEXT_H
#define RCPP_CONTEXT_H

namespace Rcpp {
 
    // borrowed from rJava
    inline SEXP get_current_call() {
        RCNTXT *ctx = R_GlobalContext;
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
            
            RCNTXT* ctx    = R_GlobalContext ;
            ctx->callflag  = CTXT_FUNCTION ;
            
            // first call to .addCondHands to add a handler
            SEXP args = pairlist( 
                Rf_mkString("error"),
                Rf_allocVector(VECSXP,1), 
                ctx->cloenv, 
                ctx->cloenv, 
                Rf_ScalarLogical(FALSE)
            ) ;
            
            SEXP symb = Rf_install(".addCondHands") ;
            SEXP ifun = INTERNAL( symb ) ;
            PRIMFUN(ifun)(symb, ifun, args, R_GlobalEnv );
               
            // call it a second time to get the current R_HandlerStack
            CAR(args) = R_NilValue ;
            SEXP value = PRIMFUN(ifun)(symb, ifun, args, R_GlobalEnv ) ;
            pair->second = VECTOR_ELT(CAR(value),4) ;
            
            Fun& fun = *reinterpret_cast<Fun*>(pair->first) ;
            fun() ;
            
        } ;
      
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
              throw eval_error( R_curErrorBuf() ) ;    
          } else {
              SEXP msg = PROTECT( Rf_eval( Rf_lang2( Rf_install( "conditionMessage"),  condition ), R_GlobalEnv ) ) ; 
              eval_error ex( CHAR(STRING_ELT(msg, 0)) ) ;
              UNPROTECT(1) ;
              throw ex ;
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
