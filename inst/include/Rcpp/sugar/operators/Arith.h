#ifndef Rcpp__sugar__Arith_h
#define Rcpp__sugar__Arith_h

namespace Rcpp{
    namespace sugar{
        
        template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T, template <class> class Op >
        class Arith_Vector_Vector : 
            public SugarVectorExpression<RTYPE, LHS_NA || RHS_NA , Arith_Vector_Vector<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T, Op> >
            {
        public:
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
            typedef typename Rcpp::arith_op_type<RTYPE,LHS_NA,RHS_NA,Op>::type Operator ;
        
            Arith_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline STORAGE operator[]( int i ) const {
                return op(lhs[i], rhs[i]) ;
            }
        
            inline int size() const { return lhs.size() ; }
              
            
        private:     
            
            const LHS_TYPE& lhs ;
            const RHS_TYPE& rhs ;
            Operator op ;
        } ;
        
        template <int RTYPE, bool LHS_NA, typename LHS_T, template <class> class Op >
        class Arith_Vector_Primitive : 
            public SugarVectorExpression<RTYPE, true , Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, Op> >
            {
        public:
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
            typedef typename Rcpp::arith_op_type<RTYPE,LHS_NA,true,Op>::type Operator ;
        
            Arith_Vector_Primitive( const LHS_TYPE& lhs_, STORAGE rhs_ ) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline STORAGE operator[]( int i ) const {
                return op(lhs[i], rhs) ;
            }
        
            inline int size() const { return lhs.size() ; }
              
            
        private:     
            
            const LHS_TYPE& lhs ;
            STORAGE rhs ;
            Operator op ;
        } ;
        
        template <int RTYPE, bool RHS_NA, typename RHS_T, template <class> class Op >
        class Arith_Primitive_Vector : 
            public SugarVectorExpression<RTYPE, true , Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, Op> >
            {
        public:
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
            typedef typename Rcpp::arith_op_type<RTYPE,true,RHS_NA,Op>::type Operator ;
        
            Arith_Primitive_Vector( STORAGE lhs_, const RHS_TYPE& rhs_ ) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline STORAGE operator[]( int i ) const {
                return op(lhs, rhs[i]) ;
            }
        
            inline int size() const { return rhs.size() ; }
              
            
        private:     
            
            STORAGE lhs ;
            const RHS_TYPE& rhs ;
            Operator op ;
        } ;
        
        
    }
}

#endif
