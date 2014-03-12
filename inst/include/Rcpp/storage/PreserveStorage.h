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
        
    private:
        SEXP data ;
    } ;
    
}

#endif
