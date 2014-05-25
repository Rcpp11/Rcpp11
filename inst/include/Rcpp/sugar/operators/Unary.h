#ifndef Rcpp__sugar__Unary_h
#define Rcpp__sugar__Unary_h

namespace Rcpp{
    namespace sugar{
        
        template <int RTYPE, int OUT_RTYPE, bool LHS_NA, typename LHS_T, template <class> class Op >
        class Unary : 
            public SugarVectorExpression<RTYPE, LHS_NA , Unary<RTYPE,OUT_RTYPE,LHS_NA,LHS_T, Op> >,
            public custom_sugar_vector_expression
        {
        public:
            typedef typename traits::storage_type<OUT_RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
            typedef typename Rcpp::unary_op_type<RTYPE,LHS_NA,Op>::type Operator ;
        
            Unary( const LHS_TYPE& lhs_) : lhs(lhs_){}
        
            inline STORAGE operator[]( R_xlen_t i ) const {
                return op(lhs[i]) ;
            }
        
            inline R_xlen_t size() const { return lhs.size() ; }
              
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(lhs), sugar_end(lhs), target.begin(), op ) ;        
            }
            
        private:     
            
            const LHS_TYPE& lhs ;
            Operator op ;
        } ;
        
    }
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Unary<RTYPE, (RTYPE==LGLSXP?INTSXP:RTYPE), NA,T,std::negate>
operator-( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& x ) {
    return Rcpp::sugar::Unary<RTYPE,(RTYPE==LGLSXP?INTSXP:RTYPE),NA,T,std::negate>( x ) ;
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Unary<RTYPE, LGLSXP, NA,T,std::logical_not>
operator!( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& x ) {
    return Rcpp::sugar::Unary<RTYPE,LGLSXP,NA,T,std::logical_not>( x ) ;
}


#endif
