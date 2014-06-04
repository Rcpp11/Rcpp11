#ifndef Rcpp_Na_Proxy_h
#define Rcpp_Na_Proxy_h

namespace Rcpp{
    class Na_Proxy{
    
        friend inline bool operator==(double x      , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<REALSXP>(x) ; }
        friend inline bool operator==(int x         , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<INTSXP>(x) ; }
        friend inline bool operator==(Rcpp::String x, Rcpp::Na_Proxy){ return Rcpp::traits::is_na<STRSXP>(x.get_sexp()) ; }
        friend inline bool operator==(Rcomplex x    , Rcpp::Na_Proxy){ return Rcpp::traits::is_na<CPLXSXP>(x) ; }
        friend inline bool operator==(SEXP x        , Rcpp::Na_Proxy){ return TYPEOF(x)==CHARSXP && Rcpp::traits::is_na<STRSXP>(x) ; }
        friend inline bool operator==(std::string   , Rcpp::Na_Proxy){ return false ; }
        friend inline bool operator==(const char*   , Rcpp::Na_Proxy){ return false ; }
        
        friend inline bool operator==(Rcpp::Na_Proxy, double x       ){ return Rcpp::traits::is_na<REALSXP>(x) ; }
        friend inline bool operator==(Rcpp::Na_Proxy, int x          ){ return Rcpp::traits::is_na<INTSXP>(x) ; }
        friend inline bool operator==(Rcpp::Na_Proxy, Rcpp::String x ){ return Rcpp::traits::is_na<STRSXP>(x.get_sexp()) ; }
        friend inline bool operator==(Rcpp::Na_Proxy, SEXP x         ){ return TYPEOF(x)==CHARSXP && Rcpp::traits::is_na<STRSXP>(x) ; }
        friend inline bool operator==(Rcpp::Na_Proxy, Rcomplex x     ){ return Rcpp::traits::is_na<CPLXSXP>(x) ; }
        friend inline bool operator==(Rcpp::Na_Proxy, std::string    ){ return false ; }
        friend inline bool operator==(Rcpp::Na_Proxy, const char*    ){ return false ; }
        
        template <typename Vec>
        friend inline bool operator==(Rcpp::internal::string_proxy<Vec> x, Rcpp::Na_Proxy){ 
            return Rcpp::traits::is_na<STRSXP>(x.get()) ; 
        }  
        template <typename Vec>
        friend inline bool operator==(Rcpp::Na_Proxy, Rcpp::internal::string_proxy<Vec> x){ 
            return Rcpp::traits::is_na<STRSXP>(x.get()) ; 
        }
        
        template <typename T>
        friend inline bool operator!=( Na_Proxy na, T x){ return !(x==na) ; }
        
        template <typename T>
        friend inline bool operator!=( T x, Na_Proxy na){ return !(x==na) ; }
        
    public:
        
        inline operator int() const { return NA_INTEGER ; }
        inline operator Rcomplex() const { return traits::get_na<CPLXSXP>() ; }
        inline operator double() const { return NA_REAL ; }
        inline operator SEXP() const { return NA_STRING; }
        
    } ;
    static Na_Proxy NA ;    

    inline String::String( Na_Proxy ) : data(NA_STRING), valid(true), buffer_ready(false) {}
    
    inline String& String::operator=( Na_Proxy ) {
      data = NA_STRING ;
      buffer_ready = false ;
      valid = true ;
      return *this ;  
    }
            
}
#endif
