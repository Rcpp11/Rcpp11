#ifndef Rcpp__sugar__rev_h
#define Rcpp__sugar__rev_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Rev : 
            public SugarVectorExpression<eT, Rev<eT,Expr>>, 
            public custom_sugar_vector_expression {
        public:
            
            class const_iterator {
            public:
                typedef typename Expr::const_iterator source_iterator ;
                const_iterator( source_iterator iter_ ) : iter(iter_){}
                
                inline const_iterator& operator++(){
                    iter-- ;
                    return *this ;    
                }
                
                inline eT operator*(){
                    return *(iter-1) ;  
                }
                
                inline bool operator==( const const_iterator& other ){ return iter == other.iter ; }
                inline bool operator!=( const const_iterator& other ){ return iter != other.iter ; }
                
            private:
                source_iterator iter ;
            } ;
            
            Rev( const SugarVectorExpression<eT,Expr>& object_ ) : 
                object(object_), n(object_.size()) {}
        
            inline R_xlen_t size() const { 
                return n ; 
            }
               
            template <typename Target>
            inline void apply( Target& target ) const {
                auto source_it=sugar_begin(object) ;
                auto it = target.end() ;
                for( R_xlen_t i=0; i<n; i++, ++source_it) { 
                    *(--it) = *source_it ;
                }
            }
            
            inline const_iterator begin() const { return const_iterator( sugar_end(object) ) ; }
            inline const_iterator end() const { return const_iterator( sugar_begin(object) ) ; }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t n ;
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Rev<eT, Expr> rev( const SugarVectorExpression<eT, Expr>& t){
        return sugar::Rev<eT, Expr>( t ) ;
    }

} // Rcpp
#endif

