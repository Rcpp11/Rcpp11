#ifndef Rcpp_Na_Proxy_h
#define Rcpp_Na_Proxy_h

namespace Rcpp{
    class Na_Proxy{
    
        friend inline bool operator==(double x      , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<REALSXP>(x) ; }
        friend inline bool operator==(int x         , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<INTSXP>(x) ; }
        friend inline bool operator==(Rcpp::String x, Rcpp::Na_Proxy){ return Rcpp::traits::is_na<STRSXP>(x) ; }
        friend inline bool operator==(Rcomplex x    , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<CPLXSXP>(x) ; }
        friend inline bool operator==(SEXP x        , Rcpp::Na_Proxy){ return TYPEOF(x)==CHARSXP && Rcpp::traits::is_na<STRSXP>(x) ; }
        friend inline bool operator==(std::string   , Rcpp::Na_Proxy){ return false ; }
        friend inline bool operator==(const char*   , Rcpp::Na_Proxy){ return false ; }
        friend inline bool operator==(Rboolean b    , Rcpp::Na_Proxy){ return b == NA_VALUE ; }
        
        template <typename Vec>
        friend inline bool operator==(Rcpp::internal::string_proxy<Vec> x, Rcpp::Na_Proxy){ 
            return Rcpp::traits::is_na<STRSXP>(x.get()) ; 
        }  
        
        template <typename T>
        friend inline bool operator==(Rcpp::Na_Proxy na, T x){ 
            return x == na ; 
        } 
        
        template <typename T>
        friend inline bool operator!=( Na_Proxy na, T x){ 
            return !(x==na) ; 
        }
        
        template <typename T>
        friend inline bool operator!=( T x, Na_Proxy na){ 
            return !(x==na) ; 
        }
        
    public:
        
        inline operator int() const { return NA_INTEGER ; }
        inline operator Rcomplex() const { return traits::get_na<CPLXSXP>() ; }
        inline operator double() const { return NA_REAL ; }
        inline operator SEXP() const { return NA_STRING; }
        inline operator Rboolean() const { return NA_VALUE ; }
        
    } ;
    static Na_Proxy NA ;    

    inline String::String( Na_Proxy ) : data( NA_STRING ){}

    inline String& String::operator=( Na_Proxy ) {
        data = NA_STRING ;
        return *this ;
    }    

    
}
#endif
