#ifndef Rcpp_ProtectedProxy_h
#define Rcpp_ProtectedProxy_h

namespace Rcpp{
    
    template <class XPtrClass>
    class ProtectedProxyPolicy{
    public:
        
        class ProtectedProxy : public GenericProxy<ProtectedProxy> {
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

        class const_ProtectedProxy : public GenericProxy<const_ProtectedProxy>{
        public:
            const_ProtectedProxy( const XPtrClass& xp_ ): xp(xp_){}
            
            template <typename U>
            operator U() const {
                return as<U>(get());
            }
            
            operator SEXP() const{ 
                return get() ; 
            }
            
        private:
            const XPtrClass& xp ;
            
            inline SEXP get() const {
                return R_ExternalPtrProtected(xp) ;
            }
            
        } ;

        ProtectedProxy prot(){
            return ProtectedProxy( static_cast<XPtrClass&>(*this) ) ;
        }
        
        const_ProtectedProxy prot() const {
            return const_ProtectedProxy( static_cast<const XPtrClass&>(*this) ) ;
        }

        
    } ;
    
}

#endif
