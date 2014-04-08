#ifndef RCPP_CONDITION_H
#define RCPP_CONDITION_H

namespace Rcpp {

    class Condition {
    public:
        Condition( const Condition& ) = delete ;
        Condition operator=( const Condition& ) = delete ;
        
        Condition( const std::exception& ex_) : ex(ex_) {}
        
        inline SEXP get_exception_classes() {
            std::string ex_class = demangle( typeid(ex).name() ) ;
        
            Shield<SEXP> res = Rf_allocVector( STRSXP, 4 );
            SET_STRING_ELT( res, 0, Rf_mkChar( ex_class.c_str() ) ) ;
            SET_STRING_ELT( res, 1, Rf_mkChar( "C++Error" ) ) ;
            SET_STRING_ELT( res, 2, Rf_mkChar( "error" ) ) ;
            SET_STRING_ELT( res, 3, Rf_mkChar( "condition" ) ) ;
            return res;
        }
        
        inline void stop(){
            Shield<SEXP> cond    = Rf_allocVector( VECSXP, 2 ) ;
            Shield<SEXP> message = Rf_mkString( ex.what() ) ;
            SET_VECTOR_ELT( cond, 0, message ) ;
            SET_VECTOR_ELT( cond, 1, get_current_call() ) ;
            Shield<SEXP> names = Rf_allocVector( STRSXP, 2 ) ;
            SET_STRING_ELT( names, 0, Rf_mkChar( "message" ) ) ;
            SET_STRING_ELT( names, 1, Rf_mkChar( "call" ) ) ;
            Rf_setAttrib( cond, R_NamesSymbol, names ) ;
            Rf_setAttrib( cond, R_ClassSymbol, get_exception_classes() ) ;
            Shield<SEXP> call = Rf_lang2( Rf_install("stop"), cond );
            Rf_eval( call, R_GlobalEnv ) ;        
        }
        
    private:
        const std::exception& ex ;
    } ;
    
    class TryError {
    public:
       
        TryError( const std::string& str_) : str(str_){}
        
        inline operator SEXP(){
            // form simple error condition based on a string
            Shield<SEXP> simpleErrorExpr = ::Rf_lang2(::Rf_install("simpleError"), Rf_mkString(str.c_str()));
            Shield<SEXP> simpleError = Rf_eval(simpleErrorExpr, R_GlobalEnv);
    
            Shield<SEXP> tryError = Rf_mkString( str.c_str() ) ;
            Rf_setAttrib( tryError, R_ClassSymbol, Rf_mkString("try-error") ) ; 
            Rf_setAttrib( tryError, Rf_install( "condition") , simpleError ) ; 
            return tryError;
        }
    private:
        const std::string& str ;         
    } ;
    
    inline void forward_exception_to_r( const std::exception& ex){
        Condition(ex).stop();
    }
    
    inline SEXP exception_to_try_error( const std::exception& ex){
        return TryError(ex.what()) ;
    }
    
    inline SEXP string_to_try_error( const std::string& str ){
        return TryError(str) ;    
    }
    
}

#endif
