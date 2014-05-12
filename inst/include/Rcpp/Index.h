#ifndef Rcpp__Index__h
#define Rcpp__Index__h

namespace Rcpp{
    
    template <int N, typename... Args>
    constexpr bool ValidIndexArgs() {
        return traits::and_<std::is_convertible<Args, size_t>...>::value && (N == sizeof...(Args) ) ;   
    }
    
    template <int N>
    class Index {
    public:
    
        Index(){}
        
        template <
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type 
        >
        Index( Args... args ) {
            set_dim(args...) ;    
        }
        
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        size_t operator()( Args... args){
            return get_index( args... ) ;    
        }
    
        inline size_t prod(){
            return std::accumulate( begin(dimensions), end(dimensions), 1, std::multiplies<double>() ) ;     
        }
        inline size_t size(){ 
            return N ;
        }
        
        inline operator SEXP() const { return wrap( dimensions ); }
        inline operator SEXP() { return wrap( dimensions ); }
        
        inline size_t& operator[](int i){
          return dimensions[i] ;
        }
        
    private:
        
        template <typename... Args >
        size_t get_index( size_t first, Args... args){
            return first + dimensions[ N - sizeof...(Args) - 1 ] * get_index( args... );
        }
        
        size_t get_index( size_t first ){
            return first ;
        }
        
        template <typename First, typename... Args>
        void set_dim( First first, Args... args) {
            dimensions[N-1-sizeof...(Args)] = static_cast<size_t>(first) ;
            set_dim(args...) ;
        }
        
        void set_dim( size_t first ){
            dimensions[N-1] = first ;    
        }
        
        std::array<size_t,N> dimensions ;
        
    } ;
     
    
} // Rcpp 

#endif
