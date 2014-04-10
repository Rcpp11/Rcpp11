#ifndef RCPP_SUGAR_VECTORIZEDMATH_H
#define RCPP_SUGAR_VECTORIZEDMATH_H

namespace Rcpp{
    namespace sugar{
    
        extern "C" typedef double (*DDFun)(double);
        
        template <DDFun Func, bool HAS_NA, typename VEC>
        class Vectorized : 
            public SugarVectorExpression<REALSXP, HAS_NA, Vectorized<Func,HAS_NA,VEC> >, 
            public custom_sugar_vector_expression {
        public:
            typedef typename Rcpp::VectorBase<REALSXP,HAS_NA,VEC> VEC_TYPE ;
                
            Vectorized( const VEC_TYPE& object_) : object( object_.get_ref() ){}
            inline double operator[]( int i) const {
                return Func( object[i] ) ;
            }
            inline int size() const { return object.size(); }
               
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(object), sugar_end(object), target.begin(), Func );    
            }
            
        private:
            const VEC_TYPE& object ;     
        } ;
        
        template <DDFun Func, bool HAS_NA, typename VEC>
        class Vectorized_INTSXP : 
            public SugarVectorExpression<REALSXP, HAS_NA, Vectorized_INTSXP<Func,HAS_NA,VEC> >, 
            public custom_sugar_vector_expression {
        public:
            typedef typename Rcpp::VectorBase<INTSXP,HAS_NA,VEC> VEC_TYPE ;
                
            Vectorized_INTSXP( const VEC_TYPE& object_) : object( object_.get_ref() ){}
            inline double operator[]( int i) const {
                int x = object[i] ;
                if( x == NA_INTEGER ) return NA_REAL ;
                return Func( x ) ;
            }
            inline int size() const { return object.size(); }
                
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(object), sugar_end(object), target.begin(), [](int x) -> double{
                    if( x == NA ) return NA ;
                    return Func( x ) ;
                });    
            }
        private:
            const VEC_TYPE& object ;     
        } ;
        
        template <DDFun Func, typename VEC>
        class Vectorized_INTSXP<Func,false,VEC> : 
            public SugarVectorExpression<REALSXP,false, Vectorized_INTSXP<Func,false,VEC> >, 
            public custom_sugar_vector_expression{
        public:
            typedef typename Rcpp::VectorBase<INTSXP,false,VEC> VEC_TYPE ;
                
            Vectorized_INTSXP( const VEC_TYPE& object_) : object( object_.get_ref() ){}
            inline double operator[]( int i) const {
                return Func( object[i] ) ;
            }
            inline int size() const { return object.size(); }
              
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(object), sugar_end(object), target.begin(), Func );    
            }
            
        private:
            const VEC_TYPE& object ;     
        } ;
    
    } // sugar
} // Rcpp

#define VECTORIZED_MATH_1(__NAME__,__SYMBOL__)                               \
namespace Rcpp{                                                              \
        template <bool NA, typename T>                                           \
        inline sugar::Vectorized<__SYMBOL__,NA,T>                                \
        __NAME__( const VectorBase<REALSXP,NA,T>& t ){                           \
                return sugar::Vectorized<__SYMBOL__,NA,T>( t ) ;                     \
        }                                                                        \
        inline sugar::Vectorized<__SYMBOL__,true,NumericVector>                  \
        __NAME__( SEXP x){ return __NAME__( NumericVector( x ) ) ; }             \
        template <bool NA, typename T>                                           \
        inline sugar::Vectorized_INTSXP<__SYMBOL__,NA,T>                         \
        __NAME__( const VectorBase<INTSXP,NA,T>& t      ){                           \
                return sugar::Vectorized_INTSXP<__SYMBOL__,NA,T>( t ) ;              \
        }                                                                        \
}


#endif
