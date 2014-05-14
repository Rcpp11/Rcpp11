#ifndef Rcpp__vector__CommonVectorMethods_h
#define Rcpp__vector__CommonVectorMethods_h

namespace Rcpp{
    
    template <int RTYPE, typename Vec>
    class CommonVectorMethods {
    private:
        Vec& get_ref(){ return static_cast<Vec&>(*this) ; }
        
    public:
        
        inline void reset(int n){
            get_ref().data = Rf_allocVector(RTYPE, n) ;        
        }
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
            get_ref().data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void import_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
            import_applyable(other) ;
        }
        
        template <typename T>
        inline void import_applyable( const T& other ){
            reset(other.size());
            other.apply(get_ref()) ;
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other,  std::true_type ){
            get_ref().data = other.get_ref() ;    
        }
        
        template <bool NA, typename Expr>
        inline void assign_expression( const SugarVectorExpression<RTYPE,NA,Expr>& other, std::false_type ){
            assign_applyable(other) ;    
        }
        
        template <typename T>
        inline void assign_applyable( const T& other ){
            int n = other.size() ;
            if( n != get_ref().size() ){
                reset(n) ;    
            }
            other.apply(get_ref()) ;
        }
        
    } ;
    
}

#endif
