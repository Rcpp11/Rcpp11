#ifndef Rcpp__vector__LazyVector_h
#define Rcpp__vector__LazyVector_h

namespace Rcpp{
            
    template <int RTYPE>
    struct LazyVectorOf {};
    
    template <int RTYPE, typename Expr>
    struct LazyVector : public LazyVectorOf<RTYPE>, public CRTP<Expr> {
        using CRTP<Expr>::get_ref ;
    
        inline int size() const { 
            return get_ref().size() ;
        }
    
        template <typename Target>
        void apply( Target& target ) const {
            get_ref().apply(target) ;
        }
        
    } ;
    
}

#endif
