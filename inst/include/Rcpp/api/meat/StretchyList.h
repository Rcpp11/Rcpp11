// Copyright (C) 2013    Romain Francois

#ifndef Rcpp_api_meat_StretchyList_h
#define Rcpp_api_meat_StretchyList_h

namespace Rcpp{ 
    
    template< template <class> class StoragePolicy>
    template< typename T>
    StretchyList_Impl<StoragePolicy>& StretchyList_Impl<StoragePolicy>::push_back__impl( const T& obj, std::false_type ){
        Shield<SEXP> s( wrap(obj) ) ;
        SEXP tmp  = Rf_cons( s, R_NilValue );
        SEXP self = Storage::get__() ;
        SETCDR( CAR(self), tmp) ;
        SETCAR( self, tmp ) ;
        return *this ;
    }

    template< template <class> class StoragePolicy>
    template< typename T>
    StretchyList_Impl<StoragePolicy>& StretchyList_Impl<StoragePolicy>::push_back__impl( const T& obj, std::true_type ){
        Shield<SEXP> s( wrap(obj.object) ) ;
        SEXP tmp  = Rf_cons( s, R_NilValue );
        Symbol tag  = obj.name ;
        SET_TAG(tmp, tag) ;
        SEXP self = Storage::get__() ;
        SETCDR( CAR(self), tmp) ;
        SETCAR( self, tmp ) ;
        return *this ;
    }

    template< template <class> class StoragePolicy>
    template< typename T>
    StretchyList_Impl<StoragePolicy>& StretchyList_Impl<StoragePolicy>::push_front__impl( const T& obj, std::false_type){
        SEXP tmp ;
        SEXP self = Storage::get__() ;
        Shield<SEXP> s( wrap(obj) ) ;
        tmp = Rf_cons(s, CDR(self) ) ;
        SETCDR(self, tmp) ;
        return *this ;
    }

    template< template <class> class StoragePolicy>
    template< typename T>
    StretchyList_Impl<StoragePolicy>& StretchyList_Impl<StoragePolicy>::push_front__impl( const T& obj, std::true_type){
        SEXP tmp ;
        SEXP self = Storage::get__() ;
        Shield<SEXP> s( wrap(obj.object) ) ;
        Symbol tag = obj.name ;
        tmp = Rf_cons(s, CDR(self) ) ;
        SET_TAG(tmp, tag );
        SETCDR(self, tmp) ;
        return *this ;
    }

    
}

#endif
