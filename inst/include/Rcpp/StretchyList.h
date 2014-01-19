#ifndef Rcpp_StretchyList_h
#define Rcpp_StretchyList_h

namespace Rcpp{

    /**
     * StretchyList uses a special pairlist to provide efficient insertion
     * at the front and the end of a pairlist. 
     *
     * This is a C++ abstraction of the functions NewList, GrowList and Insert
     * that are found in places where a pair list has to grow efficiently, e.g.
     * in the R parser (gram.y)
     */
    RCPP_API_CLASS(StretchyList_Impl),
        public DottedPairProxyPolicy<StretchyList_Impl<StoragePolicy> >, 
        public DottedPairMultipleNamedProxyPolicy<StretchyList_Impl<StoragePolicy>>
    {
    public:
        
        RCPP_GENERATE_CTOR_ASSIGN(StretchyList_Impl) 
        
        typedef typename DottedPairProxyPolicy<StretchyList_Impl>::DottedPairProxy Proxy ;
        typedef typename DottedPairProxyPolicy<StretchyList_Impl>::const_DottedPairProxy const_Proxy ;
        
        StretchyList_Impl(){
            SEXP s = Rf_cons(R_NilValue, R_NilValue);
            SETCAR(s, s);
            Storage::set__(s) ;
        }
        StretchyList_Impl(SEXP x){
            Shield<SEXP> s = Rf_cons(R_NilValue, R_NilValue) ;
            if( Rf_isNull(x) ){
                SETCAR(s,s); 
            } else {
            
                SETCDR(s, x) ;
                
                SEXP p = x ;
                for(; !Rf_isNull(CDR(p)); p = CDR(p) );
                SETCAR(s, p) ;
                
            }
            Storage::set__(s) ;
        }
        
        void update(SEXP x){}
        
        inline operator SEXP() const{
            return CDR(Storage::get__() );    
        }
        
        template <typename T>
        inline StretchyList_Impl& push_back(const T& obj ){
            return push_back__impl( obj, typename traits::is_named<T>::type() ) ;
        }
        
        template <typename T>
        inline StretchyList_Impl& push_front(const T& obj ){
            return push_front__impl( obj, typename traits::is_named<T>::type() ) ;    
        }
        
    private:
        
        template <typename T>
        StretchyList_Impl& push_back__impl(const T& obj, std::true_type ) ;
        
        template <typename T>
        StretchyList_Impl& push_back__impl(const T& obj, std::false_type ) ;
        
        template <typename T>
        StretchyList_Impl& push_front__impl(const T& obj, std::true_type ) ;
        
        template <typename T>
        StretchyList_Impl& push_front__impl(const T& obj, std::false_type ) ;
        
    } ;
    
    typedef StretchyList_Impl<PreserveStorage> StretchyList ;
}
#endif
