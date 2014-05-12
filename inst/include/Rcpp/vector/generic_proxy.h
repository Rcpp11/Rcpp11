#ifndef Rcpp__vector__generic_proxy_h
#define Rcpp__vector__generic_proxy_h
 
namespace Rcpp{
    namespace internal{
        
        template <typename Vec> 
        class generic_proxy : public GenericProxy<generic_proxy<Vec>>{
        public:
            friend class Proxy_Iterator<generic_proxy> ;
            
            generic_proxy( Vec& v, int i ) : parent(v), index(i){}
    
            generic_proxy& operator=(SEXP rhs) { 
                set(rhs) ;
                return *this ;
            }
        
            generic_proxy& operator=(const generic_proxy& rhs) {
                set(rhs.get());
                return *this ;
            }
    
            template <typename T>
            generic_proxy& operator=( const T& rhs){
                set(wrap(rhs)) ;
                return *this; 
            }
        
            inline operator SEXP() const { 
                return get() ;
            }
            inline operator bool() const { 
                return ::Rcpp::as<bool>(get()) ; 
            }
            inline operator int() const { 
                return ::Rcpp::as<int>(get()) ; 
            }
        
            template <typename U> 
            inline operator U() const {
                return ::Rcpp::as<U>(get()) ;
            }
            
            friend inline void swap( generic_proxy& a, generic_proxy& b){
                Shield<SEXP> tmp = a.get() ;
                a.set( b.get() ) ;
                b.set(tmp) ;    
            }
            
        private:
            
            Vec& parent; 
            int index ;
            
            inline void set(SEXP x) { SET_VECTOR_ELT( parent, index, x ) ;} 
            inline SEXP get() const { return VECTOR_ELT(parent, index ); } 
        
        }  ;
    
    }
}

#endif
