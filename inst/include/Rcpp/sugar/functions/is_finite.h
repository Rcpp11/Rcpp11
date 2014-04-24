#ifndef Rcpp__sugar__is_finite_h
#define Rcpp__sugar__is_finite_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename VEC_TYPE>
        class IsFinite : 
            public SugarVectorExpression< LGLSXP, false, IsFinite<RTYPE,NA,VEC_TYPE> >, 
            public custom_sugar_vector_expression {
        public:
        
            IsFinite( const SugarVectorExpression<RTYPE,NA,VEC_TYPE>& obj_) : obj(obj_){}
        
            inline int operator[]( int i ) const {
                return ::Rcpp::traits::is_finite<RTYPE>( obj[i] ) ;
            }
        
            inline int size() const { return obj.size() ; }
                
            template <typename Target>
            inline void apply( Target& target ) const {
                std::transform( sugar_begin(obj), sugar_end(obj), target.begin(), ::Rcpp::traits::is_finite<RTYPE> );  
            }       
            
        private:
            const SugarVectorExpression<RTYPE,NA,VEC_TYPE>& obj ;
        
        } ;
    
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    inline sugar::IsFinite<RTYPE,NA,T> is_finite( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t){
        return sugar::IsFinite<RTYPE,NA,T>( t ) ;
    }

} // Rcpp
#endif

