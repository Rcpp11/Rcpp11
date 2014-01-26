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
    
  private:
    Context( RCNTXT* ctx_) : ctx(ctx_){}
    
    RCNTXT* ctx ;  
  } ;
  
}

#endif
