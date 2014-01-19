#ifndef Rcpp_api_meat_NoProtectStorage_h
#define Rcpp_api_meat_NoProtectStorage_h

namespace Rcpp{ 
 
    template <typename CLASS>
    CharacterVector NoProtectStorage<CLASS>::attributeNames() const {
        SEXP attrs = ATTRIB(data);
        CharacterVector v( Rf_length( attrs ) ) ; ;
        for( int i=0; attrs != R_NilValue; i++, attrs=CDR(attrs) ){
            v[i] = PRINTNAME(TAG(attrs)) ;
        }
        return v ;
    }    
    
}

#endif
