#ifndef Rcpp__vector__const_generic_proxy_h
#define Rcpp__vector__const_generic_proxy_h
 
namespace Rcpp{
namespace internal{
    
    template <int RTYPE> 
    class const_generic_proxy : public GenericProxy<const_generic_proxy<RTYPE>> {
    public:
        typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
        
        const_generic_proxy(): parent(0), index(-1){}
        
        const_generic_proxy( const const_generic_proxy& other ) : parent(other.parent), index(other.index){} ;
        
        const_generic_proxy( const VECTOR& v, int i ) : parent(&v), index(i){} ;
        
        const_generic_proxy& operator=(const const_generic_proxy& rhs)  = delete  ;
        
        operator SEXP() const { 
            return get() ;
        }
        
        template <typename U> operator U() const {
            return ::Rcpp::as<U>(get()) ;
        }
        
        // helping the compiler (not sure why it can't help itself)
        operator bool() const { return ::Rcpp::as<bool>(get()) ; }
        operator int() const { return ::Rcpp::as<int>(get()) ; }
        
        void import( const const_generic_proxy& other){
           parent = other.parent ;
           index  = other.index ;
        }
        
        const VECTOR* parent; 
        int index ;
    
    private:
       inline void move(int n) { index += n ; }
    
    
         inline SEXP get() const { return VECTOR_ELT(*parent, index ); } 
    
      }  ;

}
}

#endif
