#include <Rcpp.h>

using namespace Rcpp ;

#define DOT_CALL(name) DotCall(#name, &name)

extern "C" SEXP rcpp_error_recorder(SEXP e){
    rcpp_current_error() = e ;
    return R_NilValue ;
}
            
static R_CallMethodDef callEntries[]  = {
    DOT_CALL(rcpp_error_recorder),
                     
    {NULL, NULL, 0}
}; 

static Rstreambuf<true>*  Rcout_buf = nullptr ;
static Rstreambuf<false>* Rcerr_buf = nullptr ;
static std::streambuf* cout_buf = nullptr ;
static std::streambuf* cerr_buf = nullptr ;

extern "C" void R_init_Rcpp11( DllInfo* info){
  R_registerRoutines(info, 
      NULL /* .C*/, 
      callEntries /*.Call*/,
      NULL /* .Fortran */,
      NULL /*.External*/
  );
    
  SEXP getNamespaceSym = Rf_install("getNamespace"); 
  SEXP RCPP    = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
  SEXP cache   = PROTECT( Rf_allocVector( VECSXP, 7 ) ) ;
  
  // the Rcpp11 namespace
  RCPP_SET_VECTOR_ELT( cache, 0, RCPP ) ;
  RCPP_SET_VECTOR_ELT( cache, 2, R_NilValue) ;
  RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ; // stack trace
  Rf_defineVar( Rf_install(".rcpp_cache"), cache, RCPP );
  
  UNPROTECT(2) ;
    
	// init routines
	Rostream<true>  Rcout;
  Rostream<false> Rcerr;
  Rcout_buf = new Rstreambuf<true> ;
  Rcerr_buf = new Rstreambuf<false> ;     
  cout_buf  = std::cout.rdbuf() ;           
  cerr_buf  = std::cerr.rdbuf() ;           
  
  std::cout.rdbuf( Rcout_buf );
  std::cerr.rdbuf( Rcerr_buf );
  
  #define REGISTER(__FUN__) R_RegisterCCallable( "Rcpp11", #__FUN__ , (DL_FUNC)__FUN__ );
  
  REGISTER(Rcpp_eval)
  REGISTER(forward_exception_to_r)
  REGISTER(exception_to_try_error)
  REGISTER(string_to_try_error)
  REGISTER(stack_trace)
  
  REGISTER(enterRNGScope)
  REGISTER(exitRNGScope)
  REGISTER(get_rcpp_cache)
}

extern "C" void R_unload_Rcpp11(DllInfo *info) {
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );
    delete Rcout_buf ; Rcout_buf = nullptr ;
    delete Rcerr_buf ; Rcerr_buf = nullptr ;
}

