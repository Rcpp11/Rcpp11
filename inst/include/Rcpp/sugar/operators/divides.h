#ifndef Rcpp__sugar__divides_h
#define Rcpp__sugar__divides_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool NA, typename T>
    class Divides_Vector_Primitive : 
        public SugarVectorExpression<RTYPE,true, Divides_Vector_Primitive<RTYPE,NA,T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
        
        Divides_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
            lhs(lhs_), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) ) {
        }
    
        inline STORAGE operator[]( int i ) const {
            if(rhs_na) return rhs ;
            STORAGE x = lhs[i] ;
            return Rcpp::traits::is_na<RTYPE>(x) ? x : (x / rhs) ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        STORAGE rhs ;
        bool rhs_na ;
    } ;
    // RTYPE : REALSXP
    template <bool NA, typename T>
    class Divides_Vector_Primitive<REALSXP,NA,T> : 
        public SugarVectorExpression<REALSXP,true, Divides_Vector_Primitive<REALSXP,NA,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,NA,T> VEC_TYPE ;
        
        Divides_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
            lhs(lhs_), rhs(rhs_) {
        }
    
        inline double operator[]( int i ) const {
            return lhs[i] / rhs ;
        }
    
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        double rhs ;
    } ;



    template <int RTYPE, typename T>
    class Divides_Vector_Primitive<RTYPE,false,T> : 
        public SugarVectorExpression<RTYPE,true, Divides_Vector_Primitive<RTYPE,false,T> > {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,T> VEC_TYPE ;
        
        Divides_Vector_Primitive( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
            lhs(lhs_), rhs(rhs_), rhs_na( Rcpp::traits::is_na<RTYPE>(rhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( rhs_na ) return rhs ;
            STORAGE x = lhs[i] ;
            return Rcpp::traits::is_na<RTYPE>(x) ? x : (x / rhs) ;
        }
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        STORAGE rhs ;
        bool rhs_na ;
    } ;
    // RTYPE = REALSXP
    template <typename T>
    class Divides_Vector_Primitive<REALSXP,false,T> : 
        public SugarVectorExpression<REALSXP,true, Divides_Vector_Primitive<REALSXP,false,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,T> VEC_TYPE ;
        
        Divides_Vector_Primitive( const VEC_TYPE& lhs_, double rhs_ ) : 
            lhs(lhs_), rhs(rhs_){}
    
        inline double operator[]( int i ) const {
            return lhs[i] / rhs ;
        }
        inline int size() const { return lhs.size() ; }
    
    private:
        const VEC_TYPE& lhs ;
        double rhs ;
    } ;



    template <int RTYPE, bool NA, typename T>                                                   
    class Divides_Primitive_Vector : 
        public SugarVectorExpression<RTYPE,true, Divides_Primitive_Vector<RTYPE,NA,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<RTYPE,NA,T> VEC_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ; 
    
        Divides_Primitive_Vector( STORAGE lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_), lhs_na( Rcpp::traits::is_na<RTYPE>(lhs_) ) {}
    
        inline STORAGE operator[]( int i ) const {
            if( lhs_na ) return lhs ;
            STORAGE x = rhs[i] ;
            return Rcpp::traits::is_na<RTYPE>(x) ? x : (lhs / x) ;
        }
        inline int size() const { return rhs.size() ; }
    private:
        STORAGE lhs ;
        const VEC_TYPE& rhs ;
        bool lhs_na ;
    } ;
    // RTYPE = REALSXP
    template <bool NA, typename T>                                                   
    class Divides_Primitive_Vector<REALSXP,NA,T> : 
        public SugarVectorExpression<REALSXP,true, Divides_Primitive_Vector<REALSXP,NA,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,NA,T> VEC_TYPE ;
        
        Divides_Primitive_Vector( double lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_) {}
    
        inline double operator[]( int i ) const {
            return lhs / rhs[i] ; 
        }
        inline int size() const { return rhs.size() ; }
    private:
        double lhs ;
        const VEC_TYPE& rhs ;
    } ;



    template <int RTYPE, typename T>                                                   
    class Divides_Primitive_Vector<RTYPE,false,T> : 
        public SugarVectorExpression<RTYPE,true, Divides_Primitive_Vector<RTYPE,false,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<RTYPE,false,T> VEC_TYPE ;
        typedef typename traits::storage_type<RTYPE>::type STORAGE ; 
        
        Divides_Primitive_Vector( STORAGE lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_), lhs_na( Rcpp::traits::is_na<RTYPE>(lhs_) ) {}

        inline STORAGE operator[]( int i ) const {
            if( lhs_na ) return lhs ;
            return lhs / rhs[i] ;
        }
        inline int size() const { return rhs.size() ; }
    
    private:
        STORAGE lhs ;
        const VEC_TYPE& rhs ;
        bool lhs_na ;
    } ;
    // RTYPE = REALSXP
    template <typename T>                                                   
    class Divides_Primitive_Vector<REALSXP,false,T> : 
        public SugarVectorExpression<REALSXP,true, Divides_Primitive_Vector<REALSXP,false,T> > {
    public:
        typedef typename Rcpp::SugarVectorExpression<REALSXP,false,T> VEC_TYPE ;
        
        Divides_Primitive_Vector( double lhs_, const VEC_TYPE& rhs_ ) : 
            lhs(lhs_), rhs(rhs_) {}

        inline double operator[]( int i ) const {
            return lhs / rhs[i] ;
        }
        inline int size() const { return rhs.size() ; }
    
    private:
        double lhs ;
        const VEC_TYPE& rhs ;
    } ;


}
}

template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Divides_Vector_Primitive< RTYPE , NA, T >
operator/( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs, 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs 
) {
    return Rcpp::sugar::Divides_Vector_Primitive<RTYPE,NA,T>( lhs, rhs ) ;
}


template <int RTYPE,bool NA, typename T>
inline Rcpp::sugar::Divides_Primitive_Vector< RTYPE , NA,T>
operator/( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs, 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& rhs
) {
    return Rcpp::sugar::Divides_Primitive_Vector<RTYPE,NA,T>( lhs, rhs ) ;
}

#endif
