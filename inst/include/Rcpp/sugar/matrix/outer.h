#ifndef Rcpp__sugar__outer_h
#define Rcpp__sugar__outer_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr1, typename Expr2, typename Function>
        class Outer : public SugarMatrixExpression<Outer<Expr1, Expr2, Function>> {
        public:
            typedef typename Expr1::value_type STORAGE ;
            typedef typename traits::vector_of<input_value_type> Vec ;
            
            typedef typename std::result_of<Function(STORAGE,STORAGE)>::type result_type ;
            const static int RESULT_R_TYPE = Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
            
            typedef typename Rcpp::traits::r_vector_element_converter<RESULT_R_TYPE>::type converter_type ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type value_type ;
        
            Outer( Vec lhs_, Vec rhs_, Function fun_ ) : 
                lhs(lhs_), rhs(rhs_), fun(fun_), nr(lhs.size()), nc(rhs.size()) {}
        
            inline value_type operator()( int i, int j ) const {
                return converter_type::get( fun( lhs[i], rhs[j] ) );
            }
        
            inline R_xlen_t size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
        private:
        
            Vec lhs, rhs ;
        
            Function fun ;
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <typename Expr1, typename Expr2, typename Function>
    typename std::enable_if<
        std::same< typename Expr1::value_type, typename Expr2::value_type >::value,
        sugar::Outer<Expr1, Expr2, Function>
    >::type
    outer( const Rcpp::SugarVectorExpression<Expr1>& lhs, const Rcpp::SugarVectorExpression<Expr2>& rhs, Function fun ){
        return sugar::Outer<Expr1, Expr2, Function>(lhs, rhs, fun ) ;
    }

} // Rcpp

#endif
