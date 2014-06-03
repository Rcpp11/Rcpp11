#ifndef Rcpp__sugar__replicate_h
#define Rcpp__sugar__replicate_h

namespace Rcpp{
    namespace sugar{
    
        template <typename CallType>
        class Replicate : 
            public SugarVectorExpression<
                typename std::result_of<CallType()>::type, 
                Replicate<CallType> 
            >, 
            public custom_sugar_vector_expression {
        public:
            typedef typename std::result_of<CallType()>::type value_type ;
            Replicate( R_xlen_t n_, CallType call_ ): n(n_), call(call_) {}
            
            inline value_type operator[]( R_xlen_t i ) const {
                return call() ;
            }
            inline R_xlen_t size() const { return n ; }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                std::generate_n( target.begin(), n, call ) ;  
            }
            
        private:
            R_xlen_t n ;
            CallType call ; 
        } ;
    
    
    } // sugar
    
    template <typename CallType>
    inline sugar::Replicate<CallType> 
    replicate( R_xlen_t n, CallType call){
        return sugar::Replicate<CallType>( n, call ) ;    
    }



} // Rcpp
#endif

