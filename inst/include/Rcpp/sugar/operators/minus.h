#ifndef Rcpp__sugar__minus_h
#define Rcpp__sugar__minus_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Minus_Vector_Vector : 
        public SugarVectorExpression<RTYPE,true, Minus_Vector_Vector<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE x = lhs[i] ; 
            if( Rcpp::traits::is_na<RTYPE>( x ) ) return x ;
            STORAGE y = rhs[i] ; 
            return Rcpp::traits::is_na<RTYPE>( y ) ? y : ( x - y ) ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // RTYPE = REALSXP
    template <bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Minus_Vector_Vector<REALSXP,LHS_NA,LHS_T,RHS_NA,RHS_T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Vector_Vector<REALSXP,LHS_NA,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<REALSXP,RHS_NA,RHS_T> RHS_TYPE ;
            
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;


    template <int RTYPE, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Minus_Vector_Vector<RTYPE,false,LHS_T,RHS_NA,RHS_T> : public SugarVectorExpression<RTYPE,true, Minus_Vector_Vector<RTYPE,false,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE y = rhs[i] ; 
            if( Rcpp::traits::is_na<RTYPE>( y ) ) return y ;
            return lhs[i] - y ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // RTYPE = REALSXP
    template <typename LHS_T, bool RHS_NA, typename RHS_T >
    class Minus_Vector_Vector<REALSXP,false,LHS_T,RHS_NA,RHS_T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Vector_Vector<REALSXP,false,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<REALSXP,RHS_NA,RHS_T> RHS_TYPE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;


    template <int RTYPE, bool LHS_NA, typename LHS_T, typename RHS_T >
    class Minus_Vector_Vector<RTYPE,LHS_NA,LHS_T,false,RHS_T> : public SugarVectorExpression<RTYPE,true, Minus_Vector_Vector<RTYPE,LHS_NA,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<RTYPE,false,RHS_T> RHS_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE x = lhs[i] ; 
            if( Rcpp::traits::is_na<RTYPE>( x ) ) return x ;
            return x - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // RTYPE = REALSXP
    template <bool LHS_NA, typename LHS_T, typename RHS_T >
    class Minus_Vector_Vector<REALSXP,LHS_NA,LHS_T,false,RHS_T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Vector_Vector<REALSXP,LHS_NA,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<REALSXP,false,RHS_T> RHS_TYPE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;


    template <int RTYPE, typename LHS_T, typename RHS_T >
    class Minus_Vector_Vector<RTYPE,false,LHS_T,false,RHS_T> : 
        public SugarVectorExpression<RTYPE,false, Minus_Vector_Vector<RTYPE,false,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<RTYPE,false,RHS_T> RHS_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline STORAGE operator[]( int i ) const {
            return lhs[i] - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    template <typename LHS_T, typename RHS_T >
    class Minus_Vector_Vector<REALSXP,false,LHS_T,false,RHS_T> : 
        public SugarVectorExpression<REALSXP,false, Minus_Vector_Vector<REALSXP,false,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::VectorBase<REALSXP,false,RHS_T> RHS_TYPE ;
        
        Minus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;





    template <int RTYPE, bool NA, typename T>
    class Minus_Vector_Primitive : 
        public SugarVectorExpression<RTYPE,true, Minus_Vector_Primitive<RTYPE,NA,T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
        
        Minus_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( rhs_na ) return rhs ;
            STORAGE x = lhs[i] ;
            return Rcpp::traits::is_na<RTYPE>(x) ? x : (x - rhs) ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        STORAGE rhs ;
        bool rhs_na ;
    } ;
    template <bool NA, typename T>
    class Minus_Vector_Primitive<REALSXP,NA,T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Vector_Primitive<REALSXP,NA,T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,NA,T> VEC_TYPE ;
        
        Minus_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        double rhs ;
    } ;


    template <int RTYPE, typename T>
    class Minus_Vector_Primitive<RTYPE,false,T> : 
        public SugarVectorExpression<RTYPE,true, Minus_Vector_Primitive<RTYPE,false,T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::VectorBase<RTYPE,false,T> VEC_TYPE ;
        
        Minus_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( rhs_na ) return rhs ;
            STORAGE x = lhs[i] ;
            return Rcpp::traits::is_na<RTYPE>(x) ? x : (x - rhs) ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        STORAGE rhs ;
        bool rhs_na ;
    } ;
    template <typename T>
    class Minus_Vector_Primitive<REALSXP,false,T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Vector_Primitive<REALSXP,false,T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,false,T> VEC_TYPE ;
        
        Minus_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
            lhs(lhs_.get_ref()), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] - rhs ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        double rhs ;
    } ;






    template <int RTYPE, bool NA, typename T>                                                   
    class Minus_Primitive_Vector : 
        public SugarVectorExpression<RTYPE,true, Minus_Primitive_Vector<RTYPE,NA,T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ; 
        
        Minus_Primitive_Vector( STORAGE lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_), lhs_na( Rcpp::traits::is_na<RTYPE>(lhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( lhs_na ) return lhs ;
            return lhs - rhs[i] ;
        }
        inline int size() const { return rhs.size() ; }
    
    private:
        STORAGE lhs ;
        const VEC_TYPE& rhs ;
        bool lhs_na ;
    } ;
    template <bool NA, typename T>                                                   
    class Minus_Primitive_Vector<REALSXP,NA,T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Primitive_Vector<REALSXP,NA,T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,NA,T> VEC_TYPE ;
        
        Minus_Primitive_Vector( double lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs - rhs[i] ;
        }
        inline int size() const { return rhs.size() ; }
    
    private:
        double lhs ;
        const VEC_TYPE& rhs ;
    } ;



    template <int RTYPE, typename T>                                                   
    class Minus_Primitive_Vector<RTYPE,false,T> : 
        public SugarVectorExpression<RTYPE,true, Minus_Primitive_Vector<RTYPE,false,T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,false,T> VEC_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ; 
        
        Minus_Primitive_Vector( STORAGE lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_), lhs_na( Rcpp::traits::is_na<RTYPE>(lhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( lhs_na ) return lhs ;
            return lhs - rhs[i] ;
        }
    
        inline int size() const { return rhs.size() ; }
    
    private:
        STORAGE lhs ;
        const VEC_TYPE& rhs ;
        bool lhs_na ;
    
    } ;
    template <typename T>                                                   
    class Minus_Primitive_Vector<REALSXP,false,T> : 
        public SugarVectorExpression<REALSXP,true, Minus_Primitive_Vector<REALSXP,false,T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,false,T> VEC_TYPE ;
        
        Minus_Primitive_Vector( double lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs - rhs[i] ;
        }
    
        inline int size() const { return rhs.size() ; }
    
    private:
        double lhs ;
        const VEC_TYPE& rhs ;
    } ;


}
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Minus_Vector_Primitive< RTYPE , NA, T >
operator-( 
    const Rcpp::VectorBase<RTYPE,NA,T>& lhs, 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs 
) {
    return Rcpp::sugar::Minus_Vector_Primitive<RTYPE,NA,T>( lhs, rhs ) ;
}


template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Minus_Primitive_Vector< RTYPE , NA,T>
operator-( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs, 
    const Rcpp::VectorBase<RTYPE,NA,T>& rhs
) {
    return Rcpp::sugar::Minus_Primitive_Vector<RTYPE,NA,T>( lhs, rhs ) ;
}

template <int RTYPE,bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Minus_Vector_Vector< 
    RTYPE , 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    >
operator-( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs,
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Minus_Vector_Vector<
        RTYPE, 
        LHS_NA,LHS_T,
        RHS_NA,RHS_T
        >( lhs, rhs ) ;
}

#endif
