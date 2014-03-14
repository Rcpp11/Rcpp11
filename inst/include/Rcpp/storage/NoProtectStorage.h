#ifndef Rcpp_storage_NoProtectStorage_h
#define Rcpp_storage_NoProtectStorage_h

namespace Rcpp{ 

    template <typename CLASS>
    class NoProtectStorage {
    public:
        
        inline void set__(SEXP x){
            data = x ;
            
            // calls the update method of CLASS
            // this is where to react to changes in the underlying SEXP
            static_cast<CLASS&>(*this).update(data) ;
        }
        
        inline SEXP get__() const {
            return data ;    
        }
        
        inline void copy__(const CLASS& other){
            set__(other.get__());
        }
        
        inline void steal__(CLASS& other){
            set__(other.invalidate__());
        }
        
        inline operator SEXP() const { return data; }
        
    private:
        SEXP data ;
        
        inline SEXP invalidate__(){ return data ;}
        
    } ;
    
}

#endif
