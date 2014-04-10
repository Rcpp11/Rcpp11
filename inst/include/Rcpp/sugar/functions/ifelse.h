#ifndef Rcpp__sugar__ifelse_h
#define Rcpp__sugar__ifelse_h

namespace Rcpp{
namespace sugar{

template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool LHS_NA , typename LHS_T, 
    bool RHS_NA , typename RHS_T
    >
class IfElse : public SugarVectorExpression< 
    RTYPE, 
    ( COND_NA || LHS_NA || RHS_NA ) ,
    IfElse<RTYPE,COND_NA,COND_T,LHS_NA,LHS_T,RHS_NA,RHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,COND_NA,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,LHS_NA ,LHS_T>  LHS_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>  RHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;

    IfElse( const COND_TYPE& cond_, const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {
            /* FIXME : cond, lhs and rhs must all have the same size */
    }

    inline STORAGE operator[]( int i ) const {
        int x = cond[i] ;
        if( Rcpp::traits::is_na<LGLSXP>(x) ) return x ;
        if( x ) return lhs[i] ;
        return rhs[i] ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    const LHS_TYPE& lhs ;
    const RHS_TYPE& rhs ;

} ;
  
template <
    int RTYPE, 
    typename COND_T, 
    bool LHS_NA , typename LHS_T, 
    bool RHS_NA , typename RHS_T
    >
class IfElse<RTYPE,false,COND_T,LHS_NA,LHS_T,RHS_NA,RHS_T> : public SugarVectorExpression< 
    RTYPE, 
    ( LHS_NA || RHS_NA ) ,
    IfElse<RTYPE,false,COND_T,LHS_NA,LHS_T,RHS_NA,RHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,false,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,LHS_NA ,LHS_T>  LHS_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>  RHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;

    IfElse( const COND_TYPE& cond_, const LHS_TYPE& lhs_, const RHS_TYPE& rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {}

    inline STORAGE operator[]( int i ) const {
        if( cond[i] ) return lhs[i] ;
        return rhs[i] ;
    }

    inline int size() const { return cond.size() ; }

private:

    const COND_TYPE& cond ;
    const LHS_TYPE& lhs ;
    const RHS_TYPE& rhs ;

} ;


/* ifelse( cond, primitive, Vector ) */

template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool RHS_NA , typename RHS_T
    >
class IfElse_Primitive_Vector : public SugarVectorExpression< 
    RTYPE, 
    true ,
    IfElse_Primitive_Vector<RTYPE,COND_NA,COND_T,RHS_NA,RHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,COND_NA,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>  RHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;

    IfElse_Primitive_Vector( const COND_TYPE& cond_, STORAGE lhs_, const RHS_TYPE& rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {}

    inline STORAGE operator[]( int i ) const {
        int x = cond[i] ;
        if( Rcpp::traits::is_na<LGLSXP>(x) ) return x ;
        if( x ) return lhs ;
        return rhs[i] ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    STORAGE lhs ;
    const RHS_TYPE& rhs ;

} ;

template <
    int RTYPE, 
    typename COND_T, 
    bool RHS_NA , typename RHS_T
    >
class IfElse_Primitive_Vector<RTYPE,false,COND_T,RHS_NA,RHS_T> : public SugarVectorExpression< 
    RTYPE, 
    true,
    IfElse_Primitive_Vector<RTYPE,false,COND_T,RHS_NA,RHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,false,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>  RHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;
    
    IfElse_Primitive_Vector( const COND_TYPE& cond_, STORAGE lhs_, const RHS_TYPE& rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {}

    inline STORAGE operator[]( int i ) const {
        if( cond[i] ) return lhs ;
        return rhs[i] ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    STORAGE lhs ;
    const RHS_TYPE& rhs ;

} ;



/* ifelse( cond, Vector, primitive ) */

template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool LHS_NA , typename LHS_T
    >
class IfElse_Vector_Primitive : public SugarVectorExpression< 
    RTYPE, 
    true ,
    IfElse_Vector_Primitive<RTYPE,COND_NA,COND_T,LHS_NA,LHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,COND_NA,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,LHS_NA ,LHS_T>  LHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;
    
    IfElse_Vector_Primitive( const COND_TYPE& cond_, const LHS_TYPE& lhs_, STORAGE rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {
            /* FIXME : cond, lhs and rhs must all have the same size */
    }

    inline STORAGE operator[]( int i ) const {
        int x = cond[i] ;
        if( x == NA ) return NA ;
        if( x ) return lhs[i] ;
        return rhs ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    const LHS_TYPE& lhs ;
    const STORAGE rhs ;

} ;

template <
    int RTYPE, 
    typename COND_T, 
    bool LHS_NA , typename LHS_T
    >
class IfElse_Vector_Primitive<RTYPE,false,COND_T,LHS_NA,LHS_T> : public SugarVectorExpression< 
    RTYPE, 
    true ,
    IfElse_Vector_Primitive<RTYPE,false,COND_T,LHS_NA,LHS_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,false,COND_T> COND_TYPE ;
    typedef Rcpp::VectorBase<RTYPE ,LHS_NA ,LHS_T>  LHS_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;
    
    IfElse_Vector_Primitive( const COND_TYPE& cond_, const LHS_TYPE& lhs_, STORAGE rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {}

    inline STORAGE operator[]( int i ) const {
        if( cond[i] ) return lhs[i] ;
        return rhs ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    const LHS_TYPE& lhs ;
    const STORAGE rhs ;

} ;





/* ifelse( cond, primitive, primitive ) */

template <
    int RTYPE, 
    bool COND_NA, typename COND_T
    >
class IfElse_Primitive_Primitive : public SugarVectorExpression< 
    RTYPE, 
    true ,
    IfElse_Primitive_Primitive<RTYPE,COND_NA,COND_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,COND_NA,COND_T> COND_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;

    IfElse_Primitive_Primitive( const COND_TYPE& cond_, STORAGE lhs_, STORAGE rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_)  {
            /* FIXME : cond, lhs and rhs must all have the same size */
    }

    inline STORAGE operator[]( int i ) const {
        int x = cond[i] ;
        if( x == NA ) return NA ;
        return x ? lhs : rhs ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    STORAGE lhs ;
    STORAGE rhs ;
    STORAGE na ;

} ;

template <
    int RTYPE, typename COND_T
    >
class IfElse_Primitive_Primitive<RTYPE,false,COND_T> : public SugarVectorExpression< 
    RTYPE, 
    true ,
    IfElse_Primitive_Primitive<RTYPE,false,COND_T>
> {
public:         
    typedef Rcpp::VectorBase<LGLSXP,false,COND_T> COND_TYPE ;
    typedef typename traits::storage_type<RTYPE>::type STORAGE ;

    IfElse_Primitive_Primitive( const COND_TYPE& cond_, STORAGE lhs_, STORAGE rhs_ ) : 
        cond(cond_), lhs(lhs_), rhs(rhs_) {
            /* FIXME : cond, lhs and rhs must all have the same size */
    }

    inline STORAGE operator[]( int i ) const {
        return cond[i] ? lhs : rhs ;
    }

    inline int size() const { return cond.size() ; }

private:
    const COND_TYPE& cond ;
    STORAGE lhs ;
    STORAGE rhs ;

} ;

} // sugar

template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool LHS_NA , typename LHS_T, 
    bool RHS_NA , typename RHS_T
    >
inline sugar::IfElse< RTYPE,COND_NA,COND_T,LHS_NA,LHS_T,RHS_NA,RHS_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    const Rcpp::VectorBase<RTYPE ,LHS_NA ,LHS_T>& lhs,
    const Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>& rhs
    ){
    return sugar::IfElse<RTYPE,COND_NA,COND_T,LHS_NA,LHS_T,RHS_NA,RHS_T>( cond, lhs, rhs ) ;
}


template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool RHS_NA , typename RHS_T
    >
inline sugar::IfElse_Primitive_Vector< RTYPE,COND_NA,COND_T,RHS_NA,RHS_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    typename traits::storage_type<RTYPE>::type lhs,
    const Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>& rhs
    ){
    return sugar::IfElse_Primitive_Vector<RTYPE,COND_NA,COND_T,RHS_NA,RHS_T>( cond, lhs, rhs ) ;
}

template <
    int RTYPE, 
    bool COND_NA, typename COND_T, 
    bool RHS_NA , typename RHS_T
    >
inline sugar::IfElse_Vector_Primitive< RTYPE,COND_NA,COND_T,RHS_NA,RHS_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    const Rcpp::VectorBase<RTYPE ,RHS_NA ,RHS_T>& lhs,
    typename traits::storage_type<RTYPE>::type rhs
    ){
    return sugar::IfElse_Vector_Primitive<RTYPE,COND_NA,COND_T,RHS_NA,RHS_T>( cond, lhs, rhs ) ;
}

template< 
    bool COND_NA, typename COND_T
>
inline sugar::IfElse_Primitive_Primitive< REALSXP,COND_NA,COND_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    double lhs,
    double rhs
    ){
    return sugar::IfElse_Primitive_Primitive<REALSXP,COND_NA,COND_T>( cond, lhs, rhs ) ;
}

template< 
    bool COND_NA, typename COND_T
>
inline sugar::IfElse_Primitive_Primitive< INTSXP,COND_NA,COND_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    int lhs,
    int rhs
    ){
    return sugar::IfElse_Primitive_Primitive<INTSXP,COND_NA,COND_T>( cond, lhs, rhs ) ;
}

template< 
    bool COND_NA, typename COND_T
>
inline sugar::IfElse_Primitive_Primitive< CPLXSXP,COND_NA,COND_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    Rcomplex lhs,
    Rcomplex rhs
    ){
    return sugar::IfElse_Primitive_Primitive<CPLXSXP,COND_NA,COND_T>( cond, lhs, rhs ) ;
}

template< 
    bool COND_NA, typename COND_T
>
inline sugar::IfElse_Primitive_Primitive< LGLSXP,COND_NA,COND_T > 
ifelse( 
    const Rcpp::VectorBase<LGLSXP,COND_NA,COND_T>& cond,
    bool lhs,
    bool rhs
    ){
    return sugar::IfElse_Primitive_Primitive<LGLSXP,COND_NA,COND_T>( cond, lhs, rhs ) ;
}


} // Rcpp

#endif
