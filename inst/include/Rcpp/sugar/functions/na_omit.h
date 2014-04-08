#ifndef Rcpp__sugar__na_omit_h
#define Rcpp__sugar__na_omit_h

namespace Rcpp{
namespace sugar{
     
    template <int RTYPE, bool NA, typename T>
    Vector<RTYPE> na_omit_impl(const T& x, std::false_type ) {
        int n = x.size() ;
        int n_out = n - sum( is_na(x) ) ;
    
        Vector<RTYPE> out(n_out) ;
        for( int i=0, j=0; i<n; i++){
            if( Vector<RTYPE>::is_na( x[i] ) ) continue ;
            out[j++] = x[i];
        }
        return out ;
    }  

    template <int RTYPE, bool NA, typename T>
    Vector<RTYPE> na_omit_impl(const T& x, std::true_type ) {
        int n = x.size() ;
        int n_out = n - sum( is_na(x) ) ;
    
        Vector<RTYPE> out(n_out) ;
        bool has_name = x.attr("names") != R_NilValue ;
        if( has_name ){
            CharacterVector names = x.attr("names") ;
            CharacterVector onames( n_out ) ;
            
            for( int i=0, j=0; i<n; i++){
                if( Vector<RTYPE>::is_na( x[i] ) ) continue ;
                onames[j] = names[i] ;
                out[j++] = x[i];
            }
            out.attr("names") = onames ;
        } else {
            for( int i=0, j=0; i<n; i++){
                if( Vector<RTYPE>::is_na( x[i] ) ) continue ;
                out[j++] = x[i];
            }
        }
        return out ;
    }  
    
} // sugar

template <int RTYPE, bool NA, typename T>
inline Vector<RTYPE> na_omit( const VectorBase<RTYPE,NA,T>& t){
    return sugar::na_omit_impl<RTYPE,NA,T>( 
        t.get_ref(), 
        typename std::is_same<T,Vector<RTYPE> >::type()
    ) ;
}

} // Rcpp
#endif

