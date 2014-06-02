#ifndef Rcpp__sugar__rep_h
#define Rcpp__sugar__rep_h

namespace Rcpp{
    namespace sugar{
    
        template <typename Expr>
        class Rep : 
            public SugarVectorExpression<Rep<Expr>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Expr::value_type value_type ;
            
            Rep( const Expr& object_, R_xlen_t times_ ) : 
                object(object_), times(times_), n(object_.size()){}
            
            inline value_type operator[]( R_xlen_t i ) const {
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
            const Expr& object ;
            R_xlen_t times, n ;
            
        } ;
        
        template <typename T>
        class Rep_Single : 
            public SugarVectorExpression<Rep_Single<T>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef T value_type ;
            
            Rep_Single( T x_, R_xlen_t n_) : x(x_), n(n_){}
            
            inline T operator[]( R_xlen_t i ) const {
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
            T x ;
            R_xlen_t n ;
        } ;
        
    } // sugar

    
    template <typename Expr>
    inline sugar::Rep<Expr> rep( const SugarVectorExpression<Expr>& t, R_xlen_t n ){
        return sugar::Rep<Expr>( t, n ) ;
    }
    
    inline sugar::Rep_Single<double> rep( double x, R_xlen_t n ){
        return sugar::Rep_Single<double>( x, n ) ;
    }
    inline sugar::Rep_Single<int> rep( int x, R_xlen_t n ){
        return sugar::Rep_Single<int>( x, n ) ;
    }
    inline sugar::Rep_Single<Rbyte> rep( Rbyte x, R_xlen_t n ){
        return sugar::Rep_Single<Rbyte>( x, n ) ;
    }
    inline sugar::Rep_Single<Rcomplex> rep( Rcomplex x, R_xlen_t n ){
        return sugar::Rep_Single<Rcomplex>( x, n ) ;
    }
    inline sugar::Rep_Single<bool> rep( bool x, R_xlen_t n ){
        return sugar::Rep_Single<bool>( x, n ) ;
    }

} // Rcpp
#endif

