#ifndef Rcpp__Index__h
#define Rcpp__Index__h

namespace Rcpp{
    
    template <int N, typename... Args>
    constexpr bool ValidIndexArgs() {
        return traits::and_<std::is_convertible<Args, int>...>::value && (N == sizeof...(Args) ) ;   
    }
    
    template <int N>
    class Index {
    public:
    
        Index(){}
        
        template <
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type 
        >
        Index( Args... args ) : dimensions({{ static_cast<size_t>(args)... }}) {}
        
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        size_t operator()( Args... args){
            return get_index( args... ) ;    
        }
    
        inline size_t prod(){
            return std::accumulate( dimensions.begin(), dimensions.end(), 1, std::multiplies<double>() ) ;     
        }
        inline size_t size(){ 
            return N ;
        }
        
        inline operator SEXP() const { return wrap( dimensions ); }
        inline operator SEXP() { return wrap( dimensions ); }
        
        inline size_t& operator[](int i){
            return dimensions[i] ;
        }
        
        inline typename std::array<size_t,N>::iterator begin(){ return dimensions.begin() ; }
        
    private:
        
        template <typename... Args >
        size_t get_index( size_t first, Args... args){
            return first + dimensions[ N - sizeof...(Args) - 1 ] * get_index( args... );
        }
        
        size_t get_index( size_t first ){
            return first ;
        }
        
        std::array<int,N> dimensions ;
        
    } ;
     
    
} // Rcpp 

#endif
