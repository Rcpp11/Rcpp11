#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T>
        class Rev : 
            public SugarVectorExpression< RTYPE ,NA, Rev<RTYPE,NA,T> >, 
            public custom_sugar_vector_expression {
        public:
            typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
            Rev( const VEC_TYPE& object_ ) : 
                object(object_), n(object_.size()) {}
        
            inline STORAGE operator[]( int i ) const {
                return object[n - i - 1] ;
            }
            inline int size() const { return n ; }
               
            template <typename Target>
            inline void apply( Target& target ) const {
                auto source_it=sugar_begin(object) ;
                auto it = target.end() ;
                for( int i=0; i<n; i++, ++source_it) { 
                    *(--it) = *source_it ;
                }
            }
            
        private:
            const VEC_TYPE& object ;
            int n ;
        } ;
    
    } // sugar
    
    template <int RTYPE,bool NA, typename T>
    inline sugar::Rev<RTYPE,NA,T> rev( const VectorBase<RTYPE,NA,T>& t){
        return sugar::Rev<RTYPE,NA,T>( t ) ;
    }

} // Rcpp
#endif

