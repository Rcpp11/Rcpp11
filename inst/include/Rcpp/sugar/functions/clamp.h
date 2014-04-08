#ifndef Rcpp__sugar__clamp_h
#define Rcpp__sugar__clamp_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA>
        struct clamp_operator{
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
            clamp_operator(STORAGE lhs_, STORAGE rhs_ ) : lhs(lhs_), rhs(rhs_){}
            
            inline STORAGE operator()(STORAGE x) const {
                return x < lhs ? lhs : (x > rhs ? rhs : x ) ;
            }
            STORAGE lhs, rhs ;    
        } ;
        // need to write this special version
        template <>
        struct clamp_operator<REALSXP,true> {
            clamp_operator(double lhs_, double rhs_ ) : lhs(lhs_), rhs(rhs_){}
            
            inline double operator()(double x) const {
                if( Rcpp::traits::is_na<REALSXP>(x) )  return x ;
                return x < lhs ? lhs : (x > rhs ? rhs : x ) ;
            }
            double lhs, rhs ;    
        } ;
        
        
        
        template <
            int RTYPE, 
            bool NA, typename T
            >
        class Clamp_Primitive_Vector_Primitive : public SugarVectorExpression< 
            RTYPE , 
            NA ,
            Clamp_Primitive_Vector_Primitive<RTYPE,NA,T>
        > {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            typedef clamp_operator<RTYPE,NA> OPERATOR ;
        
            Clamp_Primitive_Vector_Primitive( STORAGE lhs_, const T& vec_, STORAGE rhs_) : vec(vec_), op(lhs_,rhs_) {}
        
            inline STORAGE operator[]( int i ) const {
                return op( vec[i] ) ;
            }
            inline int size() const { return vec.size() ; }
        
        private:
            const T& vec ;
            OPERATOR op ; 
        } ;



    } // sugar

    template <int RTYPE, bool NA, typename T>
    inline sugar::Clamp_Primitive_Vector_Primitive<RTYPE,NA,T> 
    clamp( 
        typename Rcpp::traits::storage_type<RTYPE>::type lhs,
        const Rcpp::VectorBase<RTYPE,NA,T>& vec,  
        typename Rcpp::traits::storage_type<RTYPE>::type rhs
        ){
        return sugar::Clamp_Primitive_Vector_Primitive<RTYPE,NA,T>( lhs, vec.get_ref(), rhs ) ;
    }


} // Rcpp

#endif
