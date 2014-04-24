#ifndef Rcpp__sugar__lapply_h
#define Rcpp__sugar__lapply_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T, typename Function>
        class Lapply : public SugarVectorExpression< 
            VECSXP , 
            true ,
            Lapply<RTYPE,NA,T,Function>
        > {
        public:         
            typedef Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Lapply( const VEC& vec_, Function fun_ ) : 
                vec(vec_), fun(fun_){}
        
            inline SEXP operator[]( int i ) const {
                return Rcpp::wrap( fun( vec[i] ) );
            }
            inline int size() const { return vec.size() ; }
        
        private:
            const VEC& vec ;
            Function fun ;
        } ;
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T, typename Function >
    inline sugar::Lapply<RTYPE,NA,T,Function> 
    lapply( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t, Function fun ){
        return sugar::Lapply<RTYPE,NA,T,Function>( t, fun ) ;
    }

} // Rcpp

#endif
