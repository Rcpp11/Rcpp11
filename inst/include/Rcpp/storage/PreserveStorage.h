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
        PreserveStorage(const PreserveStorage& ) = delete ;
        PreserveStorage(PreserveStorage&& ) = delete ;
        PreserveStorage& operator=(const PreserveStorage& ) = delete ;
        PreserveStorage& operator=(PreserveStorage&& ) = delete ;
        
        inline void set__(SEXP x){
            data = Rcpp_ReplaceObject(data, x) ;
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
        
        inline SEXP invalidate__(){
            SEXP out = data ;
            data = R_NilValue ;
            return out ;
        }
        
    } ;
    
}

#endif
