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
        
        void update(SEXP){}
        
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
        StretchyList_Impl& push_back__impl(const T& obj, std::true_type ) {
            Shield<SEXP> s( wrap(obj.object) ) ;
            SEXP tmp  = Rf_cons( s, R_NilValue );
            Symbol tag  = obj.name ;
            SET_TAG(tmp, tag) ;
            SEXP self = Storage::get__() ;
            SETCDR( CAR(self), tmp) ;
            SETCAR( self, tmp ) ;
            return *this ;        
        }
        
        template <typename T>
        StretchyList_Impl& push_back__impl(const T& obj, std::false_type ) {
            Shield<SEXP> s( wrap(obj) ) ;
            SEXP tmp  = Rf_cons( s, R_NilValue );
            SEXP self = Storage::get__() ;
            SETCDR( CAR(self), tmp) ;
            SETCAR( self, tmp ) ;
            return *this ;    
        }
        
        template <typename T>
        StretchyList_Impl& push_front__impl(const T& obj, std::true_type ) {
            SEXP tmp ;
            SEXP self = Storage::get__() ;
            Shield<SEXP> s( wrap(obj.object) ) ;
            Symbol tag = obj.name ;
            tmp = Rf_cons(s, CDR(self) ) ;
            SET_TAG(tmp, tag );
            SETCDR(self, tmp) ;
            return *this ;    
        }
        
        template <typename T>
        StretchyList_Impl& push_front__impl(const T& obj, std::false_type ) {
            SEXP tmp ;
            SEXP self = Storage::get__() ;
            Shield<SEXP> s( wrap(obj) ) ;
            tmp = Rf_cons(s, CDR(self) ) ;
            SETCDR(self, tmp) ;
            return *this ;    
        }
        
    } ;
    
    typedef StretchyList_Impl<PreserveStorage> StretchyList ;
    
    template <typename... Args>
    SEXP structure( SEXP obj, Args... args ){
        StretchyList attrs = ATTRIB(obj) ;
        
        attrs.set( args... ) ;
        SET_ATTRIB(obj, attrs) ;
        
        return obj ;
    }
}
#endif
