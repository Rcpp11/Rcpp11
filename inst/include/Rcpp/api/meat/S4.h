#ifndef Rcpp_api_meat_S4_h
#define Rcpp_api_meat_S4_h

namespace Rcpp{

    template < template <class> class StoragePolicy>
    bool S4_Impl<StoragePolicy>::is( const std::string& clazz ) {
        CharacterVector cl = AttributeProxyPolicy<S4_Impl>::attr("class");
                
        // simple test for exact match
        if( ! clazz.compare( cl[0] ) ) return true ;
                
        try{
            SEXP containsSym = Rf_install("contains");
            CharacterVector res( Rf_getAttrib(
                R_do_slot(R_getClassDef(CHAR(Rf_asChar(as<SEXP>(cl)))),containsSym),
                R_NamesSymbol
            ));
            return std::any_of( 
                res.begin(), res.end(), 
                [&](String s){ return s == clazz.c_str() ; } 
            ) ;
        } catch( ... ){
            // we catch eval_error and also not_compatible when 
            // contains is NULL
        }
        return false ;
    }
    
    
}
#endif
