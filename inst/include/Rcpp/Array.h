#ifndef Rcpp__Array__h
#define Rcpp__Array__h

namespace Rcpp{
    
    template <int N, int RTYPE, template <class> class StoragePolicy = PreserveStorage>
    class Array {
    public:
        typedef Vector<RTYPE,StoragePolicy> Vec; 
        typedef typename Vec::Proxy Proxy; 
        typedef typename Vec::const_Proxy const_Proxy ; 
        
        Array( SEXP x ) : index(), data(x) {
          IntegerVector dim = data.attr("dim") ;
          if( dim.size() != N ) stop("incompatible dimensions") ;
          for( int i=0; i<N; i++)
            index[i] = dim[i] ;
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
        const_Proxy operator()( Args... args) const {
            return data[ index.get_index( args... ) ];    
        }
        
        inline operator SEXP() const { return data ; }
        inline operator SEXP(){ return data ; }
        
    private:
        Index<N> index ;
        Vec data ;
    } ;
    
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using NumericArray   = Array<N, REALSXP, StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using DoubleArray    = Array<N, REALSXP, StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using IntegerArray   = Array<N, INTSXP , StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using StringArray    = Array<N, STRSXP , StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using CharacterArray = Array<N, STRSXP , StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using LogicalArray   = Array<N, LGLSXP , StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using RawArray       = Array<N, RAWSXP , StoragePolicy> ;
    // template <int N, template <class> class StoragePolicy = PreserveStorage> using ComplexArray   = Array<N, CPLXSXP, StoragePolicy> ;
    
} // Rcpp 

#endif
