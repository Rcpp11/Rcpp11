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
            
            Parallel( const SugarVectorExpression<eT,Expr>& data_, int nthreads_ ): 
                data(data_), nthreads(nthreads_){}
            
            inline R_xlen_t size() const { 
                return data.size(); 
            }
           
            template <typename Target>
            inline void apply( Target& target ) const {
                data.apply_parallel( target, nthreads ) ;     
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                data.apply_parallel( target, nthreads ) ;     
            }
           
            inline const_iterator begin() const { return data.get_ref().begin(); }
            inline const_iterator end() const { return data.get_ref().end(); }
            
        private:
            const SugarVectorExpression<eT,Expr>& data ; 
            int nthreads ;
        } ;
    
        
        class Threads{
        public:
            Threads(int n_): n(n_){}
            int n ;
        } ;
        
    }
    
    template <typename eT, typename Expr>
    inline sugar::Parallel<eT,Expr> parallel( const SugarVectorExpression<eT,Expr>& expr, int nthreads ){
        return sugar::Parallel<eT,Expr>( expr, nthreads );   
    }
    
    template <typename eT, typename Expr>
    inline sugar::Parallel<eT,Expr> operator>>( sugar::Threads threads, const SugarVectorExpression<eT,Expr>& expr ){
        return parallel( expr, threads.n ) ;    
    }
        
    inline sugar::Threads threads(int n){ return sugar::Threads(n); }
    
}

#endif
