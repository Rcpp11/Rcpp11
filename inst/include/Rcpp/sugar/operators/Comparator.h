#ifndef Rcpp__sugar__Comparator_h
#define Rcpp__sugar__Comparator_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T, template <class> class Op >
        class Comparator : 
            public SugarVectorExpression< LGLSXP, LHS_NA || RHS_NA , Comparator<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T, Op> > {
        
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
            
            typedef typename Rcpp::comp_op_type<RTYPE,LHS_NA,RHS_NA,Op>::type Operator ;
        
            Comparator( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline int operator[]( int i ) const {
                return op( lhs[i], rhs[i] );
            }
        
            inline int size() const { return lhs.size() ; }
        
        private:
            const LHS_TYPE& lhs ;
            const RHS_TYPE& rhs ;
            Operator op ;
        
        } ;
        
    
    }
}


#endif
