#ifndef Rcpp__vector__generic_proxy_h
#define Rcpp__vector__generic_proxy_h
 
namespace Rcpp{
    namespace internal{
        
        template <int RTYPE> 
        class generic_proxy : public GenericProxy<generic_proxy<RTYPE>>{
        public:
            friend class Proxy_Iterator<generic_proxy> ;
            
            typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
        
            generic_proxy(): parent(0), index(-1){}
        
            generic_proxy( const generic_proxy& other ) : 
                parent(other.parent), index(other.index){}
        
            generic_proxy( VECTOR& v, int i ) : parent(&v), index(i){}
    
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
        
            operator SEXP() const { 
                return get() ;
            }
        
            template <typename U> operator U() const {
                return ::Rcpp::as<U>(get()) ;
            }
        
            // helping the compiler (not sure why it can't help itself)
            operator bool() const { return ::Rcpp::as<bool>(get()) ; }
            operator int() const { return ::Rcpp::as<int>(get()) ; }
        
            void swap(generic_proxy& other){
                Shield<SEXP> tmp = get() ;
                set( other.get() ) ;
                other.set(tmp) ;
            }
        
            void import( const generic_proxy& other){
                parent = other.parent ;
                index  = other.index ;
            }
        
        private:
            
            VECTOR* parent; 
            int index ;
            
            inline void set(SEXP x) { SET_VECTOR_ELT( *parent, index, x ) ;} 
            inline SEXP get() const { return VECTOR_ELT(*parent, index ); } 
        
        }  ;
    
    }
}

#endif
