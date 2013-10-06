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

// Rcpp api classes
namespace Rcpp {

    // Evaluator
    SEXP Rcpp_evaluate(SEXP expr_, SEXP env) {
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

    // Dimension
    Dimension::Dimension() : dims(){}
        
    Dimension::Dimension(SEXP x): dims(){
        dims = as< std::vector<int> >(x) ;
    }
        
    Dimension::Dimension( const Dimension& other ) : dims(){
        dims = other.dims ; /* copy */
    }
        
    Dimension& Dimension::operator=(const Dimension& other){
        dims = other.dims ; /* copy */
        return *this ;
    }
        
    Dimension::Dimension(const size_t& n1) : dims(1){
        dims[0] = n1 ;
    }
        
    Dimension::Dimension(const size_t& n1, const size_t& n2) : dims(2){
        dims[0] = n1 ;
        dims[1] = n2 ;
    }
        
    Dimension::Dimension(const size_t& n1, const size_t& n2, const size_t& n3) : dims(3){
        dims[0] = n1 ;
        dims[1] = n2 ;
        dims[2] = n3 ;
    }
        
    Dimension::operator SEXP() const {
        return wrap( dims.begin(), dims.end() ) ;
    }
        
    int Dimension::size() const {
        return static_cast<int>( dims.size() ) ;
    }
        
    int Dimension::prod() const {
        return std::accumulate( dims.begin(), dims.end(), 1, std::multiplies<int>() ) ;
    }
        
    Dimension::reference Dimension::operator[](int i) {
        if( i < 0 || i>=static_cast<int>(dims.size()) ) throw std::range_error("index out of bounds") ;
        return dims.at(i) ;
    }

    Dimension::const_reference Dimension::operator[](int i) const {
        if( i < 0 || i>=static_cast<int>(dims.size()) ) throw std::range_error("index out of bounds") ;
        return dims.at(i) ;
    }    
    
    // DataFrame
    namespace internal{
        inline SEXP empty_data_frame(){
            SEXP dataFrameSym = ::Rf_install( "data.frame"); // cannot be gc()ed once in symbol table
            return ::Rf_eval( ::Rf_lang1( dataFrameSym ), R_GlobalEnv ) ;       
        }
    }
             
    DataFrame::DataFrame(): List( internal::empty_data_frame() ){}
    DataFrame::DataFrame(SEXP x) {
        set_sexp(x) ;
    }  
    DataFrame::DataFrame( const DataFrame& other): List(other.get__()) {}
    
    DataFrame& DataFrame::operator=( DataFrame& other) {
        set__( other.get__() ) ;
        return *this ;
    }
            
    DataFrame& DataFrame::operator=( SEXP x) {
        set__(x) ;
        return *this ;
    }
    DataFrame::~DataFrame(){}     
    void DataFrame::set_sexp(SEXP x) {
        if( ::Rf_inherits( x, "data.frame" )){
            set__( x ) ;
        } else{
            SEXP y = internal::convert_using_rfunction( x, "as.data.frame" ) ;
            set__( y ) ;
            x = y ;
        }
    } 
    int DataFrame::nrows() const { return Rf_length( VECTOR_ELT(get__(), 0) ); }
        
    DataFrame DataFrame::from_list( Rcpp::List obj ){
        bool use_default_strings_as_factors = true ;
        bool strings_as_factors = true ;
        int strings_as_factors_index = -1 ;
        int n = obj.size() ;
        CharacterVector names = obj.attr( "names" ) ;
        if( !names.isNULL() ){
            for( int i=0; i<n; i++){
                if( names[i] == "stringsAsFactors" ){
                    strings_as_factors_index = i ;
                    use_default_strings_as_factors = false ;        
                    if( !as<bool>(obj[i]) ) strings_as_factors = false ;
                    break ;         
                }
            }
        }
        if( use_default_strings_as_factors ) 
            return DataFrame(obj) ;
        SEXP as_df_symb = Rf_install("as.data.frame");
        SEXP strings_as_factors_symb = Rf_install("stringsAsFactors");
        
        obj.erase(strings_as_factors_index) ;
        names.erase(strings_as_factors_index) ;
        obj.attr( "names") = names ;
        Scoped<SEXP> call  = Rf_lang3(as_df_symb, obj, wrap( strings_as_factors ) ) ;
        SET_TAG( CDDR(call),  strings_as_factors_symb ) ;   
        Scoped<SEXP> res = Rcpp_eval( call ) ; 
        DataFrame out( res ) ;
        return out ;
    }
    
    
    
} // namespace Rcpp


// Rcomplex support
Rcomplex operator*( const Rcomplex& lhs, const Rcomplex& rhs){          
    Rcomplex y ;
    y.r = lhs.r * rhs.r - lhs.i * rhs.i ;
    y.i = lhs.r * rhs.i + rhs.r * lhs.i ;
    return y ;
}
Rcomplex operator+( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r + rhs.r ;
    y.i = lhs.i + rhs.i ;
    return y ;
}

Rcomplex operator-( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r - rhs.r ;
    y.i = lhs.i - rhs.i ;
    return y ;
}
   
Rcomplex operator/( const Rcomplex& a, const Rcomplex& b){

	Rcomplex c ;
    double ratio, den;
    double abr, abi;

    if( (abr = b.r) < 0)
	abr = - abr;
    if( (abi = b.i) < 0)
	abi = - abi;
    if( abr <= abi ) {
	ratio = b.r / b.i ;
	den = b.i * (1 + ratio*ratio);
	c.r = (a.r*ratio + a.i) / den;
	c.i = (a.i*ratio - a.r) / den;
    }
    else {
	ratio = b.i / b.r ;
	den = b.r * (1 + ratio*ratio);
	c.r = (a.r + a.i*ratio) / den;
	c.i = (a.i - a.r*ratio) / den;
    }
    return c ;
}
bool operator==( const Rcomplex& a, const Rcomplex& b){
    return a.r == b.r && a.i == b.i ;    
}


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
    
    SEXP try_catch( SEXP expr, SEXP env ) {
        RCPP_DEBUG( "try_catch( expr = <%p>, env = <%p> )", expr, env )
        return Rcpp_eval(expr, env) ;
    }
    SEXP try_catch( SEXP expr ) {
        RCPP_DEBUG( "try_catch( expr = <%p> )", expr )
        return Rcpp_eval(expr) ;
    }
    
    SEXP eval_methods<EXPRSXP>::eval(){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return try_catch( Rf_lang2( evalSym, xp ) ) ;
    }
    
    SEXP eval_methods<EXPRSXP>::eval( SEXP env ){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return try_catch( Rf_lang3( evalSym, xp, env ) ) ;
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

