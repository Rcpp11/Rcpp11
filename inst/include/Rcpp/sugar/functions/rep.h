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
            typedef typename traits::vector_of<eT>::type Vec ;
            
            class const_iterator : public std::iterator_traits<eT*> {
            public:
                typedef typename Rep::Vec Vec ;
                
                const_iterator( const Rep& data_, R_xlen_t n, R_xlen_t index_ ) :
                    data(data_.data), index(index_), src_index(index % n ) {}
                
                inline const_iterator& operator++(){ 
                    index++;
                    src_index++ ; if( src_index == n ) src_index = 0 ;
                    return *this ;
                }
        
                inline eT operator*() const {
                    return data[src_index] ;
                }
                
                inline bool operator==( const const_iterator& other ) { return index == other.index; }
                inline bool operator!=( const const_iterator& other ) { return index != other.index; }
        
                inline int operator-( const const_iterator& other ){ 
                    return index - other.index ;    
                }
                    
            private:
                const Vec& data ;
                R_xlen_t n, index, src_index;
                
            } ;
            
            
            Rep( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t times_ ) : 
                data(object_), times(times_), n(object_.size())
            {
                RCPP_DEBUG( "Rep = %s \n", DEMANGLE(Rep) )    
            }
            
            inline R_xlen_t size() const { 
                return times * n ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                
                // then copy
                for( R_xlen_t i=0; i<times; i++, it += n){
                    std::copy_n( data.begin(), n, it ) ;
                }   
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                apply(target) ;
            }
            
            
            inline const_iterator begin() const { return const_iterator(*this, n, 0) ; }
            inline const_iterator end() const { return const_iterator(*this, n, size() ) ; }
            
        private:
            Vec data ;
            R_xlen_t times, n ;
            
        } ;
        
        template <typename eT>
        class Rep_Single : 
            public SugarVectorExpression<eT,Rep_Single<eT>>, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef constant_iterator<eT> const_iterator ;
            
            Rep_Single( eT x_, R_xlen_t n_) : x(x_), n(n_){}
            
            inline R_xlen_t size() const { 
                return n ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::fill( target.begin(), target.end(), x ) ;    
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target, int nthreads ) const {
                apply(target) ;
            }
            
            inline const_iterator begin() const { return const_iterator( x, 0 ) ; }
            inline const_iterator end() const { return const_iterator( x, size() ) ; }
            
        private:
            eT x ;
            R_xlen_t n ;
        } ;
        
        
    } // sugar

    
    template <typename eT, typename Expr>
    inline sugar::Rep<eT,Expr> rep( const SugarVectorExpression<eT,Expr>& t, R_xlen_t n ){
        RCPP_DEBUG( "rep<%s,%s> \n", DEMANGLE(eT), DEMANGLE(Expr) )
        return sugar::Rep<eT,Expr>( t, n ) ;
    }
    
    inline sugar::Rep_Single<double> rep( double x, R_xlen_t n ){
        return sugar::Rep_Single<double>( x, n ) ;
    }
    inline sugar::Rep_Single<int> rep( int x, R_xlen_t n ){
        return sugar::Rep_Single<int>( x, n ) ;
    }
    inline sugar::Rep_Single<Rboolean> rep( Rboolean x, R_xlen_t n ){
        return sugar::Rep_Single<Rboolean>( x, n ) ;
    }
    inline sugar::Rep_Single<Rcomplex> rep( Rcomplex x, R_xlen_t n ){
        return sugar::Rep_Single<Rcomplex>( x, n ) ;
    }

    
} // Rcpp
#endif

