#ifndef Rcpp_ProtectedProxy_h
#define Rcpp_ProtectedProxy_h

namespace Rcpp{
    
    template <class XPtrClass>
    class ProtectedProxy : public GenericProxy<ProtectedProxy<XPtrClass>> {
    public:
        ProtectedProxy( XPtrClass& xp_ ): xp(xp_){}
        
        template <typename U>
        ProtectedProxy& operator=( const U& u) {
            return set( wrap(u) );  
        }
        
        template <typename U>
        operator U() const {
            return as<U>(get());  
        }
        
        operator SEXP() const{ 
            return get() ; 
        }
        
    private:
        XPtrClass& xp ;
        
        inline SEXP get() const {
            return R_ExternalPtrProtected(xp) ;
        }
        
        inline ProtectedProxy& set( SEXP x){
            R_SetExternalPtrProtected( xp, x ) ;
            return *this ;
        }
    
    } ;

}

#endif
