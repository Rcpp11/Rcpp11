#include <Rcpp.h>
#include "internal.h"

using namespace Rcpp ;

#define DOT_EXT(name)  DotExternal(#name, &name)
#define DOT_CALL(name) DotCall(#name, &name)

static R_CallMethodDef callEntries[]  = {
    DOT_CALL(Class__name),
    DOT_CALL(Class__has_default_constructor),
    DOT_CALL(CppClass__complete),
    DOT_CALL(CppClass__methods),
    DOT_CALL(CppObject__finalize),
    DOT_CALL(Module__classes_info),
    DOT_CALL(Module__complete),
    DOT_CALL(Module__get_class),
    DOT_CALL(Module__has_class),
    DOT_CALL(Module__has_function),
    DOT_CALL(Module__functions_arity),
    DOT_CALL(Module__functions_names),
    DOT_CALL(Module__name),
    DOT_CALL(Module__get_function),
    
    DOT_CALL(rcpp_error_recorder),
    
    DOT_CALL(as_character_externalptr),
    DOT_CALL(CppField__get),
    DOT_CALL(CppField__set),
    
    {NULL, NULL, 0}
}; 

static R_ExternalMethodDef extEntries[]  = {
    DOT_EXT(CppMethod__invoke),
    DOT_EXT(CppMethod__invoke_void),
    DOT_EXT(CppMethod__invoke_notvoid),
    DOT_EXT(InternalFunction_invoke),
    DOT_EXT(Module__invoke), 
    DOT_EXT(class__newInstance), 
    DOT_EXT(class__dummyInstance), 
    
    {NULL, NULL, 0}
} ;

static Rstreambuf<true>*  Rcout_buf = nullptr ;
static Rstreambuf<false>* Rcerr_buf = nullptr ;
static std::streambuf* cout_buf = nullptr ;
static std::streambuf* cerr_buf = nullptr ;

// this is called by R_init_Rcpp11 that is in Module.cpp
void init_Rcpp11_routines(DllInfo *info){
    Rostream<true>  Rcout;
    Rostream<false> Rcerr;
    Rcout_buf = new Rstreambuf<true> ;
    Rcerr_buf = new Rstreambuf<false> ;     
    cout_buf  = std::cout.rdbuf() ;           
    cerr_buf  = std::cerr.rdbuf() ;           
    
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );

    R_registerRoutines(info, 
        NULL /* .C*/, 
        callEntries /*.Call*/,
        NULL /* .Fortran */,
        extEntries /*.External*/
    );
    
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
