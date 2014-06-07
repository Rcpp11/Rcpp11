#ifndef Rcpp_vector_Subsetter_h_
#define Rcpp_vector_Subsetter_h_

namespace Rcpp {

    template <
        typename Source, // y
        typename eT, typename Expr // x
    >
    class SubsetProxy ;
    
    template <
        typename Source, // y
        typename Expr // x
    >
    class SubsetProxy< Source, int, Expr > : public SugarVectorExpression<typename Source::value_type, SubsetProxy< Source, int, Expr > > {
    public:
        typedef typename Source::value_type value_type ;
        
        typedef SugarVectorExpression<int, Expr> INDEX_T ;
        
        SubsetProxy( Source& source_, const SugarVectorExpression<int, Expr>& index_ ) :
            source(source_), index(index_){}
            
        template <typename RHS_eT, typename RHS_Expr>
        SubsetProxy& operator=( const SugarVectorExpression<RHS_eT,RHS_Expr>& rhs ){
            auto n = index.size() ;
            if( n != rhs.size() )
                stop( "incompatible sizes" ) ;
            
            auto target_it = source.begin() ;
            auto index_it = sugar_begin(index); 
            auto rhs_it = sugar_begin(rhs) ;
            for( int i=0; i<n; i++, ++index_it, ++rhs_it){
                target_it[*index_it] = *rhs_it ;
            }
            return *this ;
        }
            
        class RhsUseIterator : public std::iterator_traits<value_type*> {
        public:
            RhsUseIterator( const SubsetProxy& proxy, int index ) : 
                index_it( sugar_begin(proxy.index) + index), 
                source_it( proxy.source.begin() + index )
                {}
            
            RhsUseIterator& operator++() {
                ++index_it ;
                return *this ;
            }
            
            RhsUseIterator& operator+=(R_xlen_t n) {
                index_it += n;
                return *this ;
            }
            
            RhsUseIterator operator+( int n){
                RhsUseIterator copy(*this) ;
                copy += n ;
                return copy ;
            }
            
            value_type operator*(){
                return source_it[*index_it] ;
            }
            
            R_xlen_t operator-( const RhsUseIterator& other ){
                return index_it - other.index_it ;    
            }
                
            inline bool operator==( const RhsUseIterator& other ){ return index_it == other.index_it ; }
            inline bool operator!=( const RhsUseIterator& other ){ return index_it != other.index_it ; }
        
            
        private:
            typename Expr::const_iterator index_it ;
            typename Source::iterator source_it ;
            
        } ;
        typedef RhsUseIterator const_iterator ;
        
        inline R_xlen_t size() const {
            return index.size() ;    
        }
        
        inline RhsUseIterator begin() const {
            return const_iterator(*this, 0) ;
        }
        
        inline RhsUseIterator end() const {
            return const_iterator(*this, size()) ;
        }
        
    private:
        Source& source ; 
        const INDEX_T& index ;
        friend class  RhsUseIterator ;   
    } ;

    
    template <typename Source, typename eT, typename Expr>
    struct subset_proxy_type ;
    
    template <
        typename Source, // y
        typename Expr // x
    >
    inline typename subset_proxy_type<Source,int,Expr>::type 
    make_subset_proxy( Source& source, const SugarVectorExpression<int, Expr>& index ) ;
    
    
    template <
        typename Source, // y
        typename Expr // x
    >
    inline typename subset_proxy_type<Source,String,Expr>::type 
    make_subset_proxy( Source& source, const SugarVectorExpression<String, Expr>& index ) ;
    
    
}

#endif
