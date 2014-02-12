#ifndef Rcpp__Array__h
#define Rcpp__Array__h

namespace Rcpp{
    
    template <int N, int RTYPE>
    class Array {
    public:
        using Vec = Vector<RTYPE>;
        using Proxy = typename Vec::Proxy; 
        using const_Proxy = typename Vec::Proxy; 
        
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
        Vector<RTYPE> data ;
    } ;
    
    
    template <int N> using NumericArray   = Array<N, REALSXP> ;
    template <int N> using DoubleArray    = Array<N, REALSXP> ;
    template <int N> using IntegerArray   = Array<N, INTSXP> ;
    template <int N> using StringArray    = Array<N, STRSXP> ;
    template <int N> using CharacterArray = Array<N, STRSXP> ;
    template <int N> using LogicalArray   = Array<N, LGLSXP> ;
    template <int N> using RawArray       = Array<N, RAWSXP> ;
    template <int N> using ComplexArray   = Array<N, CPLXSXP> ;
    
} // Rcpp 

#endif
