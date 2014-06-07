#ifndef RCPP_VECTOR_MAKE_SUBSETTER_PROXY_H
#define RCPP_VECTOR_MAKE_SUBSETTER_PROXY_H

namespace Rcpp {
    
    template <typename Source, typename Expr>
    struct subset_proxy_type<Source, int, Expr> {
        typedef SubsetProxy<Source,int,Expr> type ;
    } ;
    
    template <typename Source, typename Expr>
    struct subset_proxy_type<Source, String, Expr> {
        typedef SubsetProxy<Source,int,IntegerVector> type ;
    } ;
    
    
    template <
        typename Source, // y
        typename Expr // x
    >
    inline typename subset_proxy_type<Source,int,Expr>::type 
    make_subset_proxy( Source& source, const SugarVectorExpression<int, Expr>& index ){
        return SubsetProxy<Source,int,Expr>( source, index ) ;   
    }
    
    template <
        typename Source, // y
        typename Expr // x
    >
    inline typename subset_proxy_type<Source,String,Expr>::type 
    make_subset_proxy( Source& source, const SugarVectorExpression<String, Expr>& index ){
        auto n = index.size() ;
        IntegerVector ind(n) ;
        SEXP names = source.names() ;
        SEXP* names_it = reinterpret_cast<SEXP*>(DATAPTR(names)) ;
        SEXP* end = names_it + n ;
        for( int i=0; i<n; i++){
            String s = index[i] ;
            auto ix = std::find( names_it, names_it +n, s ) ;
            if( ix == end ) stop( "name not found: '%s' ", s ) ;
            ind[i] = (ix - names_it) ;
        }
        return SubsetProxy<Source,int,IntegerVector>( source, index ) ;   
    }
    
}

#endif
