#ifndef Rcpp__sugar__is_nan_h
#define Rcpp__sugar__is_nan_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename VEC_TYPE>
        class IsNaN : 
            public SugarVectorExpression< LGLSXP, false, IsNaN<RTYPE,NA,VEC_TYPE> >, 
            public custom_sugar_vector_expression {
        public:      
            typedef Rcpp::VectorBase<RTYPE,NA,VEC_TYPE> Base ;
            
            IsNaN( const Base& obj_) : obj(obj_){}
        
            inline int operator[]( int i ) const {
                return ::Rcpp::traits::is_nan<RTYPE>( obj[i] ) ;
            }
        
            inline int size() const { return obj.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {            
                std::transform( sugar_begin(obj), sugar_end(obj), target.begin(), Rcpp::traits::is_nan<RTYPE> );     
            }       
            
        private:
            const Base& obj ;
        
        } ;
    
    
    } // sugar
    
    template <int RTYPE, bool NA, typename T>
    inline sugar::IsNaN<RTYPE,NA,T> is_nan( const Rcpp::VectorBase<RTYPE,NA,T>& t){
        return sugar::IsNaN<RTYPE,NA,T>( t ) ;
    }

} // Rcpp
#endif

