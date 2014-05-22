#ifndef Rcpp__Array__h
#define Rcpp__Array__h

namespace Rcpp{
    
    template <int N, int RTYPE, typename Storage = PreserveStorage>
    class Array {
    public:
        typedef Vector<RTYPE,Storage> Vec; 
        typedef typename Vec::Proxy Proxy;
        
        Array( SEXP x ) : index(), data(x) {
            IntegerVector dim = data.attr("dim") ;
            if( dim.size() != N ) stop("incompatible dimensions") ;
            std::copy( dim.begin(), dim.end(), index.begin() ) ;
        }
        
        template <
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type 
        >
        Array( Args... args ) : 
            index({ static_cast<size_t>(args)... }), 
            data(index.prod())
        {
            data.attr("dim") = index ;    
        }
        
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        Proxy operator()( Args&&... args){
            return data[ index( std::forward<Args>(args)... ) ];    
        }
        
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        const Proxy operator()( Args... args) const {
            return data[ index.get_index( args... ) ];    
        }
        
        inline operator SEXP() const { return data ; }
        inline operator SEXP(){ return data ; }
        
        template <typename T>
        Array& fill( T value ){
            std::fill( data.begin(), data.end(), value ) ;
            return *this ;
        }
        
    private:
        Index<N> index ;
        Vec data ;
        
    } ;
    
    // template <int N, typename Storage = PreserveStorage> using NumericArray   = Array<N, REALSXP, Storage> ;
    // template <int N, typename Storage = PreserveStorage> using DoubleArray    = Array<N, REALSXP, Storage> ;
    // template <int N, typename Storage = PreserveStorage> using IntegerArray   = Array<N, INTSXP , Storage> ;
    // template <int N, typename Storage = PreserveStorage> using StringArray    = Array<N, STRSXP , Storage> ;
    // template <int N, typename Storage = PreserveStorage> using CharacterArray = Array<N, STRSXP , Storage> ;
    // template <int N, typename Storage = PreserveStorage> using LogicalArray   = Array<N, LGLSXP , Storage> ;
    // template <int N, typename Storage = PreserveStorage> using RawArray       = Array<N, RAWSXP , Storage> ;
    // template <int N, typename Storage = PreserveStorage> using ComplexArray   = Array<N, CPLXSXP, Storage> ;
    
} // Rcpp 

#endif
