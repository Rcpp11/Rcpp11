#ifndef Rcpp__sugar__plus_h
#define Rcpp__sugar__plus_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Plus_Vector_Vector : public SugarVectorExpression<RTYPE, true , Plus_Vector_Vector<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_) {}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE lhs_ = lhs[i] ;
            if( traits::is_na<RTYPE>(lhs_) ) return lhs_ ;
            STORAGE rhs_ = rhs[i] ;
            return traits::is_na<RTYPE>(rhs_) ? rhs_ : (lhs_ + rhs_) ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // specialization of the above for REALSXP because : 
    // NA_REAL + NA_REAL = NA_REAL
    // NA_REAL + x = NA_REAL
    // x + NA_REAL = NA_REAL
    template <bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Plus_Vector_Vector<REALSXP,LHS_NA,LHS_T,RHS_NA,RHS_T> : 
        public SugarVectorExpression<REALSXP, true , Plus_Vector_Vector<REALSXP,LHS_NA,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<REALSXP,RHS_NA,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs[i] + rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;




    // specialization LHS_NA = false
    template <int RTYPE, typename LHS_T, bool RHS_NA, typename RHS_T >
    class Plus_Vector_Vector<RTYPE,false,LHS_T,RHS_NA,RHS_T> : public SugarVectorExpression<RTYPE,true, Plus_Vector_Vector<RTYPE,false,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE rhs_ = rhs[i] ;
            if( traits::is_na<RTYPE>(rhs_) ) return rhs_ ;
            return lhs[i] + rhs_  ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // LHS_NA = false & RTYPE = REALSXP
    template <typename LHS_T, bool RHS_NA, typename RHS_T >
    class Plus_Vector_Vector<REALSXP,false,LHS_T,RHS_NA,RHS_T> : 
        public SugarVectorExpression<REALSXP,true, Plus_Vector_Vector<REALSXP,false,LHS_T,RHS_NA,RHS_T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<REALSXP,RHS_NA,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] + rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;



    // specialization for RHS_NA = false 
    template <int RTYPE, bool LHS_NA, typename LHS_T, typename RHS_T >
    class Plus_Vector_Vector<RTYPE,LHS_NA,LHS_T,false,RHS_T> : public SugarVectorExpression<RTYPE, true , Plus_Vector_Vector<RTYPE,LHS_NA,LHS_T,false,RHS_T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline STORAGE operator[]( int i ) const {
            STORAGE lhs_ = lhs[i] ;
            if( traits::is_na<RTYPE>(lhs_) ) return lhs_ ;
            return lhs_ + rhs[i]  ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // RHS_NA = false, RTYPE = REALSXP
    template <bool LHS_NA, typename LHS_T, typename RHS_T >
    class Plus_Vector_Vector<REALSXP,LHS_NA,LHS_T,false,RHS_T> : 
        public SugarVectorExpression<REALSXP, true , Plus_Vector_Vector<REALSXP,LHS_NA,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,LHS_NA,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] + rhs[i] ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;




    // specialization for RHS_NA = false  and LHS_NA = false 
    template <int RTYPE, typename LHS_T, typename RHS_T >
    class Plus_Vector_Vector<RTYPE,false,LHS_T,false,RHS_T> : public SugarVectorExpression<RTYPE, false , Plus_Vector_Vector<RTYPE,false,LHS_T,false,RHS_T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline STORAGE operator[]( int i ) const {
            return lhs[i] + rhs[i]  ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;
    // specialization for RHS_NA = false  and LHS_NA = false, RTYPE = REALSXP 
    template <typename LHS_T, typename RHS_T >
    class Plus_Vector_Vector<REALSXP,false,LHS_T,false,RHS_T> : 
        public SugarVectorExpression<REALSXP, false , Plus_Vector_Vector<REALSXP,false,LHS_T,false,RHS_T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,LHS_T> LHS_TYPE ;
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,RHS_T> RHS_TYPE ;
    
        Plus_Vector_Vector( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] + rhs[i]  ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const LHS_TYPE& lhs ;
        const RHS_TYPE& rhs ;
    } ;







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

template <int RTYPE,bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Plus_Vector_Vector< 
    RTYPE , 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    >
operator+( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Plus_Vector_Vector<
        RTYPE, 
        LHS_NA, LHS_T,
        RHS_NA, RHS_T
        >( lhs, rhs ) ;
}

#endif
