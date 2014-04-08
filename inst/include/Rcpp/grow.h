#ifndef Rcpp_grow_h
#define Rcpp_grow_h

namespace Rcpp {

    inline SEXP grow( SEXP head, SEXP tail ){
        Shield<SEXP> x = head ;
        Shield<SEXP> res = Rf_cons( x, tail ) ;
        return res ;    
    }
    
    namespace internal{
     
        template <typename T>
        inline SEXP grow__dispatch( std::false_type, const T& head, SEXP tail ){
            return grow( wrap(head), tail ) ;
        }
        
        template <typename T>
        inline SEXP grow__dispatch( std::true_type, const T& head, SEXP tail ){
            Shield<SEXP> y = wrap( head.object) ;
            Shield<SEXP> x = Rf_cons( y , tail) ;
            SET_TAG( x, head.name ); 
            return x; 
        }
    
    } // internal

    /**
     * grows a pairlist. First wrap the head into a SEXP, then 
     * grow the tail pairlist
     */
    template <typename T>
    SEXP grow(const T& head, SEXP tail) {
        return internal::grow__dispatch( typename traits::is_named<T>::type(), head, tail );
    }
    
    template <typename... Args>
    struct PairlistHelper ;
    
    template <typename First, typename... Args>
    struct PairlistHelper<First, Args...>{
        static inline SEXP get(const First& first, const Args&... pack){
            return grow( first, PairlistHelper<Args...>::get( pack... ) ) ; 
        }
    } ;
    
    template <>
    struct PairlistHelper<>{
        static inline SEXP get(){ return R_NilValue; }
    } ;
    
    
    template <typename... Args>
    inline SEXP pairlist( const Args&... args ){
        return PairlistHelper<Args...>::get( args... ) ;    
    }
    template <typename... Args>
    inline SEXP language( const Args&... args ){
        Shield<SEXP> call = pairlist( args... ) ;
        SET_TAG(call, R_NilValue);
        SET_TYPEOF(call, LANGSXP) ;
        return call ;
    }
    

} // namespace Rcpp

#endif
