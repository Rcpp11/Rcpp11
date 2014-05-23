#ifndef Rcpp__sugar__plus_h
#define Rcpp__sugar__plus_h

namespace Rcpp{
    namespace sugar{
        
        template <int RTYPE, bool NA, typename T>
        class Plus_Vector_Primitive : 
            public SugarVectorExpression<RTYPE,true, Plus_Vector_Primitive<RTYPE,NA,T> > {
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
            Plus_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
                lhs(lhs_), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) )
                {}
        
            inline STORAGE operator[]( int i ) const {
                if( rhs_na ) return rhs ;
                STORAGE x = lhs[i] ;
                return Rcpp::traits::is_na<RTYPE>(x) ? x : (x + rhs) ;
            }
        
            inline int size() const { return lhs.size() ; }
        
        private:
            const VEC_TYPE& lhs ;
            STORAGE rhs ;
            bool rhs_na ;
        
        } ;
        // RTYPE = REALSXP
        template <bool NA, typename T>
        class Plus_Vector_Primitive<REALSXP,NA,T> : 
            public SugarVectorExpression<REALSXP,true, Plus_Vector_Primitive<REALSXP,NA,T> > {
        public:
            typedef typename Rcpp::SugarVectorExpression<REALSXP,NA,T> VEC_TYPE ;
            
            Plus_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
                lhs(lhs_), rhs(rhs_)
                {}
        
            inline double operator[]( int i ) const {
                return rhs + lhs[i] ; 
            }
        
            inline int size() const { return lhs.size() ; }
        
        private:
            const VEC_TYPE& lhs ;
            double rhs ;
        } ;
    
    
    
        template <int RTYPE, typename T>
        class Plus_Vector_Primitive<RTYPE,false,T> : public SugarVectorExpression<RTYPE,false, Plus_Vector_Primitive<RTYPE,false,T> > {
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,false,T> VEC_TYPE ;
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
            Plus_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
                lhs(lhs_), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) ) {}
        
            inline STORAGE operator[]( int i ) const {
                return rhs_na ? rhs : (rhs + lhs[i] ) ;
            }
        
            inline int size() const { return lhs.size() ; }
        
        private:
            const VEC_TYPE& lhs ;
            STORAGE rhs ;
            bool rhs_na ;
        } ;
        // RTYPE = REALSXP
        template <typename T>
        class Plus_Vector_Primitive<REALSXP,false,T> : 
            public SugarVectorExpression<REALSXP,false, Plus_Vector_Primitive<REALSXP,false,T> > {
        public:
            typedef typename Rcpp::SugarVectorExpression<REALSXP,false,T> VEC_TYPE ;
        
            Plus_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline double operator[]( int i ) const {                                                  
                return rhs + lhs[i] ;
            }
        
            inline int size() const { return lhs.size() ; }
        
        private:
            const VEC_TYPE& lhs ;
            double rhs ;
        } ;
    
    }
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Plus_Vector_Primitive<RTYPE,NA,T>
operator+( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs, 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs 
) {
    return Rcpp::sugar::Plus_Vector_Primitive<RTYPE,NA,T>( lhs, rhs ) ;
}


template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Plus_Vector_Primitive< RTYPE , NA , T >
operator+( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs, 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs
) {
    return Rcpp::sugar::Plus_Vector_Primitive<RTYPE,NA, T >( lhs, rhs ) ;
}










#endif
