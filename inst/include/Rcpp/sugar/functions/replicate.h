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
            public custom_sugar_vector_expression
        {
        public:
            typedef typename std::result_of<CallType()>::type value_type ;
            typedef replicate_iterator<value_type, CallType> const_iterator ;
            
            Replicate( R_xlen_t n_, CallType call_ ): n(n_), call(call_) {}
            
            inline R_xlen_t size() const { return n ; }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                std::generate_n( target.begin(), n, call ) ;  
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                parallel::generate_n(nthreads, target.begin(), n, call) ;    
            }
            
            inline const_iterator begin() const { return const_iterator( call, 0 ) ; }
            inline const_iterator end() const { return const_iterator( call, size() ) ; }
            
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

