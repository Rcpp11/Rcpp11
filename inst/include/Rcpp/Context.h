#ifndef RCPP_CONTEXT_H
#define RCPP_CONTEXT_H

namespace Rcpp {
 
  class Context {
  public:
    
    inline int& type(){
      return ctx->callflag ;  
    }
    
    inline int evaldepth() const {
      return ctx->evaldepth ;
    }
    
    inline SEXP& cloenv(){
      return ctx->cloenv ;  
    }
    
    inline SEXP handler_stack() const {
      return ctx->handlerstack ;  
    }
    
    inline SEXP restart_stack() const {
      return ctx->restartstack ;  
    }
    
    static Context global() {
      return Context(R_GlobalContext) ;     
    }
    
    static Context toplevel(){
      return Context(R_ToplevelContext) ; 
    }
    
    Context( RCNTXT* ctx_) : ctx(ctx_){}
    
    void debug(){
      Rprintf( "ctx = callflag = %d, cstacktop = %d, depth = %d\n", 
        ctx->callflag, ctx->cstacktop, ctx->evaldepth
        ) ; 
      Rprintf( "cloenv  : <%p> \n", ctx->cloenv ) ;
      if( ctx->cloenv) Rf_PrintValue(ctx->cloenv) ;
      
      Rprintf( "callfun  : <%p> \n", ctx->callfun ) ;
      if( ctx->callfun) Rf_PrintValue(ctx->callfun) ;
      
      Rprintf( "sysparent  : <%p> \n", ctx->sysparent ) ;
      if( ctx->sysparent) Rf_PrintValue(ctx->sysparent) ;
      
      Rprintf( "call  : <%p> \n", ctx->call ) ;
      if( ctx->call) Rf_PrintValue(ctx->call) ;
      
    }
    
    RCNTXT* ctx ;  
  } ;
  
  class ConditionHandler {
  public:
    ConditionHandler( const char* klass, SEXP handler, SEXP env) : entry(5){
      entry[0] = Rf_mkChar(klass) ;
      entry[1] = CLOENV(handler) ;
      entry[2] = handler ;
      entry[3] = env ;
      entry[4] = List::create(R_NilValue, R_NilValue, R_NilValue) ;
      SETLEVELS(entry, TRUE);
    }
    
    inline operator SEXP() const {
      return entry ;  
    }
    
  private:
    List entry ;
  } ;
  
  namespace internal{
    inline void install_Rcpp11_error_handler(){
      SEXP Rcpp11    = get_Rcpp11_namespace() ;
      Context ctx    = Context::global() ;
      ctx.cloenv()   = Rcpp11 ;
      ctx.type()     = CTXT_FUNCTION ;
      SEXP handler   = rcpp11_error_handler() ;
      R_HandlerStack = pairlist( 
        ConditionHandler("error", handler , Rcpp11) 
      ) ;
    }
    
    template <typename Fun>
    void try_catch_helper( void* data ){
        install_Rcpp11_error_handler() ;
        Fun& fun = *reinterpret_cast<Fun*>(data) ;
        fun() ;
    } ;
    
  }  
  
  template <typename Fun>
  void try_catch( Fun fun ) {
      int oldshow = R_ShowErrorMessages;
      R_ShowErrorMessages = FALSE;
      reset_current_error(); 
      
      bool ok = R_ToplevelExec( &internal::try_catch_helper<Fun>, &fun ) ;
      
      if( !ok ){
        SEXP msg = PROTECT( Rf_eval( Rf_lang2( Rf_install( "conditionMessage"),  rcpp_current_error() ), R_GlobalEnv ) ) ; 
        eval_error ex( CHAR(STRING_ELT(msg, 0)) ) ;
        UNPROTECT(1) ;
        throw ex ;
      } 
      
  }

  
}

#endif
