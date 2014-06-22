#ifndef Rcpp__vector__impl_LogicalVector_h
#define Rcpp__vector__impl_LogicalVector_h

namespace Rcpp{

    #undef VEC
    #define VEC Vector<LGLSXP,Storage>

    template <typename Storage>
    class Vector<LGLSXP,Storage> :
        public VectorOfRTYPE<LGLSXP>,
        public SugarVectorExpression<Rboolean, VEC>
    {
    public:
        typedef Rboolean value_type ;
        typedef value_type&        reference       ;
        typedef const value_type&  const_reference ;
        typedef reference          Proxy           ;
        typedef const_reference    const_Proxy     ;
        typedef value_type*        iterator        ;
        typedef const value_type*  const_iterator  ;
            
        #define RTYPE LGLSXP
        #include <Rcpp/vector/impl/RCPP_VECTOR_API.h>
        #undef RTYPE
        
    public:
        Vector( R_xlen_t n, value_type x ) {
            reset(n);
            std::fill( begin(), end(), x) ;
        }
        explicit Vector( R_xlen_t n, bool x ) {
            reset(n);
            std::fill( begin(), end(), x ? TRUE : FALSE ) ;
        }


        Vector( std::initializer_list<value_type> list ){
            reset(list.size());
            std::copy( list.begin(), list.end(), begin() ) ;
        }
        Vector( std::initializer_list<bool> list ){
            reset(list.size());
            std::transform( list.begin(), list.end(), [](bool b){
                return b ? TRUE : FALSE ;        
            }) ;
        }

        Vector( std::initializer_list<traits::named_object<value_type>> list ){
            int n = list.size() ;
            reset(n);
            auto input_it = list.begin() ;
            auto it = begin() ;
            SEXP nams = PROTECT(Rf_allocVector(STRSXP, n) ) ;
            for( int i=0; i<n; i++, ++it, ++input_it){
                SET_STRING_ELT(nams, i, PRINTNAME(input_it->name) ) ;
                *it = input_it->object ;
            }
            UNPROTECT(1) ;
            names(*this) = nams ;
        }
        
        Vector( std::initializer_list<traits::named_object<bool>> list ){
            int n = list.size() ;
            reset(n);
            auto input_it = list.begin() ;
            auto it = begin() ;
            SEXP nams = PROTECT(Rf_allocVector(STRSXP, n) ) ;
            for( int i=0; i<n; i++, ++it, ++input_it){
                SET_STRING_ELT(nams, i, PRINTNAME(input_it->name) ) ;
                *it = input_it->object ? TRUE : FALSE;
            }
            UNPROTECT(1) ;
            names(*this) = nams ;
        }


        inline iterator begin() { return dataptr() ; }
        inline iterator end() { return dataptr() + size() ; }

        inline const_iterator begin() const{ return dataptr() ; }
        inline const_iterator end() const{ return dataptr() + size() ; }

        inline reference operator[](R_xlen_t i){
            RCPP_CHECK_BOUNDS(i)
            return dataptr()[i] ;
        }
        inline const_reference operator[](R_xlen_t i) const {
            RCPP_CHECK_BOUNDS(i)
            return dataptr()[i] ;
        }

    } ;

    #undef VEC

}


#endif
