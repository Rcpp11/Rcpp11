#ifndef Rcpp__protection_Shield_h
#define Rcpp__protection_Shield_h

namespace Rcpp{
    
    template <typename T>
    class Shield{
    public:
        Shield( SEXP t_) : t(t_){
            if( t != R_NilValue ) PROTECT(t); 
        }
        ~Shield(){
            if( t != R_NilValue ) UNPROTECT(1) ;    
        }
        Shield( const Shield& other ) : t(other.t){
            if( t != R_NilValue ) PROTECT(t);
        }
        Shield& operator=( const Shield& ) = delete ;
        
        Shield( Shield&& other ) : t(other.t) {
            other.t = R_NilValue ;
        }
        Shield& operator=( Shield&& other ){
            t = other.t ;
            other.t = R_NilValue ;
            return *this ;
        }
        
        // allowing Shield to be used with R internals macros
        inline SEXP operator->() const {
            return t;
        }
        inline operator SEXP() const { return t; }
        
    private:
        SEXP t ;
    } ;
    
}

#endif
