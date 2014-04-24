#ifndef RCPP_SUGAR_FUNCTIONS_COLLAPSE_H
#define RCPP_SUGAR_FUNCTIONS_COLLAPSE_H

namespace Rcpp{
    namespace sugar {
        template <typename Iterator>
        inline String collapse__impl( Iterator it, int n ){
            static String buffer ;
            buffer = "" ; 
            for( int i=0; i<n; i++ ){
                buffer += it[i] ;    
            }
            return buffer ;
        }        
        
    } // sugar
    
    
    template <bool NA, typename T>
    inline String collapse( const SugarVectorExpression<STRSXP,NA,T>& vec ){
        return sugar::collapse__impl( vec.get_ref().begin(), vec.size() ) ;
    }

}
#endif
