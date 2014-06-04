#ifndef Rcpp__sugar__rep_len_h
#define Rcpp__sugar__rep_len_h

namespace Rcpp{
    namespace sugar{
    
        template <typename eT, typename Expr>
        class Rep_len :
            public SugarVectorExpression<eT,Rep_len<eT,Expr>>,
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename traits::vector_of<eT>::type Vec ;
            
            class const_iterator {
            public:
                typedef typename Rep_len::Vec Vec ;
                
                const_iterator( const Rep_len& data_, R_xlen_t index_ ) :
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
                
                inline void set_set_index( R_xlen_t i ){
                    src_index = ( i == data.n ) ? 0 : i ;    
                }
                
            } ;
            
            
            Rep_len( const SugarVectorExpression<eT,Expr>& object_, R_xlen_t len_ ) :
                data(object_), len(len_), n(object_.size()){}
        
            inline eT operator[]( R_xlen_t i ) const {
                return data[ i % n ] ;
            }
            inline R_xlen_t size() const { return len ; }
        
            template <typename Target>
            inline void apply(Target& target) const {
                if (n >= len) {
                    std::copy_n(data.begin(), len, target.begin() );
                    return;
                }
        
                int timesToFullCopy = len / n;
                int leftoverElems = len % n;
                
                // first copy data from the sugar expression
                auto it = target.begin();
                for (R_xlen_t i=0; i < timesToFullCopy; ++i) {
                    std::copy_n(data.begin(), n, it);
                    it += n;
                }
                if (leftoverElems) {
                    std::copy_n(target.begin(), leftoverElems, it);
                }
                
            }
        
            inline const_iterator begin() const { return const_iterator( *this, 0 ) ; }
            inline const_iterator end() const { return const_iterator( *this, size() ) ; }
            
        private:
            Vec data ;
            R_xlen_t len, n ;
        
        } ;
    
    } // sugar
    
    template <typename eT, typename Expr>
    inline sugar::Rep_len<eT,Expr> rep_len( const SugarVectorExpression<eT,Expr>& t, R_xlen_t len ){
        return sugar::Rep_len<eT,Expr>( t, len ) ;
    }


} // Rcpp
#endif

