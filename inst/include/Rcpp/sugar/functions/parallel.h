#ifndef Rcpp__sugar__parallel_h
#define Rcpp__sugar__parallel_h

namespace Rcpp{

    namespace sugar{
        
        template <typename eT, typename Expr>
        class Parallel : 
            public SugarVectorExpression<eT, Parallel<eT,Expr>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Expr::const_iterator const_iterator ;
            
            Parallel( const SugarVectorExpression<eT,Expr>& data_): 
                data(data_){}
            
            inline R_xlen_t size() const { 
                return data.size(); 
            }
           
            template <typename Target>
            inline void apply( Target& target ) const {
                data.apply_parallel( target ) ;     
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                data.apply_parallel( target ) ;     
            }
           
            inline const_iterator begin() const { return data.get_ref().begin(); }
            inline const_iterator end() const { return data.get_ref().end(); }
            
        private:
            const SugarVectorExpression<eT,Expr>& data ; 
            
        } ;
    
        struct Threads{} ;
        
    }
    
    template <typename eT, typename Expr>
    inline sugar::Parallel<eT,Expr> threaded( const SugarVectorExpression<eT,Expr>& expr ){
        return sugar::Parallel<eT,Expr>( expr );   
    }
    
    template <typename eT, typename Expr>
    inline sugar::Parallel<eT,Expr> operator>>( sugar::Threads threads, const SugarVectorExpression<eT,Expr>& expr ){
        return threaded( expr ) ;    
    }
        
    inline sugar::Threads threads(){ return sugar::Threads(); }
    
}

#endif
