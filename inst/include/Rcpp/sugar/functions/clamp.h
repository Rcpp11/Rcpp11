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
        
        
        
        template <int RTYPE, bool NA, typename T>
        class Clamp_Primitive_Vector_Primitive : public SugarVectorExpression< 
            RTYPE , 
            NA ,
            Clamp_Primitive_Vector_Primitive<RTYPE,NA,T>
        >, public custom_sugar_vector_expression {
        public:
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            typedef clamp_operator<RTYPE,NA> OPERATOR ;
             
            Clamp_Primitive_Vector_Primitive( STORAGE lhs_, const T& vec_, STORAGE rhs_) : vec(vec_), op(lhs_,rhs_) {}
        
            inline STORAGE operator[]( R_xlen_t i ) const {
                return op( vec[i] ) ;
            }
            inline int size() const { return vec.size() ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                return apply_impl(target, typename traits::is_materialized<T>::type() ) ;    
            }
            
        private:
            const T& vec ;
            OPERATOR op ;
            
            template <typename Target>
            inline void apply_impl(Target& target, std::true_type) const {
                std::transform( vec.begin(), vec.end(), target.begin(), op ) ;        
            }
            
            template <typename Target>
            inline void apply_impl(Target& target, std::false_type) const {
                int n=size();
                auto it = target.begin() ;
                for(int i=0; i<n; i++, ++it){
                    *it = op(vec[i]) ;
                }
            }
            
        } ;



    } // sugar

    template <int RTYPE, bool NA, typename T>
    inline sugar::Clamp_Primitive_Vector_Primitive<RTYPE,NA,T> 
    clamp( 
        typename Rcpp::traits::storage_type<RTYPE>::type lhs,
        const Rcpp::SugarVectorExpression<RTYPE,NA,T>& vec,  
        typename Rcpp::traits::storage_type<RTYPE>::type rhs
        ){
        return sugar::Clamp_Primitive_Vector_Primitive<RTYPE,NA,T>( lhs, vec.get_ref(), rhs ) ;
    }


} // Rcpp

#endif
