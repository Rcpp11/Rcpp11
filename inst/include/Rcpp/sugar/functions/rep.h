#ifndef Rcpp__sugar__rep_h
#define Rcpp__sugar__rep_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Rep : 
            public SugarVectorExpression<eT,Rep<eT,Expr>>, 
            public custom_sugar_vector_expression
        {
        public:
            Rep( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t times_ ) : 
                object(object_), times(times_), n(object_.size()){}
            
            inline eT operator[]( R_xlen_t i ) const {
                return object[ i % n ] ;
            }
            inline R_xlen_t size() const { 
                return times * n ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                
                // materialize the first time
                std::copy_n( sugar_begin(*this), n, it );
                
                // then copy
                for( R_xlen_t i=1; i<times; i++){
                    it += n ;
                    std::copy_n( target.begin(), n, it ) ;
                }   
            }
            
        private:
            const SugarVectorExpression<eT,Expr>& object ;
            R_xlen_t times, n ;
            
        } ;
        
        template <typename eT>
        class Rep_Single : 
            public SugarVectorExpression<eT,Rep_Single<eT>>, 
            public custom_sugar_vector_expression 
        {
        public:
            Rep_Single( eT x_, R_xlen_t n_) : x(x_), n(n_){}
            
            inline eT operator[]( R_xlen_t i ) const {
                return x;
            }
            inline R_xlen_t size() const { 
                return n ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::fill( target.begin(), target.end(), x ) ;    
            }
            
        private:
            eT x ;
            R_xlen_t n ;
        } ;
        
    } // sugar

    
    template <typename eT, typename Expr>
    inline sugar::Rep<eT,Expr> rep( const SugarVectorExpression<eT,Expr>& t, R_xlen_t n ){
        return sugar::Rep<eT,Expr>( t, n ) ;
    }
    
    template <typename eT>
    inline sugar::Rep_Single<eT> rep( eT x, R_xlen_t n ){
        return sugar::Rep_Single<eT>( x, n ) ;
    }

} // Rcpp
#endif

