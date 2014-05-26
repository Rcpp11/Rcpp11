#ifndef Rcpp__sugar__sapply_h
#define Rcpp__sugar__sapply_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T, typename Function>
        class Sapply : public SugarVectorExpression< 
            Rcpp::traits::r_sexptype_traits<
                typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type
            >::rtype , 
            true ,
            Sapply<RTYPE,NA,T,Function>
        >, public custom_sugar_vector_expression {
        public:
            typedef typename std::result_of<Function(typename Rcpp::traits::storage_type<RTYPE>::type)>::type result_type ; 
            const static int RESULT_R_TYPE = 
                Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
        
            typedef Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type STORAGE ;
        
            Sapply( const VEC& vec_, Function fun_ ) : vec(vec_), fun(fun_){}
        
            inline STORAGE operator[]( R_xlen_t i ) const {
                return fun( vec[i] ) ;
            }
            inline R_xlen_t size() const { return vec.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(vec), sugar_end(vec), target.begin(), fun ) ;     
            }
            
        private:
            const VEC& vec ;
            Function fun ;
        
        } ;
    
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T, typename Function >
    inline sugar::Sapply<RTYPE,NA,T,Function> 
    sapply( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t, Function fun ){
        return sugar::Sapply<RTYPE,NA,T,Function>( t, fun ) ;
    }

} // Rcpp

#endif
