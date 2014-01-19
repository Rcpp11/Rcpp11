#ifndef Rcpp__protection_Shield_h
#define Rcpp__protection_Shield_h

namespace Rcpp{
    
    inline SEXP Rcpp_protect(SEXP x){
        if( x != R_NilValue ) PROTECT(x) ; 
        return x ; 
    }
    
    template <typename T>
    class Shield{
    public:
        Shield( SEXP t_) : t(Rcpp_protect(t_)){}
        ~Shield(){
            if( t != R_NilValue ) UNPROTECT(1) ;    
        }
        Shield( const Shield& ) = delete ;
        Shield& operator=( const Shield& ) = delete ;
        
        Shield( Shield&& other ) : t(other.t) {
            other.t = R_NilValue ;
        }
        Shield& operator=( Shield&& other ){
            t = other.t ;
            other.t = R_NilValue ;
            return *this ;
        }
        
        operator SEXP() const { return t; }
        SEXP t ;
    } ;
    
}

#endif
