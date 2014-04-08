#ifndef Rcpp__vector__string_name_proxy_h
#define Rcpp__vector__string_name_proxy_h

namespace Rcpp{
namespace internal{

    template <int RTYPE>
    class string_name_proxy : public name_proxy<RTYPE,Vector<RTYPE>> {
    public:
        using name_proxy<RTYPE,Vector<RTYPE>>::set ;
        
        typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
        
        string_name_proxy( VECTOR& v, std::string  name_) :
            parent(v), name(std::move(name_)){}
        string_name_proxy( const string_name_proxy& other ) : 
            parent(other.parent), name(other.name){}
        ~string_name_proxy(){}
    
        string_name_proxy& operator=( const std::string& rhs ){
            set( Rf_mkChar(rhs.c_str()) ) ;
            return *this ;
        }
        string_name_proxy& operator=( const string_name_proxy& other){
            set( Rf_mkChar( other.get() ) ) ;
            return *this ;
        }
        string_name_proxy& operator=( const Na_Proxy& /* other */){
            set( Rcpp::traits::get_na<RTYPE>() );
            return *this ;
        }
    
        operator char* (){
             return get() ;
        }
    
        operator SEXP(){
            return Rf_mkString(get()) ;
        }
    
        inline int size(){ return strlen( get() ) ; }
    
    private:
        VECTOR& parent ;
        std::string name;
    
        void set( SEXP rhs ){
            set( parent, name, rhs) ;
        }
    
        char* get(){
            return parent[ parent.offset(name) ];
        }
    
    } ;

}
}
#endif
