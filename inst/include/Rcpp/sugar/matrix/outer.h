#ifndef Rcpp__sugar__outer_h
#define Rcpp__sugar__outer_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, typename Function, typename STORAGE>
        class Outer : public SugarMatrixExpression< 
            Rcpp::traits::r_sexptype_traits<
                typename std::result_of<Function(STORAGE,STORAGE)>::type
            >::rtype , 
            true ,
            Outer<RTYPE,Function,STORAGE>  
        > {
        public:
            typedef Vector<RTYPE> Vec ;
            typedef typename std::result_of<Function(STORAGE,STORAGE)>::type result_type ;
            const static int RESULT_R_TYPE = Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
            
            typedef typename Rcpp::traits::r_vector_element_converter<RESULT_R_TYPE>::type converter_type ;
            typedef typename Rcpp::traits::storage_type<RESULT_R_TYPE>::type OUT_STORAGE ;
        
            Outer( Vec lhs_, Vec rhs_, Function fun_ ) : 
                lhs(lhs_), rhs(rhs_), fun(fun_), nr(lhs.size()), nc(rhs.size()) {}
        
            inline OUT_STORAGE operator()( int i, int j ) const {
                return converter_type::get( fun( lhs[i], rhs[j] ) );
            }
        
            inline int size() const { return nr * nc ; }
            inline int nrow() const { return nr; }
            inline int ncol() const { return nc; }
        
        private:
        
            Vector<RTYPE> lhs, rhs ;
        
            Function fun ;
            int nr, nc ;
        } ;
    
    } // sugar
    
    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T, typename Function >
    sugar::Outer<RTYPE,Function, typename traits::storage_type<RTYPE>::type >
    outer( const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs, const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs, Function fun ){
        return sugar::Outer<RTYPE,Function, typename traits::storage_type<RTYPE>::type >( 
            Vector<RTYPE>(lhs.get_ref()), 
            Vector<RTYPE>(rhs.get_ref()),
            fun ) ;
    }

} // Rcpp

#endif
