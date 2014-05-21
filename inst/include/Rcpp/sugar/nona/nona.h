#ifndef RCPP_SUGAR_NONA_NONA_H
#define RCPP_SUGAR_NONA_NONA_H

namespace Rcpp{
    namespace sugar {     
    
        template <int RTYPE, bool NA, typename VECTOR>
        class Nona : public SugarVectorExpression<RTYPE,false, Nona<RTYPE,NA,VECTOR> > {
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,VECTOR> SUGAR_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
            Nona( const SUGAR_TYPE& expr) : data(expr.get_ref()){} 
            
            inline int size() const { return data.size() ; }
            inline STORAGE operator[](int i) const { return data[i] ; }
            
        private:
            const VECTOR& data ;    
        } ;
        
        // specialization when the expression is actually a vector expression
        template <int RTYPE, bool NA>
        class Nona< RTYPE,NA,Rcpp::Vector<RTYPE> > : public SugarVectorExpression<RTYPE,false, Nona<RTYPE,NA,Rcpp::Vector<RTYPE> > > {
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,NA, Rcpp::Vector<RTYPE> > SUGAR_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            typedef typename Rcpp::Vector<RTYPE>::const_iterator const_iterator ;
    
            Nona( const SUGAR_TYPE& expr) : data(expr.get_ref().begin()), n(expr.size()){} 
            
            inline int size() const { return n ; }
            inline STORAGE operator[](int i) const { return data[i] ; }
            
        private:
            const_iterator data ;
            int n ;
        } ;
        
    }
    
    template <int RTYPE, bool NA, typename VECTOR>
    inline sugar::Nona<RTYPE,NA,VECTOR> noNA( const Rcpp::SugarVectorExpression<RTYPE,NA,VECTOR>& vec ){
        return sugar::Nona<RTYPE,NA,VECTOR>( vec ) ;
    }

}

#endif
