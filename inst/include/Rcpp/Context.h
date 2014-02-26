#ifndef RCPP_CONTEXT_H
#define RCPP_CONTEXT_H

namespace Rcpp {
 
    namespace internal{
      
        template <typename Fun>
        void try_catch_helper( void* data ){
            RCNTXT* ctx    = R_GlobalContext ;
            ctx->callflag  = CTXT_FUNCTION ;
            
            SEXP entry     = PROTECT(Rf_allocVector(VECSXP, 5)) ;
            SET_VECTOR_ELT(entry, 0, Rf_mkChar("error") );
            SET_VECTOR_ELT(entry, 3, ctx->cloenv );
            SET_VECTOR_ELT(entry, 4, Rf_allocVector(VECSXP,3) );
            SETLEVELS(entry, FALSE);
            
            R_HandlerStack = Rf_cons(entry, R_NilValue) ;
            UNPROTECT(1) ;  
            Fun& fun = *reinterpret_cast<Fun*>(data) ;
            fun() ;
        } ;
      
    }  
    
    template <typename Fun>
    void try_catch( Fun fun ) {
        int oldshow = R_ShowErrorMessages;
        R_ShowErrorMessages = FALSE;
        
        bool ok = R_ToplevelExec( &internal::try_catch_helper<Fun>, &fun ) ;
        R_ShowErrorMessages = oldshow ;
        
        if( !ok ){
          SEXP condition = VECTOR_ELT(R_ReturnedValue,0) ; 
          if( Rf_isNull(condition) ){
              throw eval_error( "error (unknown message)" ) ;    
          } else {
              SEXP msg = PROTECT( Rf_eval( Rf_lang2( Rf_install( "conditionMessage"),  rcpp_current_error() ), R_GlobalEnv ) ) ; 
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
