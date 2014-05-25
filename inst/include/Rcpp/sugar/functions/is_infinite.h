#ifndef Rcpp__sugar__is_infinite_h
#define Rcpp__sugar__is_infinite_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename VEC_TYPE>
        class IsInfinite : 
            public SugarVectorExpression< LGLSXP, false, IsInfinite<RTYPE,NA,VEC_TYPE> >, 
            public custom_sugar_vector_expression {
        public:
        
            IsInfinite( const SugarVectorExpression<RTYPE,NA,VEC_TYPE>& obj_) : obj(obj_){}
        
            inline int operator[]( R_xlen_t i ) const {
                return ::Rcpp::traits::is_infinite<RTYPE>( obj[i] ) ;
            }
        
            inline R_xlen_t size() const { return obj.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(obj), sugar_end(obj), target.begin(), ::Rcpp::traits::is_infinite<RTYPE> );  
            }
            
        private:
            const SugarVectorExpression<RTYPE,NA,VEC_TYPE>& obj ;
        
        } ;
    
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    inline sugar::IsInfinite<RTYPE,NA,T> is_infinite( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t){
        return sugar::IsInfinite<RTYPE,NA,T>( t ) ;
    }

} // Rcpp
#endif

