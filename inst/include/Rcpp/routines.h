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
    SEXP Rcpp_eval(SEXP expr, SEXP env = R_GlobalEnv) ;
}

#if defined(COMPILING_RCPP11)

// the idea is that this file should be generated automatically
// by Rcpp::register

namespace Rcpp{
    void forward_exception_to_r( const std::exception& ex ) ;
    SEXP exception_to_try_error( const std::exception& ex ) ;
    SEXP string_to_try_error( const std::string& str) ;
    unsigned long enterRNGScope(); 
    unsigned long exitRNGScope() ;
}
           
#else 

namespace Rcpp {
    
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
    
    inline unsigned long enterRNGScope(){
         GET_CALLABLE(enterRNGScope) ;
         return fun() ;
    }
    
    inline unsigned long exitRNGScope(){
         GET_CALLABLE(exitRNGScope) ;
         return fun() ;
    }
    
}

#endif

#endif
