#ifndef Rcpp__vector__generic_name_proxy_h
#define Rcpp__vector__generic_name_proxy_h

namespace Rcpp{
namespace internal{
    
    template <int RTYPE> class generic_name_proxy : public name_proxy<RTYPE,Vector<RTYPE>>{
    public:
        using name_proxy<RTYPE,Vector<RTYPE>>::set ;
        
        typedef ::Rcpp::Vector<RTYPE> VECTOR ;
        generic_name_proxy( VECTOR& v, std::string  name_) :
            parent(v), name(std::move(name_))
        {}
        generic_name_proxy( const generic_name_proxy& other ) : 
            parent(other.parent), name(other.name){}
        ~generic_name_proxy(){}
    
        generic_name_proxy& operator=( SEXP rhs ){
            set( rhs ) ;
            return *this ;
        }
        generic_name_proxy& operator=( const generic_name_proxy& other){
            set( other.get() ) ;
            return *this ;
        }
    
        template <typename T>
        generic_name_proxy& operator=( const T& rhs ){
            set( ::Rcpp::wrap(rhs) ) ;
            return *this ;
        }
    
        operator SEXP() const {
             return get() ;
        }
    
        template <typename T>
        operator T() const {
            return ::Rcpp::as<T>( get() ) ;
        }
    
        operator bool() const{
            return ::Rcpp::as<bool>(get()); 
        }
    
    private:
        VECTOR& parent ;
        std::string name;
        void set( SEXP rhs ){
            set( parent, name, rhs ) ;    
        }
        SEXP get() const {
            return parent[ parent.offset(name) ];
        }
    } ;
}
}
#endif
