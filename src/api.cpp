// api.cpp:  Rcpp api
//
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.
  
#define COMPILING_RCPP11

#include <Rcpp.h>
#include "internal.h" 

namespace Rcpp {

    // Evaluator
    SEXP Rcpp_eval__impl(SEXP expr_, SEXP env) {
        RCPP_DEBUG( "Rcpp_eval( expr = <%p>, env = <%p> )", expr_, env ) 
        Scoped<SEXP> expr = expr_ ;

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
        
        Scoped<SEXP> call = Rf_lang3( 
            tryCatchSym, 
            Rf_lang3( evalqSym, expr, env ),
            errorRecorderSym
        ) ;
        SET_TAG( CDDR(call), errorSym ) ;
        /* call the tryCatch call */
        Scoped<SEXP> res  = ::Rf_eval( call, RCPP );
        
        if( error_occured() ) {
            Scoped<SEXP> current_error        =  rcpp_get_current_error() ;
            Scoped<SEXP> conditionMessageCall = ::Rf_lang2(conditionMessageSym, current_error) ;
            Scoped<SEXP> condition_message    = ::Rf_eval(conditionMessageCall, R_GlobalEnv) ;
            std::string message(CHAR(::Rf_asChar(condition_message)));
            throw eval_error(message) ;
        }

        return res ;
    }
    
} // namespace Rcpp

// demangling
#include <cxxabi.h>

std::string demangle( const std::string& name ){
    std::string real_class ;
    int status =-1 ;
    char *dem = 0;
    dem = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
    if( status == 0 ){
        real_class = dem ;
        free(dem);
    } else {
        real_class = name ;
    }
    return real_class ;
}


// utilities

const char * sexp_to_name(int sexp_type) {
    switch (sexp_type) {
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
    default:
	return "<unknown>";
    }
}

namespace Rcpp{
namespace internal{

	template<> int* r_vector_start<INTSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<INTSXP>( SEXP = %p )", x )
	    return INTEGER(x) ; 
	}
	template<> int* r_vector_start<LGLSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<LGLSXP>( SEXP = %p )", x )
	    return LOGICAL(x) ;
	}
	template<> double* r_vector_start<REALSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<REALSXP>( SEXP = %p )", x )
	    return REAL(x) ;
	}
	template<> Rbyte* r_vector_start<RAWSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<RAWSXP>( SEXP = %p )", x )
	    return RAW(x) ;
	}
	template<> Rcomplex* r_vector_start<CPLXSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<CPLXSXP>( SEXP = %p )", x )
	    return COMPLEX(x) ;
	}
	
	template<> void r_init_vector<VECSXP>(SEXP x){}
	template<> void r_init_vector<EXPRSXP>(SEXP x){}
	template<> void r_init_vector<STRSXP>(SEXP x){}

	template<> Rcomplex get_zero<CPLXSXP,Rcomplex>(){
		Rcomplex x ;
		x.r = 0.0 ;
		x.i = 0.0 ;
		return x ;
	}

	template<> Rcomplex caster<std::complex<double>, Rcomplex>( std::complex<double> from){
		Rcomplex cx ;
		cx.r = from.real() ; 
		cx.i = from.imag() ;
		return cx ;
	}
	template<> Rcomplex caster<std::complex<float>, Rcomplex>( std::complex<float> from){
		Rcomplex cx ;
		cx.r = static_cast<double>( from.real() ); 
		cx.i = static_cast<double>( from.imag() );
		return cx ;
	}

	template<> std::complex<double> caster<Rcomplex,std::complex<double> >( Rcomplex from){
		return std::complex<double>(from.r, from.i ) ;
	}
	template<> std::complex<float> caster<Rcomplex,std::complex<float> >( Rcomplex from){
		return std::complex<float>(static_cast<float>(from.r), static_cast<float>(from.i) ) ;
	}
	template<> SEXP caster<String,SEXP>( String from){
		return from.get_sexp() ;
	}
	

	SEXP convert_using_rfunction(SEXP x, const char* const fun) {
        SEXP res = R_NilValue ;
        try{
            SEXP funSym = Rf_install(fun);
            res = Rcpp_eval( Rf_lang2( funSym, x ) ) ;
        } catch( eval_error& e){
            throw ::Rcpp::not_compatible( std::string("could not convert using R function : ") + fun  ) ;
        }
        return res;
    }
    
    SEXP eval_methods<EXPRSXP>::eval(){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return Rcpp_eval( Rf_lang2( evalSym, xp ) ) ;
    }
    
    SEXP eval_methods<EXPRSXP>::eval( SEXP env ){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return Rcpp_eval( Rf_lang3( evalSym, xp, env ) ) ;
    }
	
} // internal
} // Rcpp

SEXP as_character_externalptr(SEXP xp){
	char buffer[20] ;
	snprintf( buffer, 20, "%p", (void*)EXTPTR_PTR(xp) ) ;
	return Rcpp::wrap( (const char*)buffer ) ;
}

SEXP exception_to_try_error( const std::exception& ex ){
    return string_to_try_error(ex.what());
}

SEXP string_to_try_error( const std::string& str){

    using namespace Rcpp;
	
    // form simple error condition based on a string
    Scoped<SEXP> simpleErrorExpr = ::Rf_lang2(::Rf_install("simpleError"), Rf_mkString(str.c_str()));
    Scoped<SEXP> simpleError = Rf_eval(simpleErrorExpr, R_GlobalEnv);
	
    Scoped<SEXP> tryError = Rf_mkString( str.c_str() ) ;
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
    	Rcpp::Named( "stack" ) = "C++ stack not available on this system" ) ;
    trace.attr("class") = "Rcpp_stack_trace" ;
    return trace ;
}
#else // ! (defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
#include <execinfo.h>
#include <cxxabi.h>

static std::string demangler_one( const char* input){
    static std::string buffer ;
    buffer = input ;
    buffer.resize( buffer.find_last_of( '+' ) - 1 ) ;
    buffer.erase(
        buffer.begin(), 
        buffer.begin() + buffer.find_last_of( ' ' ) + 1
    ) ;
    return demangle( buffer) ;
}

/* inspired from http://tombarta.wordpress.com/2008/08/01/c-stack-traces-with-gcc/  */ 
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
SEXP stack_trace( const char *file, int line) {
	return R_NilValue ;
}
#endif   

