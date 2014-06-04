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
            
            class const_iterator {
            public:
                typedef typename Rep::Vec Vec ;
                
                const_iterator( const Rep& data_, R_xlen_t index_ ) :
                    data(data_.vec), n(data_.n), index(index_), src_index(index % n ) {}
                
                inline const_iterator& operator++(){ 
                    index++;
                    set_src_index(src_index+1) ;
                    return *this ;
                }
        
                inline eT operator*() const {
                    return data[src_index] ;
                }
        
            private:
                const Vec& data ;
                R_xlen_t n, index, src_index;
                
                inline void set_src_index( R_xlen_t i ){
                    src_index = ( i == data.n ) ? 0 : i ;    
                }
                
            } ;
            
            
            Rep( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t times_ ) : 
                data(object_), times(times_), n(object_.size()){}
            
            inline R_xlen_t size() const { 
                return times * n ; 
            }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                
                // then copy
                for( R_xlen_t i=0; i<times; i++){
                    it += n ;
                    std::copy_n( data.begin(), n, it ) ;
                }   
            }
            
            inline const_iterator begin() const { return const_iterator(*this, 0) ; }
            inline const_iterator end() const { return const_iterator(*this, size() ) ; }
            
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
            typedef SugarIterator<eT, Rep_Single<eT> > const_iterator ;
            
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
            
            inline const_iterator begin() const { return const_iterator( *this, 0 ) ; }
            inline const_iterator end() const { return const_iterator( *this, size() ) ; }
            
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

