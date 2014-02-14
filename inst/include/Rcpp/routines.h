#ifndef RCPP_ROUTINE_H
#define RCPP_ROUTINE_H

namespace Rcpp{ 
  
    inline const char * type2name(SEXP x) {
        switch (TYPEOF(x)) {
        case NILSXP:	return "NILSXP";
        case SYMSXP:	return "SYMSXP";
        case RAWSXP:	return "RAWSXP";
        case LISTSXP:	return "LISTSXP";
        case CLOSXP:	return "CLOSXP";
        case ENVSXP:	return "ENVSXP";
        case PROMSXP:	return "PROMSXP";
        case LANGSXP:	return "LANGSXP";
        case SPECIALSXP:	return "SPECIALSXP";
        case BUILTINSXP:	return "BUILTINSXP";
        case CHARSXP:	return "CHARSXP";
        case LGLSXP:	return "LGLSXP";
        case INTSXP:	return "INTSXP";
        case REALSXP:	return "REALSXP";
        case CPLXSXP:	return "CPLXSXP";
        case STRSXP:	return "STRSXP";
        case DOTSXP:	return "DOTSXP";
        case ANYSXP:	return "ANYSXP";
        case VECSXP:	return "VECSXP";
        case EXPRSXP:	return "EXPRSXP";
        case BCODESXP:	return "BCODESXP";
        case EXTPTRSXP:	return "EXTPTRSXP";
        case WEAKREFSXP:	return "WEAKREFSXP";
        case S4SXP:		return "S4SXP";
        default:    return "<unknown>";
        }
    }
}

#if defined(COMPILING_RCPP11)

// the idea is that this file should be generated automatically
// by Rcpp::register

namespace Rcpp{
    SEXP Rcpp_eval(SEXP expr, SEXP env = R_GlobalEnv) ;
    std::string demangle( const std::string& name) ;
    void forward_exception_to_r( const std::exception& ex ) ;
    SEXP exception_to_try_error( const std::exception& ex ) ;
    SEXP string_to_try_error( const std::string& str) ;
    SEXP stack_trace( const char *file, int line) ;
    unsigned long enterRNGScope(); 
    unsigned long exitRNGScope() ;
}
           
SEXP rcpp_set_stack_trace(SEXP) ;
SEXP rcpp_get_current_error() ;
int& reset_current_error() ;
int error_occured() ;
SEXP rcpp11_error_handler() ;
SEXP& rcpp_get_current_module() ;

#else 

namespace Rcpp {
    
    inline int& reset_current_error(){
        GET_CALLABLE(reset_current_error) ;
        return fun();  
    }
    
    inline nanotime_t get_nanotime(void){
        GET_CALLABLE(get_nanotime) ;
        return fun() ; 
    }
    
    inline SEXP Rcpp_eval(SEXP expr, SEXP env = R_GlobalEnv){
        GET_CALLABLE(Rcpp_eval) ;
        return fun(expr, env) ;
    }
    
    inline std::string demangle( const std::string& name){
        GET_CALLABLE(demangle) ;
        return fun(name) ;
    }
    
    inline void forward_exception_to_r( const std::exception& ex ){
        GET_CALLABLE(forward_exception_to_r); 
        return fun(ex) ;
    }
    
    inline SEXP exception_to_try_error( const std::exception& ex ){
        GET_CALLABLE(exception_to_try_error);
        return fun(ex) ;
    }
    
    inline SEXP string_to_try_error( const std::string& str){
        GET_CALLABLE(string_to_try_error) ;
        return fun(str) ;
    }
    
    inline SEXP stack_trace( const char *file, int line){
        GET_CALLABLE(stack_trace) ;
        return fun(file, line) ;
    }
    
    inline unsigned long enterRNGScope(){
         GET_CALLABLE(enterRNGScope) ;
         return fun() ;
    }
    
    inline unsigned long exitRNGScope(){
         GET_CALLABLE(exitRNGScope) ;
         return fun() ;
    }
    
}
 
inline SEXP rcpp_get_current_error(){
    GET_CALLABLE(rcpp_get_current_error);
    return fun();
}

inline SEXP rcpp_set_stack_trace(SEXP x){
    GET_CALLABLE(rcpp_set_stack_trace) ;
    return fun(x) ;    
}

inline SEXP rcpp11_error_handler(){
    GET_CALLABLE(rcpp11_error_handler); 
    return fun(); 
}
  
inline int error_occured(){
    GET_CALLABLE(error_occured); 
    return fun(); 
}

inline SEXP& rcpp_get_current_module(){
    GET_CALLABLE(rcpp_get_current_module); 
    return fun();
}


#endif

#endif
