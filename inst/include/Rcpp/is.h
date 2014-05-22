#ifndef Rcpp__is__h
#define Rcpp__is__h

namespace Rcpp{
      
    namespace internal{  
        
        // simple implementation, for most default types
        template <typename T> bool is__simple( SEXP x) ;
        
        template <typename T>
        struct Is {
            inline bool test(SEXP /* x */){
                return false ;    
            }
        } ;
        template <> struct Is<RObject> ;
        template <> struct Is<DataFrame> ;
        template <> struct Is<S4> ;
        template <> struct Is<Reference> ;
        template <> struct Is<Formula> ;
        template <> struct Is<Function> ;
        
        template <int RTYPE> struct TypeofIs{
            inline bool test(SEXP x){
                return TYPEOF(x) == RTYPE ;    
            }
        } ;
        template <int RTYPE> struct IsMatrixTypeofIs{
            inline bool test(SEXP x){
                return TYPEOF(x) == RTYPE && Rf_isMatrix(x) ;
            }
        } ;
        
        template <typename T>
        struct PrimitiveIs{
            inline bool test(SEXP x){
                return Rf_length(x) == 1 && 
                    TYPEOF(x) == Rcpp::traits::r_sexptype_traits<T>::rtype ;    
            }
        };
           
        template <int RTYPE> struct Is< Vector<RTYPE> > : TypeofIs<RTYPE>{} ;
        template <int RTYPE> struct Is< Matrix<RTYPE> > : IsMatrixTypeofIs<RTYPE>{} ;
        
        template <> struct Is<Environment>   : TypeofIs<ENVSXP> {} ;
        template <> struct Is<Pairlist>      : TypeofIs<LISTSXP> {} ;
        template <> struct Is<Promise>       : TypeofIs<PROMSXP> {} ;
        template <> struct Is<Symbol>        : TypeofIs<SYMSXP> {} ;
        template <> struct Is<WeakReference> : TypeofIs<WEAKREFSXP> {} ;
        template <> struct Is<Language>      : TypeofIs<LANGSXP> {} ;
        
        template <typename T>
        struct is_type{
            typedef typename std::conditional<
                Rcpp::traits::is_primitive<T>::value, 
                PrimitiveIs<T>,
                Is<T>
            >::type type ;
        } ;
        
    }
    
    /** identify if an x can be seen as the T type
     *  
     *  example:
     *     bool is_list = is<List>( x ) ;
     */
    template <typename T> bool is( SEXP x ){
        return typename internal::is_type<T>::type().test(x) ;
    }
    
} // Rcpp 

#endif
