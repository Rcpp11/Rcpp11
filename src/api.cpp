#include <Rcpp.h>

namespace Rcpp {

    static SEXP get_exception_classes( const std::string& ex_class) {
        Shield<SEXP> res = Rf_allocVector( STRSXP, 4 );
        SET_STRING_ELT( res, 0, Rf_mkChar( ex_class.c_str() ) ) ;
        SET_STRING_ELT( res, 1, Rf_mkChar( "C++Error" ) ) ;
        SET_STRING_ELT( res, 2, Rf_mkChar( "error" ) ) ;
        SET_STRING_ELT( res, 3, Rf_mkChar( "condition" ) ) ;
        return res;
    }
    
    static SEXP make_condition(const std::string& ex_msg, SEXP call, SEXP classes){
        Shield<SEXP> res     = Rf_allocVector( VECSXP, 2 ) ;
        Shield<SEXP> message = Rf_mkString( ex_msg.c_str() ) ;
        RCPP_SET_VECTOR_ELT( res, 0, message ) ;
        RCPP_SET_VECTOR_ELT( res, 1, call ) ;
        Shield<SEXP> names = Rf_allocVector( STRSXP, 2 ) ;
        SET_STRING_ELT( names, 0, Rf_mkChar( "message" ) ) ;
        SET_STRING_ELT( names, 1, Rf_mkChar( "call" ) ) ;
        Rf_setAttrib( res, R_NamesSymbol, names ) ;
        Rf_setAttrib( res, R_ClassSymbol, classes ) ;
        return res ;
    }
    
    static SEXP exception_to_r_condition( const std::exception& ex){
        std::string ex_class = Rcpp::demangle( typeid(ex).name() ) ;
        std::string ex_msg   = ex.what() ; 
        
        Shield<SEXP> call      = get_current_call() ;
        Shield<SEXP> classes   = get_exception_classes(ex_class) ;
        Shield<SEXP> condition = make_condition( ex_msg, call, classes ) ; 
        return condition ;
    }
    
    // [[Rcpp::register]]
    void forward_exception_to_r( const std::exception& ex){
        SEXP stop_sym  = Rf_install( "stop" ) ;
        Shield<SEXP> condition = exception_to_r_condition(ex) ;
        Shield<SEXP> expr = Rf_lang2( stop_sym , condition );
        Rf_eval( expr, R_GlobalEnv ) ;
    }

    // [[Rcpp::register]]
    SEXP exception_to_try_error( const std::exception& ex ){
        return string_to_try_error(ex.what());
    }
    
    // [[Rcpp::register]]
    SEXP string_to_try_error( const std::string& str){
        // form simple error condition based on a string
        Shield<SEXP> simpleErrorExpr = ::Rf_lang2(::Rf_install("simpleError"), Rf_mkString(str.c_str()));
        Shield<SEXP> simpleError = Rf_eval(simpleErrorExpr, R_GlobalEnv);
    	
        Shield<SEXP> tryError = Rf_mkString( str.c_str() ) ;
        Rf_setAttrib( tryError, R_ClassSymbol, Rf_mkString("try-error") ) ; 
        Rf_setAttrib( tryError, Rf_install( "condition") , simpleError ) ; 
        return tryError;
    }

}

