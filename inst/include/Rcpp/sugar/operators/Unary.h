#ifndef Rcpp__sugar__Unary_h
#define Rcpp__sugar__Unary_h

namespace Rcpp{
    namespace sugar{
        
        template <int RTYPE, int OUT_RTYPE, bool LHS_NA, typename LHS_T, template <class> class Op >
        class Unary : 
            public SugarVectorExpression<RTYPE, LHS_NA , Unary<RTYPE,OUT_RTYPE,LHS_NA,LHS_T, Op> >
            {
        public:
            typedef typename traits::storage_type<OUT_RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
            typedef typename Rcpp::unary_op_type<RTYPE,LHS_NA,Op>::type Operator ;
        
            Unary( const LHS_TYPE& lhs_) : lhs(lhs_){}
        
            inline STORAGE operator[]( int i ) const {
                return op(lhs[i]) ;
            }
        
            inline int size() const { return lhs.size() ; }
              
            
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
