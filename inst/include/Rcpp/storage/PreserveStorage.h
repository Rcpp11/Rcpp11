#ifndef Rcpp_storage_PreserveStorage_h
#define Rcpp_storage_PreserveStorage_h

namespace Rcpp{ 

    template <typename CLASS>
    class PreserveStorage {
    public:
        
        PreserveStorage() : data(R_NilValue){}
        
        ~PreserveStorage(){
            Rcpp_ReleaseObject(data) ;
            data = R_NilValue;
        }
        
        inline void set__(SEXP x){
            data = Rcpp_ReplaceObject(data, x) ;
            
            // calls the update method of CLASS
            // this is where to react to changes in the underlying SEXP
            static_cast<CLASS&>(*this).update(data) ;
        }
        
        inline SEXP get__() const {
            return data ;    
        }
        
        inline SEXP invalidate__(){
            SEXP out = data ;
            data = R_NilValue ;
            return out ;
        }
        
        inline CLASS& copy__(const CLASS& other){
            if( this != &other){
                set__(other.get__());
            }
            return static_cast<CLASS&>(*this) ;
        }
        
        inline CLASS& steal__(CLASS& other){
            if( this != &other){
                set__(other.invalidate__());
            }
            return static_cast<CLASS&>(*this) ;
        }
        
        inline operator SEXP() const { return data; }
        
        inline bool inherits(const char* clazz) const { 
            return ::Rf_inherits( data, clazz) ;
        }
        
        bool hasAttribute( const std::string& attr) const {
            SEXP attrs = ATTRIB(data);
            while( attrs != R_NilValue ){
                if( attr == CHAR(PRINTNAME(TAG(attrs))) ){
                    return true ;
                }
                attrs = CDR( attrs ) ;
            }
            return false;    
        }
        bool hasSlot(const std::string& name) const {
            if( !Rf_isS4(data) ) throw not_s4() ;
            return R_has_slot( data, Rf_mkString(name.c_str()) ) ;    
        }
                                                   
        inline bool isNULL() const{ return Rf_isNull(data) ; }
        inline bool isObject() const { return ::Rf_isObject(data) ;}
        inline bool isS4() const { return ::Rf_isS4(data) ; }
        
        
    private:
        SEXP data ;
    } ;
    
}

#endif
