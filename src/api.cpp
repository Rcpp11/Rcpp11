#define COMPILING_RCPP11

#include <Rcpp.h>
#include "internal.h" 

namespace Rcpp {

    // [[Rcpp::register]]
    SEXP Rcpp_eval(SEXP expr_, SEXP env) {
        RCPP_DEBUG( "Rcpp_eval( expr = <%p>, env = <%p> )", expr_, env ) 
        Shield<SEXP> expr = expr_ ;

        reset_current_error() ; 

        Environment RCPP = Environment::Rcpp11_namespace(); 
        static SEXP tryCatchSym = NULL, evalqSym, conditionMessageSym, errorRecorderSym, errorSym ;
        if (!tryCatchSym) {
            tryCatchSym               = ::Rf_install("tryCatch");
            evalqSym                  = ::Rf_install("evalq");
            conditionMessageSym       = ::Rf_install("conditionMessage");
            errorRecorderSym          = ::Rf_install(".rcpp_error_recorder");
            errorSym                  = ::Rf_install("error");
        }
        RCPP_DEBUG( "  [Rcpp_eval] RCPP = " ) 
        
        Shield<SEXP> call = Rf_lang3( 
            tryCatchSym, 
            Rf_lang3( evalqSym, expr, env ),
            errorRecorderSym
        ) ;
        SET_TAG( CDDR(call), errorSym ) ;
        /* call the tryCatch call */
        Shield<SEXP> res  = ::Rf_eval( call, RCPP );
        
        if( error_occured() ) {
            Shield<SEXP> conditionMessageCall = ::Rf_lang2(conditionMessageSym, rcpp_current_error() ) ;
            Shield<SEXP> condition_message    = ::Rf_eval(conditionMessageCall, R_GlobalEnv) ;
            std::string message(CHAR(::Rf_asChar(condition_message)));
            throw eval_error(message) ;
        }

        return res ;
    }
    
    static SEXP get_last_call(){
        SEXP sys_calls_symbol = Rf_install( "sys.calls" ) ;
        Shield<SEXP> sys_calls_expr = Rf_lang1(sys_calls_symbol) ;   
        Shield<SEXP> calls = Rf_eval( sys_calls_expr, R_GlobalEnv ) ;
        SEXP res = calls ;
        while( !Rf_isNull(CDR(res)) ) res = CDR(res); 
        return CAR(res) ;
    }
    
    static SEXP get_exception_classes( const std::string& ex_class) {
        Shield<SEXP> res = Rf_allocVector( STRSXP, 4 );
        SET_STRING_ELT( res, 0, Rf_mkChar( ex_class.c_str() ) ) ;
        SET_STRING_ELT( res, 1, Rf_mkChar( "C++Error" ) ) ;
        SET_STRING_ELT( res, 2, Rf_mkChar( "error" ) ) ;
        SET_STRING_ELT( res, 3, Rf_mkChar( "condition" ) ) ;
        return res;
    }
    
    static SEXP make_condition(const std::string& ex_msg, SEXP call, SEXP cppstack, SEXP classes){
        Shield<SEXP> res     = Rf_allocVector( VECSXP, 3 ) ;
        Shield<SEXP> message = Rf_mkString( ex_msg.c_str() ) ;
        RCPP_SET_VECTOR_ELT( res, 0, message ) ;
        RCPP_SET_VECTOR_ELT( res, 1, call ) ;
        RCPP_SET_VECTOR_ELT( res, 2, cppstack ) ;
        Shield<SEXP> names = Rf_allocVector( STRSXP, 3 ) ;
        SET_STRING_ELT( names, 0, Rf_mkChar( "message" ) ) ;
        SET_STRING_ELT( names, 1, Rf_mkChar( "call" ) ) ;
        SET_STRING_ELT( names, 2, Rf_mkChar( "cppstack" ) ) ;
        Rf_setAttrib( res, R_NamesSymbol, names ) ;
        Rf_setAttrib( res, R_ClassSymbol, classes ) ;
        return res ;
    }
    
    static SEXP exception_to_r_condition( const std::exception& ex){
        std::string ex_class = Rcpp::demangle( typeid(ex).name() ) ;
        std::string ex_msg   = ex.what() ; 
        
        Shield<SEXP> cppstack  = rcpp_stack_trace() ;
        Shield<SEXP> call      = get_last_call() ;
        Shield<SEXP> classes   = get_exception_classes(ex_class) ;
        Shield<SEXP> condition = make_condition( ex_msg, call, cppstack, classes ) ; 
        rcpp_stack_trace() = R_NilValue ;
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

    #if defined(__GNUC__)
    #if defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
        // Simpler version for Windows and *BSD 
        SEXP stack_trace( const char* file, int line ){
            Rcpp::List trace = Rcpp::List::create( 
                Rcpp::Named( "file"  ) = file, 
                Rcpp::Named( "line"  ) = line, 
                Rcpp::Named( "stack" ) = "C++ stack not available on this system"
            ) ;
            trace.attr("class") = "Rcpp_stack_trace" ;
            return trace ;
        }
    #else 
    #include <execinfo.h>
    
        static std::string demangler_one( const char* input){
            static std::string buffer ;
            buffer = input ;
            buffer.resize( buffer.find_last_of( '+' ) - 1 ) ;
            buffer.erase(
                buffer.begin(), 
                buffer.begin() + buffer.find_last_of( ' ' ) + 1
            ) ;
            return Rcpp::demangle( buffer) ;
        }
        
        // [[Rcpp::register]]
        SEXP stack_trace( const char *file, int line) {
            const size_t max_depth = 100;
            size_t stack_depth;
            void *stack_addrs[max_depth];
            char **stack_strings;
        
            stack_depth = backtrace(stack_addrs, max_depth);
            stack_strings = backtrace_symbols(stack_addrs, stack_depth);
        
            std::string current_line ;
            
            Rcpp::CharacterVector res( stack_depth - 1) ;
            std::transform( 
                stack_strings + 1, stack_strings + stack_depth, 
                res.begin(), 
                demangler_one 
            ) ;
            free(stack_strings); // malloc()ed by backtrace_symbols
            
            Rcpp::List trace = Rcpp::List::create( 
                Rcpp::Named( "file"  ) = file, 
                Rcpp::Named( "line"  ) = line, 
                Rcpp::Named( "stack" ) = res ) ;
            trace.attr("class") = "Rcpp_stack_trace" ;
            return trace ;
        }
    #endif 
    #else /* !defined( __GNUC__ ) */
        SEXP stack_trace__impl( const char *file, int line) {
            return R_NilValue ;
        }
    #endif   

    namespace {
        unsigned long RNGScopeCounter = 0;
    }
    
    // [[Rcpp::register]]
    unsigned long enterRNGScope() {       
        if (RNGScopeCounter == 0)
            GetRNGstate();       
        return ++RNGScopeCounter;
    }
    
    // [[Rcpp::register]]
    unsigned long exitRNGScope() {
        RNGScopeCounter--;
        if (RNGScopeCounter == 0)
            PutRNGstate();
        return RNGScopeCounter ;
    }

}

