#ifndef Rcpp__vector__simple_const_name_proxy_h
#define Rcpp__vector__simple_const_name_proxy_h

namespace Rcpp{
namespace internal{

    template <int RTYPE> class simple_const_name_proxy {
    public:
        typedef ::Rcpp::Vector<RTYPE> VECTOR ;
        typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
    
        simple_const_name_proxy( const VECTOR& v, std::string  name_) :
            parent(v), name(std::move(name_)){}
        simple_const_name_proxy( const simple_const_name_proxy& other ) : 
            parent(other.parent), name(other.name){}
        ~simple_const_name_proxy() {}
    
        simple_const_name_proxy& operator=( const simple_const_name_proxy& other) = delete ;
    
        operator CTYPE() const {
             return get() ;
        }
    
        operator SEXP() const {
            return ::Rcpp::wrap(get()) ;
        }
    
    private:
        const VECTOR& parent ;
        std::string name;
        CTYPE get() const {
            return parent.at(name) ;
        }
    } ;

}
}
#endif
