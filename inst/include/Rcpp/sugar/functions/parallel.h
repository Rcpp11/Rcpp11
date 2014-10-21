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
        
        template <typename eT, typename Expr>
        class Serial : 
            public SugarVectorExpression<eT, Serial<eT,Expr>>, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Expr::const_iterator const_iterator ;
            
            Serial( const SugarVectorExpression<eT,Expr>& data_): 
                data(data_){}
            
            inline R_xlen_t size() const { 
                return data.size(); 
            }
           
            template <typename Target>
            inline void apply( Target& target ) const {
                data.apply_serial( target ) ;     
            }
            
            template <typename Target>
            inline void apply_parallel( Target& target ) const {
                data.apply_serial( target ) ;     
            }
            
            template <typename Target>
            inline void apply_serial( Target& target ) const {
                data.apply_serial( target ) ;     
            }
           
            inline const_iterator begin() const { return data.get_ref().begin(); }
            inline const_iterator end() const { return data.get_ref().end(); }
            
        private:
            const SugarVectorExpression<eT,Expr>& data ; 
            
        } ;
    
    
        struct Threaded_tag{} ;
        struct Serial_tag{};
    
        template <typename eT, typename Expr>
        inline sugar::Parallel<eT,Expr> threaded( const SugarVectorExpression<eT,Expr>& expr ){
            return sugar::Parallel<eT,Expr>( expr );   
        }
    
        template <typename eT, typename Expr>
        inline sugar::Serial<eT,Expr> serial( const SugarVectorExpression<eT,Expr>& expr ){
            return sugar::Serial<eT,Expr>( expr );   
        }
    
    }
    
    
    template <typename eT, typename Expr>
    inline sugar::Parallel<eT,Expr> operator>>( sugar::Threaded_tag, const SugarVectorExpression<eT,Expr>& expr ){
        return sugar::threaded( expr ) ;    
    }
    
    template <typename eT, typename Expr>
    inline sugar::Serial<eT,Expr> operator>>( sugar::Serial_tag, const SugarVectorExpression<eT,Expr>& expr ){
        return sugar::serial( expr ) ;    
    }
        
    inline sugar::Threaded_tag threads(){ return sugar::Threaded_tag(); }
    inline sugar::Serial_tag serial(){ return sugar::Serial_tag() ; }
    
}

#endif
