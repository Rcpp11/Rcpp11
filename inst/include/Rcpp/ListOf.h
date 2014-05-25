#ifndef Rcpp__vector__impl_ListOf_h
#define Rcpp__vector__impl_ListOf_h

namespace Rcpp{
       
    template <typename T, typename Storage = PreserveStorage>
    class ListOf {
    public:
        typedef Vector<VECSXP, Storage> List ;
        
        ListOf( SEXP x ) {
            set(x) ;
        }
        ListOf& operator=( SEXP x){
            set(x) ;
            return *this ;
        }
        inline operator SEXP() const {
            return data ;    
        }
        
        ListOf( R_xlen_t n, const T& obj ) : data(n, obj) {}
        
        ListOf( std::initializer_list<T> list ) : data(list.size()) {
            std::copy( list.begin(), list.end(), data.begin() );    
        }
        
        class Proxy : public GenericProxy<Proxy> {
        public:
            Proxy( R_xlen_t i_ ) : i(i_){}
            
            inline operator T() const {
                return as<T>( data[i] ) ;    
            }
            
            inline Proxy& operator=( const T& rhs ){
                data[i] = rhs ;    
            }
            
        private:
            R_xlen_t i ;
        } ;
        
        Proxy operator[](R_xlen_t i){
            return Proxy( i ) ;    
        }
        
        const Proxy operator[]( R_xlen_t i) const {
            return Proxy( i );    
        }
        
        inline R_xlen_t size() const { return data.size(); }
        
        std::vector<T> force() const {
            std::vector<T> v ;
            v.reserve( size() );
            std::for_each( data.begin(), data.end(), [&v](SEXP x) {
                    v.push_back( as<T>(x) ) ;
            }) ;
            return v ;
        }
        
    private:
        List data ;
        
        void set(SEXP x){
            List tmp(x) ;
            if( !std::all_of( tmp.begin(), tmp.end(), is<T> ) ) {
                stop( "list contains data not compatible with specified type in ListOf<%s>", DEMANGLE(T) ) ;        
            }
            data = std::move(tmp) ;
        }
        
    } ;
    
    #undef VEC  
}
#endif
